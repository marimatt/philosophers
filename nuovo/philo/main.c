/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimatt <marimatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:25:19 by marimatt          #+#    #+#             */
/*   Updated: 2023/04/03 17:32:42 by marimatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	have_all_philos_eat_ok(t_philo **philo_par, int n)
{
	while (n > 0)
	{
		n--;
		if ((philo_par[n])->eat_ok == 0)
			return (-1);
	}
	return (1);
}

int	did_someone_died(t_philo **philo_p, int n)
{
	while (n > 0)
	{
		n--;
		pthread_mutex_lock(philo_p[n]->mutex_life);
		if (ft_get_micros() >= (philo_p[n])->t_last_meal + (philo_p[n])->t_die)
		{
			pthread_mutex_lock(philo_p[0]->mutex_print);
			*(philo_p[0]->game_over) = 1;
			printf("%d %d %s\n", ft_timestp(philo_p[0]->t_start), \
				n + 1, "died");
			pthread_mutex_unlock(philo_p[0]->mutex_print);
			pthread_mutex_unlock(philo_p[n]->mutex_life);
			return (n + 1);
		}
		pthread_mutex_unlock(philo_p[n]->mutex_life);
	}
	return (-1);
}

void	start_main_cycle(t_philo **philo_p, t_data *params)
{
	while (did_someone_died(philo_p, params->n) < 0)
	{
		if (params->min_eat > 0 && have_all_philos_eat_ok(philo_p, params->n) > 0)
		{
			pthread_mutex_lock(philo_p[0]->mutex_print);
			*(philo_p[0]->game_over) = 1;
			pthread_mutex_unlock(philo_p[0]->mutex_print);
			return ;
		}
	}
}

void	wait_joined_threads(pthread_t *philo_t, int n)
{
	int	i;

	i = -1;
	while (++i < n)
		pthread_join(philo_t[i], NULL);
}

int	main(int argc, char **argv)
{
	t_data				*global_params;
	pthread_t			*philo_th;
	t_philo				**philo_par;

	global_params = ft_parse_arguments(argv, argc);
	if (global_params == NULL)
		return (1);
	if (ft_init_mutex(global_params) < 0)
		return (1);
	if (ft_init_threads_pointers(&philo_th, global_params->n) < 0)
		return (1);
	philo_par = assign_philo_par(global_params);
	if (philo_par == NULL)
		return (1);
	if (ft_run_all_philos(philo_th, philo_par, global_params) > 0)
	{
		start_main_cycle(philo_par, global_params);
		wait_joined_threads(philo_th, global_params->n);
		free_philo_and_global_params(philo_par, global_params);
		free(philo_th);
		return (0);
	}
	free(philo_th);
	return (1);
}
