/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aankote <aankote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 00:43:26 by aankote           #+#    #+#             */
/*   Updated: 2023/04/06 17:44:35 by aankote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	get_characters(char *str, int *i, char **p)
{
	if ((str[*i] != '\'' && str[*i] != '\"'))
		*p = ft_charjoin(*p, str[*i]);
	if (str[*i] == '\'' && quotes(str, *i) == 1)
		*p = ft_charjoin(*p, str[*i]);
	if (str[*i] == '\"' && quotes(str, *i) == 2)
		*p = ft_charjoin(*p, str[*i]);
}

void	get_val(int *check, int *i, char *str, char **p)
{
	char	*value;

	*check = 1;
	value = ft_get_arg(g_dep.env_copy, str, i);
	*p = ft_join_free(*p, value);
	free(value);
}
