/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakhsas <rakhsas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 13:52:44 by rakhsas           #+#    #+#             */
/*   Updated: 2023/04/06 13:44:56 by rakhsas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_next_main_exec(int *x, t_list *list)
{
	if (access(list->args[0], R_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(list->args[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_dep.exit_status = UNKNOWN_COMMAND;
		exit(g_dep.exit_status);
	}
	if (*x == 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(list->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		g_dep.exit_status = UNKNOWN_COMMAND;
		exit(g_dep.exit_status);
	}
}

void	ft_main_execution(t_list *list)
{
	int	x;
	int	i;

	x = 0;
	i = 0;
	while (g_dep.staar[i++])
	{
		g_dep.staar[i] = ft_join_free(g_dep.staar[i], "/");
		g_dep.staar[i] = ft_join_free(g_dep.staar[i], list->args[0]);
	}
	i = 0;
	while (g_dep.staar[i++])
	{
		if (access(g_dep.staar[i], X_OK) == 0
			&& !ft_strchr(g_dep.staar[i], '.'))
		{
			if (execve(g_dep.staar[i], list->args, g_dep.env_copy) == -1)
			{
				g_dep.exit_status = ERROR;
				exit(g_dep.exit_status);
			}
		}
	}
	ft_next_main_exec(&x, list);
}

void	do_exec(t_list *list)
{
	if (access(list->args[0], X_OK) == 0)
		execve(list->args[0], list->args, g_dep.env_copy);
}

void	main_execution(t_list *list)
{
	g_dep.str = get_arg();
	if (g_dep.str == NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(list->args[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_dep.exit_status = 127;
		exit(g_dep.exit_status);
	}
	g_dep.staar = ft_split(g_dep.str + 5, ':');
	do_exec(list);
	ft_main_execution(list);
}
