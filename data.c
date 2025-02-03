/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 15:07:05 by kadachi           #+#    #+#             */
/*   Updated: 2025/02/03 15:08:15 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static inline int	ft_atoi(const char *nptr)
{
	int	sign;
	int	num;

	sign = 1;
	num = 0;
	while (*nptr == ' ' || *nptr == '\f' || *nptr == '\n'
		|| *nptr == '\r' || *nptr == '\t' || *nptr == '\v')
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		num *= 10;
		num += *nptr - '0';
		nptr++;
	}
	num *= sign;
	return (num);
}

int	init_data(t_data *data, int argc, char **argv)
{
	int	i;

	memset(data, 0, sizeof(t_data));
	data->num_philos = ft_atoi(argv[1]);
	data->ms_die = ft_atoi(argv[2]);
	data->ms_eat = ft_atoi(argv[3]);
	data->ms_sleep = ft_atoi(argv[4]);
	data->num_eat = -1;
	if (argc == 6)
		data->num_eat = ft_atoi(argv[5]);
	data->ms_start = gettime_ms() + 100;
	data->mtx_forks = malloc(data->num_philos * sizeof(pthread_mutex_t));
	if (data->mtx_forks == NULL)
		return (printf("Error: malloc() failed\n"), 1);
	i = -1;
	while (++i < data->num_philos)
		pthread_mutex_init(&data->mtx_forks[i], NULL);
	pthread_mutex_init(&data->mtx_print, NULL);
	pthread_mutex_init(&data->mtx_end, NULL);
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->num_philos);
	if (data->philos == NULL)
		return (printf("Error: malloc() failed\n"), 1);
	memset(data->philos, 0, data->num_philos * sizeof(t_philo));
	return (0);
}

int	valid_data(int argc, t_data *data)
{
	if (data->num_philos < 1)
		return (printf("Error: num_of_philos must be 1 or more\n"), 1);
	if (data->ms_die < 1 || data->ms_eat < 1 || data->ms_sleep < 1)
		return (printf("Error: time parameters must be 1 or more\n"), 1);
	if (data->num_eat < 0 && argc == 6)
		return (printf("Error: num_of_must_eat must be 0 or more\n"), 1);
	return (0);
}

void	free_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
		pthread_mutex_destroy(&data->mtx_forks[i]);
	free(data->mtx_forks);
	pthread_mutex_destroy(&data->mtx_print);
	pthread_mutex_destroy(&data->mtx_end);
	free(data->philos);
}
