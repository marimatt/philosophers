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

t_globals	*ft_parse_arguments(char **argv, int argc)
{
	t_globals	*global_params;

	if (argc < 5 || argc > 6)
		return (NULL);
	global_params = (t_globals*)malloc(sizeof(t_globals) * 1);
	if (global_params == NULL)
		return (NULL);
	global_params->n = ft_atoi(argv[1]);
	global_params->t_die = 1000 * ft_atoi(argv[2]);
	global_params->t_eat = 1000 * ft_atoi(argv[3]);
	global_params->t_sleep = 1000 * ft_atoi(argv[4]);
	global_params->min_eat = -1;
	if (argc == 6)
		global_params->min_eat = ft_atoi(argv[5]);
	if (global_params->n <= 0 || global_params->t_die < 0 || global_params->t_eat < 0 \
			|| global_params->t_sleep < 0 || (argc == 6 && global_params->min_eat < 0))	
	{
		free(global_params);
		global_params = NULL;
	}
	return (global_params);
}

int	ft_init_mutex(t_globals *g)
{
	int	i;

	g->mutex_print = (pthread_mutex_t *)malloc(sizeof(*(g->mutex_print)));
	g->mutex_forks = (pthread_mutex_t **)malloc(sizeof(*(g->mutex_forks)) * g->n);
	g->mutex_meals = (pthread_mutex_t **)malloc(sizeof(*(g->mutex_meals)) * g->n);
	if (g->mutex_print == NULL || g->mutex_forks == NULL || g->mutex_meals == NULL)
		return (-1);
	if (pthread_mutex_init(g->mutex_print, NULL) != 0)
		return (-1);
	i = 0;
	while (i < g->n)
	{
		g->mutex_forks[i] = (pthread_mutex_t *)malloc(sizeof(*(g->mutex_forks[i])));
		g->mutex_meals[i] = (pthread_mutex_t *)malloc(sizeof(*(g->mutex_forks[i])));
		if ((g->mutex_forks)[i] == NULL || (g->mutex_meals)[i] == NULL)
			return (-1);
		if (pthread_mutex_init((g->mutex_forks)[i], NULL) != 0)
			return (-1);
		if (pthread_mutex_init((g->mutex_meals)[i], NULL) != 0)
			return (-1);
		i++;
	}
	return (1);
}

int	ft_init_threads_pointers(pthread_t **philo_th, int n)
{
	*philo_th = (pthread_t *)malloc(sizeof(**philo_th) * n);
	if (*philo_th == NULL)
		return (-1);
	return (1);
}

void	fill_res(t_philo *res, int pos, t_globals *globals, int *game_over)
{
	res->n = globals->n;
	res->t_die = globals->t_die;
	res->t_eat = globals->t_eat;
	res->t_sleep = globals->t_sleep;
	res->min_eat = globals->min_eat;
	res->game_over = game_over;
	res->pos = pos;
	res->n_eats = 0;
}

t_philo	**assign_philo_par(t_globals *globals)
{
	int			n;
	int			*game_over;
	t_philo		**res;

	res = (t_philo **)malloc(sizeof(*res) * globals->n);
	if (res == NULL)
		return (NULL);
	if (ft_init_int_pointer(&game_over, -1) < 0)
		return (NULL);
	n = 0;
	while (n < globals->n)
	{
		res[n] = (t_philo *)malloc(sizeof(**res));
		if (res[n] == NULL)
			return (NULL);
		res[n]->mutex_f_l = (globals->mutex_forks)[n];
		res[n]->mutex_f_r = (globals->mutex_forks)[(n + 1) % globals->n];
		res[n]->mutex_print = globals->mutex_print;
		res[n]->mutex_meal = globals->mutex_meals[n];
		fill_res(res[n], n + 1, globals, game_over);
		n++;
	}
	return (res);
}
