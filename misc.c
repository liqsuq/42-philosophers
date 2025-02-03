/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 16:56:56 by kadachi           #+#    #+#             */
/*   Updated: 2025/02/02 18:57:55 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	gettime_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((long long)time.tv_sec * 1000 + (long long)time.tv_usec / 1000);
}

void	msleep(unsigned int ms)
{
	long long	start;

	start = gettime_ms();
	while ((gettime_ms() - start) < ms)
		usleep(10);
}

int	check_end(t_data *d)
{
	int	ret;

	pthread_mutex_lock(&d->mtx_end);
	ret = d->is_end;
	pthread_mutex_unlock(&d->mtx_end);
	return (ret);
}

void	set_end(t_data *d)
{
	pthread_mutex_lock(&d->mtx_end);
	d->is_end = 1;
	pthread_mutex_unlock(&d->mtx_end);
}

void	print_status(t_philo *p, char *str)
{
	pthread_mutex_lock(&p->data->mtx_print);
	if (check_end(p->data) == 0)
		printf("%-6lld %d %s\n", gettime_ms() - p->data->ms_start, p->id, str);
	pthread_mutex_unlock(&p->data->mtx_print);
}
