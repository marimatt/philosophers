/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimatt <marimatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:22:54 by marimatt          #+#    #+#             */
/*   Updated: 2022/07/21 18:22:55 by marimatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	ft_am_i_died(t_data *par)
{
	if (ft_get_micros() < par->last_meal + par->t_die)
		return (-1);
	return (1);
}

long long int	how_long_to_live(t_data *par, long long int t_now)
{
	return (par->last_meal + par->t_die - t_now);
}

void	ft_case_one_philo(t_data *par)
{
	ft_print_msg(par, "has taken a fork");
	ft_usleep_till(par->last_meal + par->t_die);
	printf("%d %d died\n", ft_timestp(par->t_start), par->pos);
	return ;
}

void	release_forks(sem_t *forks_semaphore)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (sem_post(forks_semaphore) == 0)
			i++;
	}
}

int	fork_philos(t_data *par, int **pid)
{
	int	i;

	i = 0;
	par->pid = *pid;
	par->t_start = ft_get_micros();
	while (i < par->n)
	{
		(*pid)[i] = fork();
		if ((*pid)[i] < 0)
			return (kill_all_pids(*pid, i));
		else if ((*pid)[i] == 0)
		{
			par->pos = i + 1;
			run_philo(par);
			exit(0);
		}
		i++;
		usleep(100);
	}
	return (1);
}
