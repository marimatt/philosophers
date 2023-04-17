/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimatt <marimatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:25:19 by marimatt          #+#    #+#             */
/*   Updated: 2022/07/21 19:55:40 by marimatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	ft_philo_life(t_data *par, int *sent_signal_eats)
{
	sem_wait(par->forks_semaphore);
	ft_print_msg(par, "has taken a fork");
	sem_wait(par->forks_semaphore);
	par->last_meal = ft_get_micros();
	sem_wait(par->print_semaphore);
	printf("%d %d has taken a fork\n", (int)((par->last_meal - par->t_start)/ 1000), par->pos);
	printf("%d %d is eating\n", (int)((par->last_meal - par->t_start) / 1000), par->pos);
	sem_post(par->print_semaphore);
	ft_usleep(par->t_eat);
	par->n_eats += 1;
	if (par->n_must_eat > 0 && par->n_eats >= par->n_must_eat && *sent_signal_eats == 0)
	{
		sem_post(par->eat_semaphore);
		*sent_signal_eats = 1;
	}
	release_forks(par->forks_semaphore);
	ft_print_msg(par, "is sleeping");
	ft_usleep(par->t_sleep);
	ft_print_msg(par, "is thinking");
}

void	*check_philo_death(void *params)
{
	t_data			*par;
	long long int	dt;

	par = (t_data *)params;
	dt = par->last_meal + par->t_die - ft_get_micros();
	while (dt >= 0)
	{
		ft_usleep((long long int)(dt * 0.95));
		if (par->last_meal + par->t_die - ft_get_micros())
		{
			sem_wait(par->print_semaphore);
			if (par->last_meal + par->t_die - ft_get_micros() < 0)
			{
				printf("%d %d died\n", ft_timestp(par->t_start), par->pos);
				exit(0);
			}
			else
				sem_post(par->print_semaphore);
		}
		dt = par->last_meal + par->t_die - ft_get_micros();
	}
	return (NULL);
}

void	run_philo(t_data *par)
{
	pthread_t	philo_thread;
	int			sent_signal_eats;

	sent_signal_eats = 0;
	par->last_meal = ft_get_micros();
	if (par->n == 1)
		return (ft_case_one_philo(par));
	if (pthread_create(&philo_thread, NULL, &check_philo_death, (void *)par) != 0)
		return ;
	par->last_meal = ft_get_micros();
	while (1)
	{
		ft_philo_life(par, &sent_signal_eats);
	}
}
