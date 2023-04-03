#include "./philo.h"

void	ft_case_one_philo(t_data *par)
{
	ft_print_msg(par, "has taken a fork");
	ft_usleep(par->t_die);
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
	par->t_start = ft_get_micros();
	par->pid = *pid;
	while (i < par->n)
	{
		(par->pid)[i] = fork();
		if ((par->pid)[i] < 0)
			return (kill_all_pids(par->pid, i));
		else if ((par->pid)[i] == 0)
		{
			par->forks_semaphore = sem_open("/forks_semaphore", 0);
			par->print_semaphore = sem_open("/print_semaphore", 0);
			par->eat_semaphore = sem_open("/eat_semaphore", 0);
			par->pos = i + 1;
			run_philo(par);
			exit(0);
		}
		i++;
	}
	return (1);
}
