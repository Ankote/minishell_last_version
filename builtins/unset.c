/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakhsas <rakhsas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 10:09:44 by rakhsas           #+#    #+#             */
/*   Updated: 2023/04/06 17:07:08 by rakhsas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset_next(t_list *list, int i)
{
	int	j;

	j = 0;
	while (g_dep.env_copy[j] != '\0')
	{
		if (ft_strnstr(g_dep.env_copy[j], list->args[i],
				ft_strlen(list->args[i]))
			&& (g_dep.env_copy[j][ft_strlen(list->args[i])] == '='
			|| g_dep.env_copy[j][ft_strlen(list->args[i])] == '\0'))
		{
			while (g_dep.env_copy[j])
			{
				free(g_dep.env_copy[j]);
				g_dep.env_copy[j] = "";
				g_dep.env_copy[j] = ft_strjoin(g_dep.env_copy[j],
						g_dep.env_copy[j + 1]);
				j++;
			}
			g_dep.env_copy[j] = "\0";
			return ;
		}
		j++;
	}
}

void	ft_unset(t_list *list)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (list->args)
	{
		while (list->args[i])
		{
			j = 0;
			if (ft_isalnum(list->args[i][ft_strlen(list->args[i]) - 1] == 0)
					&& !ft_strnstr(g_dep.env_copy[j], list->args[i],
						ft_strlen(list->args[i])))
			{
				ft_putstr_fd(list->args[0], 1);
				ft_putstr_fd(": `", 1);
				ft_putstr_fd(list->args[i], 1);
				ft_putstr_fd("': not valid identifier\n", 1);
			}
			ft_unset_next(list, i);
			i++;
		}
	}
}
