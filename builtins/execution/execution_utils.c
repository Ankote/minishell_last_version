/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakhsas <rakhsas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 22:24:58 by rakhsas           #+#    #+#             */
/*   Updated: 2023/04/06 02:12:29 by rakhsas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_if_builtin(t_list *list)
{
	int	i;

	i = 0;
	if (!ft_strcmp(list->args[0], "echo"))
		echo(list);
	else if (!ft_strcmp(list->args[0], "pwd"))
	{
		if (list->infile != -1 || list->outfile != -1)
			ft_putendl_fd(g_dep.pwd, list->outfile);
	}
	else if (!ft_strcmp(list->args[0], "exit"))
		ft_exit(list);
	else if (!ft_strcmp(list->args[0], "cd"))
		ft_cd(list);
	else if (!ft_strcmp(list->args[0], "env"))
		ft_env(list->outfile);
	else if (!ft_strcmp(list->args[0], "unset"))
		ft_unset(list);
	else if (!ft_strcmp(list->args[0], "export"))
		export(list);
	else
		i++;
	return (i);
}

char	*get_arg(void)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (g_dep.env_copy[i])
	{
		if (g_dep.env_copy[i][j] == 'P' && g_dep.env_copy[i][j + 4] == '=')
		{
			str = g_dep.env_copy[i];
			return (str);
		}
		i++;
	}
	return (NULL);
}
