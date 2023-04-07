/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aankote <aankote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:34:21 by rakhsas           #+#    #+#             */
/*   Updated: 2023/04/06 23:23:38 by aankote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_pwd(char *str)
{
	char	*path;
	int		i;

	i = 0;
	while (g_dep.env_copy[i])
	{
		if (ft_strnstr(g_dep.env_copy[i], str, ft_strlen(str)))
			path = g_dep.env_copy[i] + ft_strlen(str);
		i++;
	}
	if (!path || ft_strlen(path) == 0)
		path = getenv(str);
	return (path);
}

void	cd_utils(t_list *list, char *path)
{
	if (list->args && path && chdir(path) == -1)
	{
		next_error("cd: ", list->args[1], ": No such file or directory");
		return ;
	}
	(update_old_pwd(), path = getcwd(NULL, 0));
	if (path)
		(update_pwd(path), g_dep.exit_status = SUCCESS);
}

void	*cd_home(t_list *list, char *path)
{
	path = get_pwd("HOME=");
	if (chdir(path) == -1)
		return (next_error("minishell: ", list->args[1],
				": HOME not set"), NULL);
	else
		g_dep.exit_status = SUCCESS;
	return (NULL);
}

void	*ft_cd(t_list *list)
{
	char	*path;
	int		i;

	i = 1;
	path = NULL;
	if (!list->args[1])
		cd_home(list, path);
	else if (list->args[1][0] == 0)
		return (NULL);
	else if (list->args[1][0] == '-')
	{
		if (ft_strcmp(get_pwd("OLDPWD="), get_pwd("PWD=")) == 0)
			return (ft_error("minishell: cd: OLDPWD not set"), NULL);
		else
			(chdir(get_pwd("OLDPWD=")), printf("%s\n", get_pwd("OLDPWD=")));
	}
	else if (list->args[1][0] == '~' && ft_strlen(list->args[1]) >= 1)
	{
		path = get_pwd("HOME=");
	}
	else
		path = list->args[i];
	cd_utils(list, path);
	return (0);
}
