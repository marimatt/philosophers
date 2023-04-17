/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimatt <marimatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:34:15 by marimatt          #+#    #+#             */
/*   Updated: 2023/04/03 17:36:01 by marimatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	ft_unlock_with_ret(pthread_mutex_t *mtx, int val)
{
	pthread_mutex_unlock(mtx);
	return (val);
}

int	ft_get_forks(t_philo *par, pthread_mutex_t *mutex_1, pthread_mutex_t *mutex_2)
{
	long long int	t_meal;

	pthread_mutex_lock(mutex_1);
	if (ft_print_msg(par, "has taken a fork") < 0)
		return (ft_unlock_with_ret(mutex_1, -1));
	pthread_mutex_lock(mutex_2);

	pthread_mutex_lock(par->mutex_meal);
	par->t_last_meal = ft_get_micros();
	pthread_mutex_unlock(par->mutex_meal);

	pthread_mutex_lock(par->mutex_print);
	if (*(par->game_over) > 0)
	{
		pthread_mutex_unlock(mutex_1);
		pthread_mutex_unlock(mutex_2);
		return (ft_unlock_with_ret(par->mutex_print, -1));
	}
	t_meal = par->t_last_meal - par->t_start;
	printf("%d %d %s\n", (int)(t_meal / 1000), par->pos, "has taken a fork");
	printf("%d %d %s\n", (int)(t_meal / 1000), par->pos, "is eating");
	pthread_mutex_unlock(par->mutex_print);
	ft_usleep_2(par->t_eat);
	pthread_mutex_unlock(mutex_1);
	return (ft_unlock_with_ret(mutex_2, 1));
}

int	ft_get_meal(t_philo *p)
{
	if (p->n % 2 == 0)
	{
		if ((p->pos + p->n_eats) % 2 == 0)
			ft_usleep_2((p->t_eat - p->t_sleep) * 0.75);
		if (p->pos % 2 == 0)
			return (ft_get_forks(p, p->mutex_f_l, p->mutex_f_r));
		return (ft_get_forks(p, p->mutex_f_r, p->mutex_f_l));
	}
	else
	{
		if ((p->pos + p->n_eats) % 2 == 0)
			// ft_usleep_2((p->t_eat - p->t_sleep) * 0.75);
			ft_usleep_2(p->t_eat / 2);
		else if ((p->pos + 1) % p->n == p->n_eats % p->n)
			ft_usleep_2(p->t_eat);
			// ft_usleep_2(2 * p->t_eat - p->t_sleep);
		return (ft_get_forks(p, p->mutex_f_l, p->mutex_f_r));
	}
}

void	ft_sleep_and_think(t_philo *par)
{
	par->n_eats += 1;
	if (ft_print_msg(par, "is sleeping") < 0)
		return ;
	ft_usleep_2(par->t_sleep);
	ft_print_msg(par, "is thinking");
}

void	*run_philo(void *params)
{
	t_philo	*par;

	par = (t_philo *)params;
	pthread_mutex_lock(par->mutex_meal);
	par->t_last_meal = ft_get_micros();
	pthread_mutex_unlock(par->mutex_meal);

	if (par->n == 1)
	{
		ft_print_msg(par, "has taken a fork");
		ft_usleep_2(par->t_die);
		return (NULL);
	}
	while (*(par->game_over) < 0)
	{
		if (ft_get_meal(par) >= 0)
			ft_sleep_and_think(par);
		else
			break ;
	}
	return (NULL);
}
