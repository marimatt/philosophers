/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimatt <marimatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:23:26 by marimatt          #+#    #+#             */
/*   Updated: 2023/04/03 17:07:34 by marimatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	ft_run_all_philos(pthread_t *philo_th, t_philo **philo_par, t_globals *globals)
{
	int					pos;
	long long int		t_start;

	t_start = ft_get_micros();
	pos = 0;
	while (pos < globals->n)
	{
		if (pthread_create(&(philo_th[pos]), NULL, &run_philo, (void *)(philo_par[pos])) != 0)
			return (-1);
		philo_par[pos]->t_start = t_start;
		philo_par[pos]->t_last_meal = ft_get_micros();
		pos += 2;
	}
	pos = 1;
	while (pos < globals->n)
	{
		if (pthread_create(&philo_th[pos], NULL, &run_philo, (void *)(philo_par[pos])) != 0)
			return (-1);
		philo_par[pos]->t_start = t_start;
		philo_par[pos]->t_last_meal = ft_get_micros();
		pos += 2;
	}
	return (1);
}

void	free_all(t_philo **philo_p, pthread_t *philo_t, t_globals *globals)
{
	int	i;

	free(philo_p[0]->game_over);
	i = 0;
	while (i < globals->n)
	{
		free(philo_p[i]);
		i++;
	}
	free(philo_p);
	i = 0;
	while (i < globals->n)
	{
		pthread_mutex_destroy(globals->mutex_forks[i]);
		pthread_mutex_destroy(globals->mutex_meals[i]);
		free(globals->mutex_meals[i]);
		free(globals->mutex_forks[i]);
		i++;
	}
	free(globals->mutex_forks);
	free(globals->mutex_meals);
	free(globals->mutex_print);
	free(philo_t);
}
