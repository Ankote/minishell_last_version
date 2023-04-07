/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakhsas <rakhsas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 00:35:12 by rakhsas           #+#    #+#             */
/*   Updated: 2023/04/06 02:12:29 by rakhsas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	next_error(char *header, char *arg, char *msg)
{
	print_error(header, arg);
	ft_putendl_fd(msg, 2);
	g_dep.exit_status = ERROR;
}

void	ft_error(char *msg)
{
	ft_putendl_fd(msg, 2);
	g_dep.exit_status = ERROR;
}

void	update_pwd(char *path)
{
	int	i;

	i = 0;
	while (g_dep.env_copy[i])
	{
		if (ft_strnstr(g_dep.env_copy[i], "PWD=", ft_strlen("PWD=")))
		{
			free(g_dep.env_copy[i]);
			g_dep.env_copy[i] = ft_strjoin("PWD=", path);
			g_dep.pwd = path;
		}
		i++;
	}
}

void	update_old_pwd(void)
{
	int	i;

	i = 0;
	while (g_dep.env_copy[i])
	{
		if (ft_strnstr(g_dep.env_copy[i], "OLDPWD", ft_strlen("OLDPWD")))
		{
			free(g_dep.env_copy[i]);
			g_dep.env_copy[i] = ft_strjoin("OLDPWD=", g_dep.pwd);
			return ;
		}
		i++;
	}
}
