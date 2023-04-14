/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_stuff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimatt <marimatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:33:50 by marimatt          #+#    #+#             */
/*   Updated: 2023/04/03 17:34:06 by marimatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	ft_unlock_with_ret(pthread_mutex_t *mtx, int val)
{
	pthread_mutex_unlock(mtx);
	return (val);
}


int	get_forks(t_philo *par, pthread_mutex_t *mutex_1, pthread_mutex_t *mutex_2)
{
	long long int	t_meal;

	pthread_mutex_lock(mutex_1);
	if (ft_print_msg(par, "has taken a fork") < 0)
		return (ft_unlock_with_ret(mutex_1, -1));
	pthread_mutex_lock(mutex_2);
	t_meal = ft_get_micros();
	pthread_mutex_lock(par->mutex_meal);
	par->t_last_meal = t_meal;
	pthread_mutex_unlock(par->mutex_meal);
	pthread_mutex_lock(par->mutex_print);
	if (*(par->game_over) > 0)
	{
		pthread_mutex_unlock(mutex_1);
		pthread_mutex_unlock(mutex_2);
		return (ft_unlock_with_ret(par->mutex_print, -1));
	}
	t_meal -= par->t_start;
	printf("%d %d %s\n", (int)(t_meal / 1000), par->pos, "has taken a fork");
	printf("%d %d %s\n", (int)(t_meal / 1000), par->pos, "is eating");
	pthread_mutex_unlock(par->mutex_print);
	ft_usleep(par->t_eat);
	pthread_mutex_unlock(mutex_1);
	return (ft_unlock_with_ret(mutex_2, 1));
}
