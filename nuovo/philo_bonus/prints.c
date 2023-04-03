/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimatt <marimatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:25:19 by marimatt          #+#    #+#             */
/*   Updated: 2022/07/21 18:22:57 by marimatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	ft_timestp(long long int t_start)
{
	return ((int)((ft_get_micros() - t_start)/ 1000));
}

int	ft_print_msg(t_data *p, char *msg)
{
	sem_wait(p->print_semaphore);
	if (ft_am_i_died(p) < 0)
	{
		printf("%d %d %s\n", ft_timestp(p->t_start), p->pos, msg);
		sem_post(p->print_semaphore);
		return (1);
	}
	return (-1);
}

void	ft_print_msg_with_time(t_data *p, char *msg, long long int t)
{
	sem_wait(p->print_semaphore);
	printf("%d %d %s\n", (int)(t / 1000), p->pos, msg);
	sem_post(p->print_semaphore);
}

void	ft_usleep(long long int dt)
{
	long long int	t_end;

	if (dt <= 50)
		return ;
	t_end = ft_get_micros() + dt;
	while (ft_get_micros() < t_end - 50)
		usleep(50);
}

void	ft_usleep_till(long long int t)
{
	t -= 50;
	while (ft_get_micros() < t)
		usleep(50);
}

void	ft_usleep_till_2(long long int t)
{
	long long int	t_now;

	t_now = ft_get_micros();
	while (t_now < t - 100)
	{
		usleep((t - t_now) * 0.9);
		t_now = ft_get_micros();
	}
	if (t - t_now > 50)
		usleep(50);
}
