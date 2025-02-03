/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 17:00:35 by kadachi           #+#    #+#             */
/*   Updated: 2025/02/03 15:09:38 by kadachi          ###   ########.fr       */
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
	int					num_ate;
	long long			ms_ate;
	pthread_t			thread;
	pthread_mutex_t		mtx_ate;
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
	int				is_end;
	pthread_mutex_t	*mtx_forks;
	pthread_mutex_t	mtx_print;
	pthread_mutex_t	mtx_end;
	struct s_philo	*philos;
}					t_data;

int			init_data(t_data *data, int argc, char **argv);
int			valid_data(int argc, t_data *data);
void		free_data(t_data *data);
void		*philo(void *arg);
void		monitor(t_data *data);
long long	gettime_ms(void);
void		msleep(unsigned int ms);
int			check_end(t_data *d);
void		set_end(t_data *d);
void		print_status(t_philo *philo, char *str);

#endif
