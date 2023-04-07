/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aankote <aankote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 17:54:47 by rakhsas           #+#    #+#             */
/*   Updated: 2023/04/06 21:34:19 by aankote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_var_remove_p(char *str)
{
	char	*suff;
	char	*new;
	char	*new1;
	int		k;

	k = 0;
	new = ft_strrchr(str, '=');
	suff = ft_search_1(str, '+');
	new1 = ft_join_free(suff, new);
	g_dep.env_copy = ft_realloc(g_dep.env_copy, new1);
}

void	add_new_var(char *str)
{
	g_dep.env_copy = ft_realloc(g_dep.env_copy, str);
}

void	ft_append(int index, char *str)
{
	char	*tmp1;

	tmp1 = g_dep.env_copy[index];
	if (ft_check_for_equal(g_dep.env_copy[index]) == NULL)
	{
		g_dep.env_copy[index] = ft_join_free(g_dep.env_copy[index],
				ft_strrchr(str, '=') + 1);
		return ;
	}
}

void	export_declare(int k, int i, t_list *list)
{
	k = 0;
	while (g_dep.env_copy[k] != '\0')
		k++;
	while (k)
	{
		if (ft_strchr(g_dep.env_copy[i], '='))
		{
			ft_putstr_fd("declare -x ", list->outfile);
			print_test(g_dep.env_copy[i], list->outfile);
			ft_putstr_fd("\n", list->outfile);
		}
		else
		{
			if (ft_strlen(g_dep.env_copy[i]) > 0
				&& !ft_strchr(g_dep.env_copy[i], '='))
			{
				ft_putstr_fd("declare -x ", list->outfile);
				ft_putstr_fd(g_dep.env_copy[i], list->outfile);
				ft_putstr_fd("\n", list->outfile);
			}
		}
		i++;
		k--;
	}
}

void	export(t_list *list)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 1;
	k = 0;
	if (!list->args[1])
	{
		if (g_dep.env_copy)
			export_declare(k, i, list);
	}
	else
		ft_next_export(list, 0, 1);
}
