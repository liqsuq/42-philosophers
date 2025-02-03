/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 20:12:13 by kadachi           #+#    #+#             */
/*   Updated: 2025/02/03 15:07:34 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static inline void	usage(void)
{
	printf("Usage: ./philo <num_of_philos> <time_to_die> <time_to_eat> "
		"<time_to_sleep> [num_of_must_eat]\n\n");
	printf("num_of_philos       number of philosophers and nunber of forks\n");
	printf("time_to_die [ms]    the time in when they must start eating\n");
	printf("time_to_eat [ms]    the time it takes them to eat\n");
	printf("time_to_sleep [ms]  the amount of sleep they need\n");
	printf("num_of_must_eat     number of times each philosopher must eat\n");
}

static inline int	init_thread(t_data *d)
{
	int	i;
	int	done_philos;

	i = -1;
	while (++i < d->num_philos)
	{
		d->philos[i].id = i + 1;
		d->philos[i].ms_ate = d->ms_start;
		d->philos[i].data = d;
		pthread_mutex_init(&d->philos[i].mtx_ate, NULL);
		if (pthread_create(&d->philos[i].thread, NULL, philo, &d->philos[i]))
		{
			printf("Error: pthread_create failed\n");
			pthread_mutex_destroy(&d->philos[i].mtx_ate);
			set_end(d);
			break ;
		}
	}
	monitor(d);
	done_philos = i;
	while (--i >= 0)
		pthread_join(d->philos[i].thread, NULL);
	while (++i < done_philos)
		pthread_mutex_destroy(&d->philos[i].mtx_ate);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		usage();
		return (1);
	}
	if (init_data(&data, argc, argv))
	{
		free_data(&data);
		return (1);
	}
	if (valid_data(argc, &data))
	{
		usage();
		free_data(&data);
		return (1);
	}
	if (init_thread(&data))
	{
		free_data(&data);
		return (1);
	}
	free_data(&data);
	return (0);
}
