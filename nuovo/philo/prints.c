/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimatt <marimatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:25:19 by marimatt          #+#    #+#             */
/*   Updated: 2022/07/14 15:02:32 by marimatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	ft_timestp(long long int t_start)
{
	return ((ft_get_micros() - t_start) / 1000);
}

int	ft_timestp_by_time(long long int t_now, long long int t_start)
{
	return ((t_now - t_start) / 1000);
}

int	ft_print_msg(t_philo *par, char *msg)
{
	int	t;

	pthread_mutex_lock(par->mutex_print);
	if (*(par->end_game) == 0)
	{
		t = ft_timestp(par->glob->t_start);
		printf("%d %d %s\n", t, par->pos, msg);
		pthread_mutex_unlock(par->mutex_print);
		return (1);
	}
	pthread_mutex_unlock(par->mutex_print);
	return (-1);
}
