/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marimatt <marimatt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 18:22:58 by marimatt          #+#    #+#             */
/*   Updated: 2022/07/21 18:22:59 by marimatt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

long long int	ft_get_micros()
{
	static struct timeval	t;

	gettimeofday(&t, NULL);
	return ((long long int)((t.tv_sec) * 1000000) + (long long int)((t.tv_usec)));
}

int	kill_all_pids(int *pid, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (pid[i] > 0)
			kill(pid[i], SIGKILL);
		i++;
	}
	i = 0;
	while (i < len)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
	return (-1);
}

int	ft_parse_args(t_data **par, char **argv, int argc)
{
	if (argc < 5 || argc > 6)
		return (-1);
	*par = (t_data *)malloc(sizeof(**par));
	if (par == NULL)
		return (-1);
	(*par)->n = ft_atoi(argv[1]);
	(*par)->t_die = (long long int)(1000 * ft_atoi(argv[2]));
	(*par)->t_eat = (long long int)(1000 * ft_atoi(argv[3]));
	(*par)->t_sleep = (long long int)(1000 * ft_atoi(argv[4]));
	(*par)->n_must_eat = -1;
	(*par)->n_eats = 0;
	if (argc == 6)
		(*par)->n_must_eat = ft_atoi(argv[5]);
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[2]) <= 0 || ft_atoi(argv[3]) <= 0 || \
		ft_atoi(argv[4]) <= 0 || (argc == 6 && ft_atoi(argv[5]) <= 0))
		return (-1);
	return (1);
}

int	ft_init_int_pointer(int **ptr, int val, int len)
{
	*ptr = (int *)malloc(sizeof(**ptr) * len);
	if (*ptr == NULL)
		return (-1);
	while (len > 0)
	{
		len--;
		(*ptr)[len] = val;
	}
	return (1);
}

int	ft_sum_array(int *arr, int len)
{
	int	res;

	res = 0;
	while (len > 0)
	{
		len--;
		res += arr[len];
	}
	return (res);
}
