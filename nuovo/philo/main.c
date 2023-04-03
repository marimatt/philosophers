/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimatt <marimatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:25:19 by marimatt          #+#    #+#             */
/*   Updated: 2023/03/27 15:51:25 by marimatt         ###   ########.fr       */
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
	long long int	t_now;

	t_now = ft_get_micros();
	while (n > 0)
	{
		n--;
		pthread_mutex_lock(philo_p[n]->mutex_life);
		if (t_now >= (philo_p[n])->t_last_meal + (philo_p[n])->glob->t_die)
		{
			pthread_mutex_lock(philo_p[0]->mutex_print);
			*(philo_p[0]->end_game) = 1;
			printf("%d %d %s\n", ft_timestp(philo_p[0]->glob->t_start), \
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
		if (params->neat > 0 && have_all_philos_eat_ok(philo_p, params->n) > 0)
		{
			pthread_mutex_lock(philo_p[0]->mutex_print);
			*(philo_p[0]->end_game) = 1;
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
	pthread_t			*philo_th;
	t_philo				**philo_par;
	t_data				*global_params;

	global_params = ft_parse_arguments(argv, argc);
	if (global_params == NULL)
		return (1);
	if (ft_init_mutex(global_params) < 0)
		return (1);
	if (ft_init_threads(&philo_th, global_params->n) < 0)
		return (1);
	philo_par = assign_philo_par(global_params);
	if (philo_par == NULL)
		return (1);
	if (ft_run_all_philos(philo_th, philo_par, global_params) == global_params->n)
	{
		start_main_cycle(philo_par, global_params);
		wait_joined_threads(philo_th, global_params->n);
		free_philo_and_global_params(philo_par, global_params);
		free(philo_th);
		return (0);
	}
	return (1);
}
