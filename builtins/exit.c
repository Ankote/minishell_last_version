/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakhsas <rakhsas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 23:24:00 by rakhsas           #+#    #+#             */
/*   Updated: 2023/04/06 17:41:16 by rakhsas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_args(char **args)
{
	int	i;

	if (!args)
		return (0);
	i = 0;
	while (args[i])
		i++;
	return (i + 1);
}

void	is_numeric(char **args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (args[i] != NULL)
	{
		while (args[0][j])
		{
			if ((args[0][0] == '-' || args[0][0] == '+') && args[0][1] == '0'
			&& !ft_atoi(&args[0][1]))
				(ft_putendl_fd("exit", 1), exit(0));
			if (args[0][j] != '0' && !ft_atoi(&args[0][j]))
			{
				print_error("minishell: exit: ", args[0]);
				ft_putendl_fd(": numeric argument required", 2);
				g_dep.exit_status = 255;
				exit(g_dep.exit_status);
			}
			j++;
		}
		i++;
	}
}

void	helper(t_list *data)
{
	print_error("minishell: exit: ", data->args[1]);
	ft_putendl_fd(": numeric argument required", 2);
	g_dep.exit_status = 255;
	exit(g_dep.exit_status);
}

void	exit_next(t_list *data, int len)
{
	if (len > 2)
	{
		print_error("exit\n", "minishell: exit: too many arguments\n");
		g_dep.exit_status = ERROR;
	}
	else if (len == 2)
	{
		len = ft_atoi(data->args[1]);
		if (data->args[1][0] != '-' && len < 0)
			helper(data);
		else
		{
			ft_putendl_fd("exit", 1);
			g_dep.exit_status = ft_atoi(data->args[1]);
			exit(g_dep.exit_status);
		}
	}
}

int	ft_exit(t_list *data)
{
	long long	len;

	len = count_args(data->args + 1);
	if (len == 1)
		(ft_putendl_fd("exit", 1), g_dep.exit_status = 0,
			exit(g_dep.exit_status));
	if (data->args + 1)
	{
		is_numeric(data->args + 1);
		exit_next(data, len);
	}
	return (1);
}
