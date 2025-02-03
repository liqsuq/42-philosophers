/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 13:35:39 by kadachi           #+#    #+#             */
/*   Updated: 2025/02/03 15:55:44 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static inline int	monitor_dead(t_data *d)
{
	int			i;
	long long	ms_ate;

	i = -1;
	while (++i < d->num_philos)
	{
		pthread_mutex_lock(&d->philos[i].mtx_ate);
		ms_ate = d->philos[i].ms_ate;
		pthread_mutex_unlock(&d->philos[i].mtx_ate);
		if (gettime_ms() - ms_ate > d->ms_die)
		{
			pthread_mutex_lock(&d->mtx_print);
			printf("%-6lld %d died\n",
				gettime_ms() - d->ms_start, d->philos[i].id);
			set_end(d);
			pthread_mutex_unlock(&d->mtx_print);
			return (1);
		}
	}
	return (0);
}

static inline int	monitor_full(t_data *d)
{
	int	i;
	int	cnt_full;

	i = -1;
	cnt_full = 0;
	while (++i < d->num_philos)
	{
		pthread_mutex_lock(&d->philos[i].mtx_ate);
		if (d->num_eat != -1 && d->philos[i].num_ate >= d->num_eat)
			cnt_full++;
		pthread_mutex_unlock(&d->philos[i].mtx_ate);
	}
	if (d->num_eat != -1 && cnt_full >= d->num_philos)
	{
		set_end(d);
		return (1);
	}
	return (0);
}

void	monitor(t_data *d)
{
	while (check_end(d) == 0)
	{
		if (monitor_dead(d))
			break ;
		if (monitor_full(d))
			break ;
	}
}
