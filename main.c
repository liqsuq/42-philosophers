/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 20:12:13 by kadachi           #+#    #+#             */
/*   Updated: 2025/01/27 17:23:31 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_data(t_data *data, int argc, char **argv)
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
	data->ms_start = gettime_ms();
	data->mtx_forks = malloc(data->num_philos * sizeof(pthread_mutex_t));
	if (data->mtx_forks == NULL)
		return (printf("ERR: malloc() failed\n"), 1);
	i = -1;
	while (++i < data->num_philos)
		pthread_mutex_init(&data->mtx_forks[i], NULL);
	pthread_mutex_init(&data->mtx_print, NULL);
	return (0);
}

static void	free_data(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_philos)
		pthread_mutex_destroy(&data->mtx_forks[i]);
	free(data->mtx_forks);
	pthread_mutex_destroy(&data->mtx_print);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (1);
	if (init_data(&data, argc, argv))
	{
		free_data(&data);
		return (1);
	}
	if (init_philos(&data))
	{
		free_data(&data);
		return (1);
	}
	free_data(&data);
	return (0);
}
