/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimatt <marimatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:22:49 by marimatt          #+#    #+#             */
/*   Updated: 2023/04/03 16:59:42 by marimatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	ft_usleep(long long int dt)
{
	long long int	t_end;

	if (dt <= 0)
		return (1);
	t_end = ft_get_micros() + dt - 50;
	while (ft_get_micros() < t_end)
		usleep(50);
	return (1);
}

int	ft_usleep_2(long long int dt)
{
	long long int	t_end;
	long long int	t_now;

	if (dt <= 50)
		return (1);
	t_now = ft_get_micros();
	t_end = t_now + dt;
	while (t_end - t_now > 100)
	{
		usleep((t_end - t_now) * 0.5);
		t_now = ft_get_micros();
	}
	return (1);
}

long long int	ft_get_micros(void)
{
	long long int	res;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	res = ((long long int)(current_time.tv_sec)) * 1000000;
	res += (long long int)(current_time.tv_usec);
	return (res);
}

int	ft_init_int_pointer(int **ptr, int val)
{
	*ptr = (int *)malloc(sizeof(**ptr));
	if (*ptr == NULL)
		return (-1);
	**ptr = val;
	return (1);
}
