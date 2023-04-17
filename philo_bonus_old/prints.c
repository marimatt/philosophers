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

int	ft_timestp(long long int t_start)
{
	return ((int)((ft_get_micros() - t_start)/ 1000));
}

void	ft_print_msg(t_data *p, char *msg)
{
	sem_wait(p->print_semaphore);
	printf("%d %d %s\n", ft_timestp(p->t_start), p->pos, msg);
	sem_post(p->print_semaphore);
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

	if (dt <= 0)
		return ;
	t_end = ft_get_micros() + dt;
	while (ft_get_micros() < t_end - 25)
		usleep(25);
	// while (ft_get_micros() < t_end)
	// 	continue ;
}

void	ft_usleep_till(long long int t)
{
	while (ft_get_micros(0) < t)
		usleep(50);
}
