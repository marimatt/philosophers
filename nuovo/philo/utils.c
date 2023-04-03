/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimatt <marimatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:22:49 by marimatt          #+#    #+#             */
/*   Updated: 2023/04/03 15:47:15 by marimatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	ft_usleep(long long int dt)
{
	long long int	t_end;

	if (dt <= 0)
		return (1);
	t_end = ft_get_micros() + dt - 50;
	while (ft_get_micros() < t_end)
		usleep(50);
	return (1);
}

int	ft_usleep_2(long long int dt)
{
	long long int	t_end;
	long long int	t_now;
	long long int	tmp;

	if (dt <= 0)
		return (1);
	t_now = ft_get_micros();
	t_end = t_now + dt;
	while (t_now < t_end)
	{
		tmp = t_end - t_now;
		if (tmp < 50)
			break ;
		usleep((t_end - t_now) / 2);
		t_now = ft_get_micros();
	}
	return (1);
}

long long int	ft_get_micros(void)
{
	long long int	res;
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	res = ((long long int)(current_time.tv_sec)) * 1000000;
	res += (long long int)(current_time.tv_usec);
	return (res);
}

t_data	*ft_parse_arguments(char **argv, int argc)
{
	t_data	*global_params;

	if (argc < 5 || argc > 6)
		return (NULL);
	global_params = (t_data*)malloc(sizeof(t_data) * 1);
	if (global_params == NULL)
		return (NULL);
	global_params->n = ft_atoi(argv[1]);
	global_params->t_die = 1000 * ft_atoi(argv[2]);
	global_params->t_eat = 1000 * ft_atoi(argv[3]);
	global_params->t_eat = 1000 * ft_atoi(argv[4]);
	global_params->neat = -1;
	if (argc == 6)
		global_params->neat = ft_atoi(argv[5]);
	if (global_params->n <= 0 || global_params->t_die < 0 || global_params->t_eat < 0 \
			|| global_params->t_eat < 0 || (argc == 6 && global_params->neat < 0))	
	{
		free(global_params);
		global_params = NULL;
	}
	return (global_params);
}

int	ft_init_int_pointer(int **ptr, int val)
{
	*ptr = (int *)malloc(sizeof(**ptr));
	if (*ptr == NULL)
		return (-1);
	**ptr = val;
	return (1);
}
