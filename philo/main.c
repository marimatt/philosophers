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

int	have_all_philos_eat_ok(t_philo **philo_p, int n, int min_eat)
{
	while (n > 0)
	{
		n--;
		if ((philo_p[n])->n_eats < min_eat)
			return (-1);
	}
	return (1);
}

int	did_someone_died(t_philo **philo_p, int n)
{
	while (n > 0)
	{
		n--;
		pthread_mutex_lock(philo_p[n]->mutex_meal);
		if (ft_get_micros() > (philo_p[n])->t_last_meal + (philo_p[n])->t_die)
		{
			pthread_mutex_lock(philo_p[0]->mutex_print);
			*(philo_p[0]->game_over) = 1;
			printf("%d %d %s\n", ft_timestp(philo_p[0]->t_start), philo_p[n]->pos, "died");
			pthread_mutex_unlock(philo_p[n]->mutex_meal);
			pthread_mutex_unlock(philo_p[0]->mutex_print);
			return (philo_p[n]->pos);
		}
		pthread_mutex_unlock(philo_p[n]->mutex_meal);
	}
	return (-1);
}

void	start_main_cycle(t_philo **philo_p, t_globals *globals)
{
	while (did_someone_died(philo_p, globals->n) < 0)
	{
		if (globals->min_eat > 0 && \
			have_all_philos_eat_ok(philo_p, globals->n, globals->min_eat) > 0)
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
	while (n-- > 0)
		pthread_join(philo_t[n], NULL);
}

int	main(int argc, char **argv)
{
	t_globals	*globals;
	pthread_t	*philo_t;
	t_philo		**philo_p;

	globals = ft_parse_arguments(argv, argc);
	if (globals == NULL)
		return (1);
	if (ft_init_mutex(globals) < 0)
		return (1);
	if (ft_init_threads_pointers(&philo_t, globals->n) < 0)
		return (1);
	philo_p = assign_philo_par(globals);
	if (philo_p == NULL)
		return (1);
	if (ft_run_all_philos(philo_t, philo_p, globals) > 0)
	{
		start_main_cycle(philo_p, globals);
		wait_joined_threads(philo_t, globals->n);
		free_all(philo_p, philo_t, globals);
		return (0);
	}
	return (1);
}
