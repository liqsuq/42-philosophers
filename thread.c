/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 16:38:50 by kadachi           #+#    #+#             */
/*   Updated: 2025/01/27 17:24:17 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static pthread_mutex_t	*choose_fork(int id_fork, t_philo *philo)
{
	int	id_philo;
	int	num_philos;

	id_philo = philo->id;
	num_philos = philo->data->num_philos;
	if (id_fork == 1)
	{
		if (id_philo % 2 == 0)
			return (&philo->data->mtx_forks[id_philo - 1]);
		else
			return (&philo->data->mtx_forks[id_philo % num_philos]);
	}
	else
	{
		if (id_philo % 2 == 0)
			return (&philo->data->mtx_forks[id_philo % num_philos]);
		else
			return (&philo->data->mtx_forks[id_philo - 1]);
	}
}

static void	*philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->data->is_dead == 0)
	{
		print_status(philo, "is thinking");
		pthread_mutex_lock(choose_fork(1, philo));
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(choose_fork(2, philo));
		print_status(philo, "has taken a fork");
		philo->ms_ate = gettime_ms();
		print_status(philo, "is eating");
		msleep(philo->data->ms_eat);
		philo->num_ate++;
		pthread_mutex_unlock(choose_fork(1, philo));
		usleep(10);
		pthread_mutex_unlock(choose_fork(2, philo));
		print_status(philo, "is sleeping");
		msleep(philo->data->ms_sleep);
	}
	return (NULL);
}

static void	*monitor(t_data *d)
{
	int		i;
	int		cnt_full;

	while (1)
	{
		i = -1;
		cnt_full = 0;
		while (++i < d->num_philos)
		{
			if (gettime_ms() - d->philos[i].ms_ate > d->ms_die)
			{
				pthread_mutex_lock(&d->mtx_print);
				printf("%lld %d died\n", gettime_ms(), d->philos[i].id);
				d->is_dead = 1;
				pthread_mutex_unlock(&d->mtx_print);
				return (NULL);
			}
			if (d->num_eat != -1 && d->philos[i].num_ate >= d->num_eat)
				cnt_full++;
		}
		if (d->num_eat != -1 && cnt_full >= d->num_philos)
			return (NULL);
	}
	return (NULL);
}

int	init_philos(t_data *d)
{
	int	i;

	d->philos = (t_philo *)malloc(sizeof(t_philo) * d->num_philos);
	if (d->philos == NULL)
		return (printf("Error: malloc failed\n"), 1);
	i = -1;
	while (++i < d->num_philos)
	{
		d->philos[i].id = i + 1;
		d->philos[i].num_ate = 0;
		d->philos[i].ms_ate = d->ms_start;
		d->philos[i].data = d;
		if (pthread_create(&d->philos[i].thread, NULL, philo, &d->philos[i]))
			return (printf("Error: pthread_create failed\n"), 1);
		pthread_detach(d->philos[i].thread);
		usleep(10);
	}
	monitor(d);
	return (0);
}
