/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 17:00:35 by kadachi           #+#    #+#             */
/*   Updated: 2025/01/27 17:23:11 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

struct	s_data;
struct	s_philo;

typedef struct s_philo
{
	int					id;
	volatile int		num_ate;
	volatile long long	ms_ate;
	pthread_t			thread;
	struct s_data		*data;
}						t_philo;

typedef struct s_data
{
	int				num_philos;
	int				ms_die;
	int				ms_eat;
	int				ms_sleep;
	int				num_eat;
	long long		ms_start;
	volatile int	is_dead;
	pthread_mutex_t	mtx_print;
	pthread_mutex_t	*mtx_forks;
	struct s_philo	*philos;
}					t_data;

int			init_philos(t_data *data);
int			ft_atoi(const char *nptr);
long long	gettime_ms(void);
void		msleep(unsigned int ms);
void		print_status(t_philo *philo, char *str);

#endif
