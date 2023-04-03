#include "./philo.h"

void	wait_for_forks(t_data *par)
{
	sem_wait(par->forks_semaphore);
	ft_print_msg(par, "has taken a fork");
	sem_wait(par->forks_semaphore);
	sem_wait(par->print_semaphore);
	par->last_meal = ft_get_micros();
	printf("%d %d has taken a fork\n", (int)((par->last_meal - par->t_start)/ 1000), par->pos);
	printf("%d %d is eating\n", (int)((par->last_meal - par->t_start) / 1000), par->pos);
	sem_post(par->print_semaphore);
	ft_usleep(par->t_eat);
	par->n_eats += 1;
	if (par->n_must_eat > 0 && par->n_eats >= par->n_must_eat)
		sem_post(par->eat_semaphore);
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

	par->last_meal = ft_get_micros();
	if (par->n == 1)
		return (ft_case_one_philo(par));
	if (pthread_create(&philo_thread, NULL, &check_philo_death, (void *)par) != 0)
		return ;
	par->last_meal = ft_get_micros();
	while (1)
	{
		wait_for_forks(par);
	}
}
