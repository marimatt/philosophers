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

void	ft_clear_stuff(t_data *par)
{
	sem_close(par->forks_semaphore);
	sem_close(par->print_semaphore);
	sem_close(par->eat_semaphore);
	sem_unlink("/forks_semaphore");
	sem_unlink("/print_semaphore");
	sem_unlink("/eat_semaphore");
}

int	ft_init_semaphores(t_data *par, int retry)
{
	if (retry == 0)
		return (-1);
	sem_unlink("/forks_semaphore");
	sem_unlink("/print_semaphore");
	sem_unlink("/eat_semaphore");
	par->print_semaphore = sem_open("/print_semaphore", O_CREAT, S_IRWXU, 1);
	if (par->print_semaphore == SEM_FAILED)
		return (ft_init_semaphores(par, retry - 1));
	par->forks_semaphore = sem_open("/forks_semaphore", O_CREAT, S_IRWXU, par->n);
	if (par->forks_semaphore == SEM_FAILED)
	{
		sem_close(par->print_semaphore);
		return (ft_init_semaphores(par, retry - 1));
	}
	par->eat_semaphore = sem_open("/eat_semaphore", O_CREAT, S_IRWXU, 0);
	if (par->eat_semaphore == SEM_FAILED)
	{
		sem_close(par->print_semaphore);
		sem_close(par->forks_semaphore);
		return (ft_init_semaphores(par, retry - 1));
	}
	return (1);
}

void	*ft_check_eat(void *params)
{
	t_data	*par;
	int		i;

	par = (t_data *)params;
	i = 0;
	while (i < par->n)
	{
		if (sem_wait(par->eat_semaphore) == 0)
			i++;
	}
	kill_all_pids(par->pid, par->n);
	ft_clear_stuff(par);
	exit(0);
	return (NULL);
}

int	main(int argc, char **argv)
{
	pthread_t	t_check_eat;
	t_data		*par;
	int			*pid;

	if (ft_parse_args(&par, argv, argc) < 0)
		return (1);
	if (ft_init_int_pointer(&pid, 0, par->n) < 0)
		return (1);
	if (ft_init_semaphores(par, 3) < 0)
		return (1);
	if (par->n_must_eat > 0 && \
		pthread_create(&t_check_eat, NULL, &ft_check_eat, (void *)par) != 0)
		return (1);
	if (fork_philos(par, &pid) < 0)
	{
		kill_all_pids(pid, par->n);
		return (1);
	}
	waitpid(-1, NULL, 0);
	kill_all_pids(par->pid, par->n);
	ft_clear_stuff(par);
	return (0);
}
