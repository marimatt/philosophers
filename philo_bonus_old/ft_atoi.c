/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimatt <marimatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:40:23 by marimatt          #+#    #+#             */
/*   Updated: 2022/01/21 14:34:37 by marimatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_is_num(char s)
{
	if (s >= '0' && s <= '9')
		return (1);
	else
		return (0);
}

static int	ft_isspace_3(char s)
{
	if (s == ' ' || s == '\f' || s == '\n')
		return (1);
	else if (s == '\r' || s == '\t' || s == '\v')
		return (1);
	else
		return (0);
}

static int	ft_to_power(int base, int pwr)
{
	int	res;

	if (pwr == 0)
		return (1);
	res = ft_to_power(base, pwr - 1) * base;
	return (res);
}

static int	ft_str_to_num(const char *s, int size, int pos)
{
	int	res;
	int	n;

	n = 0;
	res = 0;
	if (size == 0)
		return (0);
	while (size > 0)
	{
		res += (s[pos + size - 1] - 48) * ft_to_power(10, n);
		size--;
		n++;
	}
	return (res);
}

int	ft_atoi(const char *str)
{
	int		j;
	int		i;
	int		sign;

	i = 0;
	j = 0;
	sign = 1;
	while (ft_isspace_3(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (ft_is_num(str[i + j]) == 1)
		j++;
	return (sign * ft_str_to_num(str, j, i));
}
