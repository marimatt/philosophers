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

int	ft_malloc_mutex(t_data *par)
{
	par->mutex_print = (pthread_mutex_t *)malloc(sizeof(*(par->mutex_print)));
	if (par->mutex_print == NULL)
		return (-1);
	if (pthread_mutex_init(par->mutex_print, NULL) != 0)
	{
		free(par->mutex_print);
		return (-1);
	}
	par->mutex_forks = (pthread_mutex_t **)malloc(sizeof(*(par->mutex_forks)) \
							* par->n);
	if (par->mutex_forks == NULL)
	{
		free(par->mutex_print);
		return (-1);
	}
	par->mutex_lifes = (pthread_mutex_t **)malloc(sizeof(*(par->mutex_lifes)) \
							* par->n);
	if (par->mutex_lifes == NULL)
	{
		free(par->mutex_print);
		free(par->mutex_forks);
		return (-1);
	}
	return (1);
}

int	ft_init_mutex(t_data *par)
{
	int	i;

	if (ft_malloc_mutex(par) < 0)
		return (-1);
	i = 0;
	while (i < par->n)
	{
		par->mutex_forks[i] = \
			(pthread_mutex_t *)malloc(sizeof(*(par->mutex_forks[i])));
		if ((par->mutex_forks)[i] == NULL)
			return (-1);
		if (pthread_mutex_init((par->mutex_forks)[i], NULL) != 0)
			return (-1);
		(par->mutex_lifes)[i] = \
			(pthread_mutex_t *)malloc(sizeof(*(par->mutex_lifes[i])));
		if ((par->mutex_lifes)[i] == NULL)
			return (-1);
		if (pthread_mutex_init((par->mutex_lifes)[i], NULL) != 0)
			return (-1);
		i++;
	}
	return (1);
}

void	ft_print_meal(long long int t_n, long long int t_s, int pos)
{
	printf("%d %d %s\n", ft_timestp_by_time(t_n, t_s), pos, "has taken a fork");
	printf("%d %d %s\n", ft_timestp_by_time(t_n, t_s), pos, "is eating");
}

int	get_forks(t_philo *par, pthread_mutex_t *mutex_1, pthread_mutex_t *mutex_2)
{
	pthread_mutex_lock(mutex_1);
	if (ft_print_msg(par, "has taken a fork") < 0)
		return (ft_unlock_with_ret(mutex_1, -1));

	pthread_mutex_lock(mutex_2);
	pthread_mutex_lock(par->mutex_life);
	par->t_last_meal = ft_get_micros();
	pthread_mutex_lock(par->mutex_print);
	if (*(par->game_over) == 0)
	{
		ft_print_meal(ft_get_micros(), par->t_start, par->pos);
		pthread_mutex_unlock(par->mutex_print);
		pthread_mutex_unlock(par->mutex_life);
	}
	else
	{
		pthread_mutex_unlock(mutex_2);
		pthread_mutex_unlock(mutex_1);
		pthread_mutex_unlock(par->mutex_life);
		return (ft_unlock_with_ret(par->mutex_print, -1));
	}
	ft_usleep(par->t_eat);
	pthread_mutex_unlock(mutex_2);
	return (ft_unlock_with_ret(mutex_1, 1));
}
