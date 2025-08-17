/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 11:46:54 by kwillian          #+#    #+#             */
/*   Updated: 2025/08/17 20:02:10 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

// pthread_mutex_t	g_mutex;

typedef struct s_rules
{
	int				number_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_think;
	int				time_to_sleep;
	int				must_eat;
	int				someone_died;
	long			start_time;
	long			end_time;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
}	t_rules;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*lock_meal;
	t_rules			*rules;
}	t_philo;

//MAIN

//AUX
int		ft_atoi(const char *str);
long	get_time_ms(void);
void	print_status(t_philo *philo, char *msg, int i);
void	*live_checker(t_philo *arg);
void	freedom(t_philo	*philos, t_rules *rules);
void stop_threads(t_philo *philos, t_rules *rules);

//ROUTINES
void	*routine(void *arg);

#endif