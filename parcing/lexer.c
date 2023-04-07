/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aankote <aankote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 10:50:47 by aankote           #+#    #+#             */
/*   Updated: 2023/04/06 22:59:48 by aankote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_cmd(t_list **list, t_token **token)
{
	t_token	*tmp;
	t_list	*tmp_list;

	tmp = *token;
	tmp_list = (t_list *)malloc(sizeof(t_list));
	list_init(tmp_list);
	if (!open_her(token, g_dep.env_copy))
		return (free(tmp_list));
	while (tmp && type_arg(tmp))
	{
		if (tmp->type == ARG || tmp->type == CMD)
			(tmp_list)->args = ft_realloc((tmp_list)->args, tmp->val);
		else if (tmp->type == INFILE)
			get_infile(tmp_list, tmp->val);
		else if (tmp->type == OUTFILE)
			get_outfile(tmp_list, tmp->val, OUTFILE);
		else if (tmp->type == APPEND)
			get_outfile(tmp_list, tmp->next->val, APPOUT);
		else if (tmp->type == HERDOC)
			get_infile(tmp_list, tmp->next->val);
		if ((tmp->next && tmp->next->type == PIPE) || !tmp->next)
			add_command(list, &tmp_list);
		tmp = tmp->next;
	}
	free(tmp_list);
}

int	type_arg(t_token *token)
{
	if (ft_strcmp(token->val, ">") == 0)
		token->type = TRUNC;
	else if (ft_strcmp(token->val, ">>") == 0)
		token->type = APPEND;
	else if (ft_strcmp(token->val, "<<") == 0)
		token->type = HERDOC;
	else if (ft_strcmp(token->val, "<") == 0)
		token->type = INPUT;
	else if (ft_strcmp(token->val, "|") == 0)
		token->type = PIPE;
	else if (token->prev && token->prev->type == INPUT)
		token->type = INFILE;
	else if (token->prev && token->prev->type == APPEND)
		token->type = APPOUT;
	else if (token->prev && token->prev->type == TRUNC)
		token->type = OUTFILE;
	else if (token->prev && token->prev->type == HERDOC)
		token->type = LIMITER;
	else if (token->prev == NULL || token->prev->type >= TRUNC)
		token->type = CMD;
	else
		token->type = ARG;
	return (1);
}

//leaks visited : done
void	get_token(char *line, t_token **token)
{
	int	i;

	*token = NULL;
	i = -1;
	while (line[++i])
	{
		if (line[i] && !ignore_sep(line[i], line, i))
			ft_add_str(line, token, &i);
		if (line[i] && ignore_sep(line[i], line, i))
			ft_add_opr(line, token, &i);
	}
}
//stoped here

char	*ft_expand_fname(char *str)
{
	int		i;
	char	*p;
	int		check;

	i = -1;
	check = 0;
	p = ft_strdup("");
	while (str[++i])
	{
		if (str[i] == '$' && (quotes(str, i) == 0 || quotes(str, i) == 1))
		{
			if (str[i + 1] != '$')
				get_val(&check, &i, str, &p);
			else
				i++;
		}
		else
			get_characters(str, &i, &p);
	}
	if (do_exp_inp(str) && check && (!p[0] || check_spac(p) > 1))
		return (free(p), free(str), ft_strdup("\b"));
	return (free(str), p);
}

// char *ft_expand_in(char *str)
// {
//     int i;
//     char *p;
//     char *value;
// 	int check;

//     i = -1;
// 	check = 0;
//     p = ft_strdup("");
//     while(str[++i])
//     {
//         if(str[i] == '$' && (quotes(str, i) == 0 || quotes(str, i) == 1))
//         {
//             if(str[i + 1] != '$')
//             {
// 				check = 1;
//                 value = ft_get_arg(g_dep.env_copy, str, (&i));
//                 p = ft_join_free(p, value);
// 				free(value);
//             }
//             else
//                 i++;
//         }
//         else
// 			ftt(str, &i, &p);
//         {
//             if((str[i] != '\'' && str[i] != '\"'))
//                 p = ft_charjoin(p, str[i]);
//             if(str[i] == '\'' && quotes(str, i) == 1)
//                 p = ft_charjoin(p, str[i]);
//             if(str[i] == '\"' && quotes(str, i) == 2)
//                 p = ft_charjoin(p, str[i]);
//         }
//     }
// 	if(do_exp_inp(str) && check && (!p[0] || check_spac(p) > 1))
// 		return(free(p), free(str), ft_strdup("\b"));
//     return (free(str), p);
// }

int	tokens(char *line, t_token **token)
{
	t_token	*tmp;

	get_token(line, token);
	tmp = *token;
	while (tmp)
	{
		type_arg(tmp);
		if (tmp->type == INFILE || tmp->type == OUTFILE)
			tmp->val = ft_expand_fname(tmp->val);
		if (tmp->type == APPOUT)
			tmp->val = ft_expand_fname(tmp->val);
		tmp = tmp->next;
	}
	if (!check_token_syntax(token))
	{
		return (SYNTAX_ERROR);
		g_dep.exit_status = SYNTAX_ERROR;
	}
	return (1);
}
