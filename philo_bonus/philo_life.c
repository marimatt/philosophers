/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimatt <marimatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:22:49 by marimatt          #+#    #+#             */
/*   Updated: 2022/07/21 19:22:46 by marimatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	print_fork_and_eat(t_data *par)
{
	long long int	tmp;

	tmp = ft_get_micros();
	sem_wait(par->print_semaphore);
	printf("%d %d has taken a fork\n", (int)((tmp - par->t_start)/ 1000), par->pos);
	printf("%d %d is eating\n", (int)((tmp - par->t_start) / 1000), par->pos);
	sem_post(par->print_semaphore);
}

int	wait_with_ret(sem_t *sm, int ret)
{
	sem_wait(sm);
	return(ret);
}

// int ft_initial_timing_checks(t_data *par)
// {
// 	if (par->pos > par->n / 2)
// 	{
// 		if (par->t_die < par->t_eat + par->t_sleep || par->t_die < 2 * par->t_eat)
// 			return (-1);
// 	}
// 	return (1);
// }

int	ft_routine(t_data *par)
{
	long long int	tmp;

	// if (ft_initial_timing_checks(par) < 0)
	// 	return (-1);
	sem_wait(par->forks_semaphore);
	if(ft_print_msg(par, "has taken a fork") < 0)
		return (-1);
	sem_wait(par->forks_semaphore);
	tmp = ft_get_micros();
	if (how_long_to_live(par, tmp) <= 1000)
		return (wait_with_ret(par->print_semaphore, -1));
	par->last_meal = tmp;
	print_fork_and_eat(par);
	if (par->t_die < par->t_eat)
		return (wait_with_ret(par->print_semaphore, -1));
	ft_usleep(par->last_meal + par->t_eat - ft_get_micros());
	release_forks(par->forks_semaphore);
	par->n_eats += 1;
	if (par->n_must_eat > 0 && par->n_eats >= par->n_must_eat)
		sem_post(par->eat_semaphore);
	if (ft_print_msg(par, "is sleeping") < 0)
		return (-1);
	ft_usleep(par->t_sleep);
	return (ft_print_msg(par, "is thinking"));
}

void	ft_pre_sleep(t_data *par)
{
	if (par->n == 1)
		ft_usleep_till(par->last_meal + par->t_die + 50);
	else if (par->pos % 2 == 0)
	{
		if (par->t_eat < par->t_die)
			ft_usleep_till(par->last_meal + par->t_eat - 10000);
		else
			ft_usleep_till(par->last_meal + par->t_die + 50);
	}
	else if (par->n % 2 == 1 && par->n == par->pos)
	{
		if (par->t_die > 2 * par->t_eat)
			ft_usleep_till(par->last_meal + 2 * par->t_eat - 10000);
		else
			ft_usleep_till(par->last_meal + par->t_die + 50);
	}
}

void	run_philo(t_data *par)
{
	par->last_meal = ft_get_micros();

	ft_pre_sleep(par);

	while (ft_routine(par) > 0)
	{
		if (par->t_eat - par->t_sleep < par->t_die)
			ft_usleep_till(par->last_meal + par->t_eat - 500);
		else
			break ;
		if (par->n % 2 == 1 && par->n_eats % par->n == par->n - par->pos)
		{
			if (2 *par->t_eat - par->t_sleep < par->t_die)
				ft_usleep_till(par->last_meal + 2 *par->t_eat - 500);
			else
				break ;
		}
	}
	while(ft_am_i_died(par) < 0)
		continue ;

	printf("%d %d died\n", (int)((ft_get_micros() - par->t_start) / 1000), par->pos);
	exit(0);
}
