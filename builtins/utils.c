/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rakhsas <rakhsas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:32:07 by rakhsas           #+#    #+#             */
/*   Updated: 2023/04/06 17:05:29 by rakhsas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	helper_test(int *check, char *str)
{
	int		index;
	char	*tmp;

	tmp = ft_search_1(str, '=');
	index = ft_check_for_existence(tmp, '=');
	free(tmp);
	if (*check == 0)
	{
		if (index == 0)
			add_new_var(str);
		else if (index >= 1)
			change_value(str, index);
	}
}

void	ft_next_check(char *str)
{
	int		i;
	int		check;
	char	*suffix;

	i = 0;
	check = 0;
	suffix = NULL;
	helper_export(str, i, &check, suffix);
	helper_test(&check, str);
}
