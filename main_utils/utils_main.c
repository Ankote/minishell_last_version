/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aankote <aankote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:14:16 by rakhsas           #+#    #+#             */
/*   Updated: 2023/04/06 23:24:31 by aankote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_env_next(char **env, int n)
{
	char	**new_env;
	int		i;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i])
		i++;
	if (n == 0)
		new_env = (char **)malloc(sizeof(char *) * (i + (n + 1) + 1));
	else
		new_env = (char **)malloc(sizeof(char *) * (i + n + 1));
	if (!new_env)
		return (NULL);
	return (new_env);
}

char	**ft_help_env(char **env, int n)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	new_env = ft_env_next(env, n);
	i = 0;
	while (env[i])
	{
		j = 0;
		new_env[i] = malloc(sizeof(char) * ft_strlen(env[i]) + 1);
		while (env[i][j])
		{
			new_env[i][j] = env[i][j];
			j++;
		}
		new_env[i][j] = 0;
		i++;
	}
	if (n == 0)
		new_env[i++] = ft_strdup("OLDPWD=");
	new_env[i] = NULL;
	return (new_env);
}

int	ftsearch(char *haystack, char *needle, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (haystack[i] && (i < len))
	{
		j = 0;
		while (needle[j] == haystack[i + j] && (i + j < len))
		{
			if (needle[j + 1] == '\0')
			{
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

char	**default_env(void)
{
	char	*c;
	char	**new;

	c = getcwd(NULL, 0);
	new = (char **)malloc(sizeof(char *) * 4);
	if (!new)
		return (NULL);
	new[0] = ft_strdup("OLDPWD");
	new[1] = ft_strjoin("PWD=", c);
	free(c);
	new[2] = ft_strdup("SHLVL=1");
	new[3] = NULL;
	return (new);
}

void	init_vars(char **env, int ac, char **av)
{
	if (!env[0])
	{
		g_dep.env_copy = default_env();
		return ;
	}
	g_dep.env_copy = ft_help_env(env, checker(env));
	g_dep.pwd = get_pwd("PWD=");
	(void)ac;
	(void)av;
}
