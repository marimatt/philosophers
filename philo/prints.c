/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimatt <marimatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:25:19 by marimatt          #+#    #+#             */
/*   Updated: 2023/04/03 17:24:13 by marimatt         ###   ########.fr       */
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
	pthread_mutex_lock(par->mutex_print);
	if (*(par->game_over) > 0)
	{
		pthread_mutex_unlock(par->mutex_print);
		return (-1);
	}
	printf("%d %d %s\n", ft_timestp(par->t_start), par->pos, msg);
	pthread_mutex_unlock(par->mutex_print);
	return (1);
}
