/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 22:01:49 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/28 00:20:13 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void *live_checker(void *arg)
{
	t_philo *philos = (t_philo *)arg;
	int i;
	long now;

	while (1)
	{
		i = 0;
		while (i < philos->rules->number_of_philos)
		{
			pthread_mutex_lock(&philos[i].lock_meal);
			now = get_time_ms();
			if (now - &philos[i].last_meal > philos->rules->time_to_die)
			{
				pthread_mutex_lock(&rules->print);
				printf("%ld %d died\n", now - rules->start_time, rules->philos[i].id);
				pthread_mutex_unlock(&rules->print);
				rules->someone_died = 1;
				pthread_mutex_unlock(&rules->philos[i].lock_meal);
				return (NULL);
			}
			pthread_mutex_unlock(&philos[i]->lock_meal);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

void	print_status(t_philo *philo, char *msg, int i)
{
	long	timestamp;

	timestamp = get_time_ms() - philo->rules->start_time;
	pthread_mutex_lock(&philo->rules->print);
	if (i == 1)
		philo->last_meal = timestamp;
	printf("%ld %d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(&philo->rules->print);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	s;
	int	n;

	i = 0;
	s = 1;
	n = 0;
	while ((str[i] > 8 && str[i] < 14) || (str[i] == 32))
		i++;
	while (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			s = s * (-1);
		if ((str[i] == 45 || str[i] == 43) && (str[i + 1] == 45
				|| str[i + 1] == 43))
			return (0);
		i++;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		n = (n * 10) + (str[i] - 48);
		i++;
	}
	return (n * s);
}

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000));
}
