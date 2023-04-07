/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakhsas <rakhsas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:03:56 by rakhsas           #+#    #+#             */
/*   Updated: 2023/04/06 02:12:29 by rakhsas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	search(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			if (str[i + 1])
				return (1);
		}
		i++;
	}
	return (0);
}

void	ft_env(int out)
{
	int	i;

	i = 0;
	if (!g_dep.env_copy)
		ft_putstr_fd("env: No such file or directory\n", out);
	while (g_dep.env_copy[i])
	{
		if (search(g_dep.env_copy[i], '=') == 1)
			ft_putendl_fd(g_dep.env_copy[i], out);
		i++;
	}
}
