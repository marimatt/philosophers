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

int	ft_init_threads_pointers(pthread_t **philo_t, int n)
{
	*philo_t = (pthread_t *)malloc(sizeof(**philo_t) * n);
	if (*philo_t == NULL)
		return (-1);
	return (1);
}

void	fill_res(t_philo *res, int pos, t_data *params, int *game_over)
{
	res->n = params->n;
	res->t_die = params->t_die;
	res->t_eat = params->t_eat;
	res->t_sleep = params->t_sleep;
	res->min_eat = params->min_eat;
	res->game_over = game_over;
	res->pos = pos;
	res->eat_ok = 0;
}

t_philo	**assign_philo_par(t_data *params)
{
	t_philo		**res;
	int			n;
	int			*game_over;

	res = (t_philo **)malloc(sizeof(*res) * params->n);
	if (res == NULL)
		return (NULL);
	if (ft_init_int_pointer(&game_over, -1) < 0)
		return (NULL);
	n = 0;
	while (n < params->n)
	{
		res[n] = (t_philo *)malloc(sizeof(**res));
		if (res[n] == NULL)
			return (NULL);
		res[n]->mutex_f_l = (params->mutex_forks)[n];
		res[n]->mutex_f_r = (params->mutex_forks)[(n + 1) % params->n];
		res[n]->mutex_life = (params->mutex_lifes)[n];
		res[n]->mutex_print = params->mutex_print;
		fill_res(res[n], n + 1, params, game_over);
		n++;
	}
	return (res);
}

int	ft_run_all_philos(pthread_t *philos_th, t_philo **philo_par, t_data *params)
{
	int					pos;
	long long int		t_start;

	t_start = ft_get_micros();
	pos = 0;
	while (pos < params->n)
	{
		philo_par[pos]->t_last_meal = t_start;
		philo_par[pos]->t_start = t_start;
		if (pthread_create(&(philos_th[pos]), NULL, &run_philo, \
				(void *)(philo_par[pos])) != 0)
			return (-1);
		pos += 2;
	}
	pos = 1;
	while (pos < params->n)
	{
		philo_par[pos]->t_last_meal = t_start;
		philo_par[pos]->t_start = t_start;
		if (pthread_create(&philos_th[pos], NULL, &run_philo, \
				(void *)(philo_par[pos])) != 0)
			return (-1);
		pos += 2;
	}
	return (1);
}

void	free_philo_and_global_params(t_philo **philo, t_data *par)
{
	int	i;

	free(philo[0]->game_over);
	i = 0;
	while (i < par->n)
	{
		free(philo[i]);
		i++;
	}
	free(philo);
	i = 0;
	while (i < par->n)
	{
		pthread_mutex_destroy(par->mutex_forks[i]);
		pthread_mutex_destroy(par->mutex_lifes[i]);
		free(par->mutex_forks[i]);
		free(par->mutex_lifes[i]);
		i++;
	}
	free(par->mutex_forks);
	free(par->mutex_lifes);
	free(par->mutex_print);
}
