/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimatt <marimatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 14:45:39 by marimatt          #+#    #+#             */
/*   Updated: 2023/04/03 17:04:29 by marimatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>

typedef struct s_globals
{
	int					n;
	long long int		t_die;
	long long int		t_eat;
	long long int		t_sleep;
	long long int		min_eat;
	pthread_mutex_t		**mutex_forks;
	pthread_mutex_t		**mutex_meals;
	pthread_mutex_t		*mutex_print;
}			t_globals;

typedef struct s_philo
{
	int					n;
	long long int		t_die;
	long long int		t_eat;
	long long int		t_sleep;
	long long int		min_eat;
	long long int		t_start;
	pthread_mutex_t		*mutex_f_l;
	pthread_mutex_t		*mutex_f_r;
	pthread_mutex_t		*mutex_print;
	pthread_mutex_t		*mutex_meal;
	long long int		t_last_meal;
	int					n_eats;
	int					pos;
	int					*game_over;
}			t_philo;

int				ft_atoi(const char *str);

int				ft_usleep(long long int dt);
int				ft_usleep_2(long long int dt);
long long int	ft_get_micros(void);
int				ft_timestp(long long int t_start);
int				ft_timestp_by_time(long long int t_now, long long int t_start);
int				ft_print_msg(t_philo *p, char *msg);

t_globals		*ft_parse_arguments(char **argv, int argc);
int				ft_init_threads_pointers(pthread_t **philos, int n);
int				ft_init_int_pointer(int **ptr, int val);
int				ft_init_mutex(t_globals *par);
t_philo			**assign_philo_par(t_globals *globals);

int				ft_run_all_philos(pthread_t *philo_t, t_philo **philo_p, t_globals *globals);
void			*run_philo(void *params);

void			free_all(t_philo **philo, pthread_t *philo_t, t_globals *par);

#endif
