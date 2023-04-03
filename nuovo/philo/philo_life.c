/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimatt <marimatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:34:15 by marimatt          #+#    #+#             */
/*   Updated: 2022/07/21 17:18:56 by marimatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	ft_get_meal(t_philo *p, int *eats)
{
	if (p->glob->n % 2 == 0)
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
			ft_usleep_2(p->glob->t_eat);
		else if (*eats > 0 || p->pos == p->glob->n)
			ft_usleep_2(2 * p->glob->t_eat - p->glob->t_sleep);
		return (get_forks(p, p->mutex_f_l, p->mutex_f_r));
	}
}

void	ft_sleep_and_think(t_philo *par, int *eats)
{
	*eats += 1;
	if (par->glob->neat > 0 && *eats >= par->glob->neat && par->eat_ok == 0)
		par->eat_ok = 1;
	if (ft_print_msg(par, "is sleeping") < 0)
		return ;
	ft_usleep(par->glob->t_sleep);
	if (ft_print_msg(par, "is thinking") < 0)
		return ;
}

void	*run_philo(void *params)
{
	t_philo			*par;
	int				eats;

	par = (t_philo *)params;
	par->t_last_meal = ft_get_micros();
	eats = 0;
	if (par->glob->n == 1)
	{
		ft_print_msg(par, "has taken a fork");
		ft_usleep_2(par->glob->t_die);
		return (NULL);
	}
	while (*(par->end_game) == 0)
	{
		if (ft_get_meal(par, &eats) >= 0)
			ft_sleep_and_think(par, &eats);
		else
			break ;
	}
	return (NULL);
}
