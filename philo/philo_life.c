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

int	ft_get_meal(t_philo *p, int *eats)
{
	if (p->n % 2 == 0)
	{
		if (((*eats % 2 == 1) ^ (p->pos % 2 == 0)))
		{
			if (get_forks(p, p->mutex_f_l, p->mutex_f_r) < 0)
				return (-1);
		}
		else if (get_forks(p, p->mutex_f_r, p->mutex_f_l) < 0)
			return (-1);
		return (1);
	}
	else
	{
		if (*eats == 0 && p->pos % 2 == 0)
			ft_usleep(p->t_eat);
		else if (*eats > 0 || p->pos == p->n)
			ft_usleep(2 * p->t_eat - p->t_sleep);
		return (get_forks(p, p->mutex_f_l, p->mutex_f_r));
	}
}

void	ft_sleep_and_think(t_philo *par, int *eats)
{
	*eats += 1;
	if (par->min_eat > 0 && *eats >= par->min_eat && par->eat_ok == 0)
		par->eat_ok = 1;
	if (ft_print_msg(par, "is sleeping") < 0)
		return ;
	ft_usleep(par->t_sleep);
	if (ft_print_msg(par, "is thinking") < 0)
		return ;
}

void	*run_philo(void *params)
{
	t_philo			*par;
	int				eats;

	par = (t_philo *)params;
	eats = 0;
	if (par->n == 1)
	{
		ft_print_msg(par, "has taken a fork");
		ft_usleep(par->t_die);
		return (NULL);
	}
	while (*(par->game_over) == 0)
	{
		if (ft_get_meal(par, &eats) >= 0)
			ft_sleep_and_think(par, &eats);
		else
			break ;
	}
	return (NULL);
}
