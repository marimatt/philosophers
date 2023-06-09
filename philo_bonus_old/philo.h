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

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <semaphore.h>
# include <signal.h>

#include <errno.h>

typedef struct s_data
{
	long long int			t_start;
	long long int			t_die;
	long long int			t_sleep;
	long long int			t_eat;
	long long int			last_meal;
	int						n_must_eat;
	int						n;
	int						pos;
	int						n_eats;
	int						*pid;
	sem_t					*print_semaphore;
	sem_t					*forks_semaphore;
	sem_t					*eat_semaphore;
}			t_data;

int					ft_atoi(const char *str);

void				*ft_check_eat(void *params);
void				ft_clear_stuff(t_data *par);
void				ft_print_msg_with_time(t_data *p, char *msg, long long int t);
void				ft_print_msg(t_data *p, char *msg);

int					kill_all_pids(int *pid, int len);
void				check_and_kill_all_pids(t_data *par);
int					ft_init_semaphores(t_data *par, int retry);

long long int		ft_get_micros();
int					ft_timestp(long long int t_start);
int					ft_parse_args(t_data **par, char **argv, int argc);
int					ft_init_int_pointer(int **ptr, int val, int len);
int					ft_sum_array(int *arr, int len);

void				ft_usleep(long long int dt);
void				ft_usleep_till(long long int dt);

void				ft_case_one_philo(t_data *par);
int					fork_philos(t_data *par, int **pid);

void				release_forks(sem_t *forks_semaphore);

void				run_philo(t_data *par);

// prints
void				ft_print_fork(t_data *par);
void				ft_print_sleep(t_data *par);
void				ft_print_eat(t_data *par);
void				ft_print_think(t_data *par);

#endif
