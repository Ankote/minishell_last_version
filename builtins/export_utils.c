/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aankote <aankote@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:58:58 by rakhsas           #+#    #+#             */
/*   Updated: 2023/04/06 21:33:45 by aankote          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_next_search(int *i, char *str)
{
	char	*s;
	int		j;

	j = 0;
	s = (char *)malloc(sizeof(char) * (*i + 1));
	if (!s)
		return (NULL);
	while (str[j] && j < *i)
	{
		s[j] = str[j];
		j++;
	}
	s[j] = '\0';
	return (s);
}

char	*ft_search(char *str, char c)
{
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == c)
		{
			i++;
			break ;
		}
		i++;
	}
	return (ft_next_search(&i, str));
}

char	*ft_search_1(char *str, char c)
{
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == c)
		{
			break ;
		}
		i++;
	}
	return (ft_next_search(&i, str));
}

void	print_test(char *str, int fd)
{
	int		i;
	int		c;
	char	x;

	i = 0;
	c = 1;
	x = '"';
	while (i[str])
	{
		if (i[str] == '=' && c == 1)
		{
			write(fd, &i[str], 1);
			write(fd, &x, fd);
			c++;
		}
		else
			write(fd, &i[str], 1);
		i++;
	}
	write(fd, &x, 1);
}

int	parssing(char *c)
{
	int	i;

	i = 1;
	if (ft_isalnum(c[0]) == 0 && c[0] == '_')
		return (0);
	if (ft_isdigit(c[0]) == 1 || ft_isalpha(c[0]) == 0)
		return (1);
	while (c[i] != '\0' && c[i] != '=')
	{
		if (c[i] == '+' && c[i + 1] != '=')
			return (1);
		i++;
	}
	return (0);
}
