/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakhsas <rakhsas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 02:16:09 by rakhsas           #+#    #+#             */
/*   Updated: 2023/04/06 17:07:21 by rakhsas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_next_export(t_list *list, int i, int j)
{
	while (list->args[j])
	{
		i = 0;
		if (parssing(list->args[j]) == 1)
		{
			print_error("minishell: export: `", list->args[j]);
			print_error("': not a valid identifier", "\n");
			g_dep.exit_status = ERROR;
			return ;
		}
		else if (list->args[j][i] == '-')
		{
			print_error("minishell: export: --: invalid option\n",
				"export: usage: export [-nf] [name[=value] ...] or export -p\n");
			g_dep.exit_status = ERROR;
			return ;
		}
		ft_next_check(list->args[j]);
		j++;
	}
}

int	ft_check_for_existence(char *str, char c)
{
	int		i;
	char	*helper;
	char	*prefix;

	i = 0;
	while (g_dep.env_copy[i])
	{
		prefix = ft_search_1(g_dep.env_copy[i], '=');
		helper = ft_search(str, c);
		if (ft_strcmp(prefix, helper) == 0)
			return (free(helper), free(prefix), i);
		free(helper);
		free(prefix);
		i++;
	}
	return (0);
}

void	helper_export(char *str, int i, int *check, char *suffix)
{
	while (str[i] != '\0' && str[i] != '=')
	{
		if (str[i] == '+' && str[i + 1] == '=')
		{
			suffix = ft_search_1(str, '+');
			if (ft_check_for_existence(suffix, '+') > 0)
			{
				(ft_append(ft_check_for_existence(suffix,
							'='), str), check[0]++, free(suffix));
				return ;
			}
			else
			{
				(add_var_remove_p(str), check[0]++, free(suffix));
				break ;
			}
		}
		i++;
	}
}

void	change_value(char *str, int index)
{
	int		i;
	char	*tmp;
	char	*suffix;

	i = 0;
	while (str[i] != '=')
		i++;
	i++;
	suffix = ft_search(str, '=');
	tmp = ft_join_free(suffix, str + i);
	free(g_dep.env_copy[index]);
	g_dep.env_copy[index] = tmp;
}

char	*ft_check_for_equal(char *str)
{
	int		i;
	char	*new;

	i = 0;
	if (ft_strchr(str, '='))
		return (NULL);
	new = ft_join_free(str, "=");
	return (new);
}
