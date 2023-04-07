/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aankote <aankote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 08:56:34 by aankote           #+#    #+#             */
/*   Updated: 2023/04/07 18:15:36 by aankote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_list(char **env, t_list **list)
{
	t_list	*tmp;
	int		i;

	i = -1;
	tmp = *list;
	while (tmp)
	{
		if (tmp->cmd)
			tmp->cmd = ft_expand(env, tmp->cmd);
		if (tmp->args)
		{
			while (tmp->args[++i])
			{
				tmp->args[i] = ft_expand(env, tmp->args[i]);
				if (!check_command(tmp->args[0]))
					tmp->infile = -1;
			}
		}
		i = -1;
		tmp = tmp->next;
	}
}

void	ft_lstclear(t_token **token)
{
	t_token	*current;
	t_token	*next;

	if (!token)
		return ;
	current = *token;
	while (current != NULL)
	{
		next = current->next;
		free(current->val);
		free(current);
		current = next;
	}
	*token = NULL;
}

void	ft_next(char *line, t_token *data, t_list *list)
{
	if (tokens(line, &data) == 258)
	{
		ft_lstclear(&data);
		free(line);
		return ;
	}
	get_cmd(&list, &data);
	ft_lstclear(&data);
	expand_list(g_dep.env_copy, &list);
	if (list)
		ft_exec(list);
	free_list(list);
	free(line);
}

int	checker(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ftsearch(env[i], "OLDPWD=", ft_strlen("OLDPWD=")) == 1)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_token	*data;
	t_list	*list;
	char	*line;

	data = malloc(sizeof(data));
	init_vars(env, ac, av);
	list = NULL;
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		signal(SIGINT, handle_signal2);
		line = readline("minishell$ ");
		if (!line)
			break ;
		if(line[0])
		{
			if (!check_cmd_syntax(line))
			{
				g_dep.exit_status = SYNTAX_ERROR;
				(add_history(line), free(line));
				continue ;
			}
			if (ft_strlen(line))
				(add_history(line), ft_next(line, data, list));
			
		}
	}
}
