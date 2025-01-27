/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 16:56:56 by kadachi           #+#    #+#             */
/*   Updated: 2025/01/27 17:24:02 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *nptr)
{
	int		sign;
	int		num;

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
		usleep(100);
}

void	print_status(t_philo *philo, char *str)
{
	if (!philo->data->is_dead)
	{
		pthread_mutex_lock(&philo->data->mtx_print);
		printf("%lld %d %s\n", gettime_ms(), philo->id, str);
		pthread_mutex_unlock(&philo->data->mtx_print);
	}
}
