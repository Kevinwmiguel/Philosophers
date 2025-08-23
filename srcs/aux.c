/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 22:01:49 by kwillian          #+#    #+#             */
/*   Updated: 2025/08/23 12:58:39 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	debuger(long now, t_philo *philo, int i)
{
	printf("%ld %d died\n\n", now, philo[i].id);
	philo->rules->someone_died = 1;
}

void	*live_checker(void *arg)
{
	t_philo	*ph;
	t_rules	*r;
	int		i;
	long	now;
	long	last;

	ph = (t_philo *)arg;
	r = ph[0].rules;
	while (!r->someone_died)
	{
		i = 0;
		while (i < r->number_of_philos && !r->someone_died)
		{
			now = get_time_ms();
			pthread_mutex_lock(ph[i].lock_meal);
			last = ph[i].last_meal;
			pthread_mutex_unlock(ph[i].lock_meal);
			if (now - last > r->time_to_die)
			{
				if (!r->someone_died)
				{
					pthread_mutex_lock(&r->print);
					r->someone_died = 1;
					pthread_mutex_lock(ph[i].lock_meal);
					if (r->must_eat != ph[i].meals_eaten)
						printf("%ld %d died\n", now - r->start_time, ph[i].id);
					pthread_mutex_unlock(&r->print);
					pthread_mutex_unlock(ph[i].lock_meal);
				}
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

void	print_status(t_philo *philo, const char *msg)
{
	long	timestamp;

	pthread_mutex_lock(&philo->rules->print);
	if (!philo->rules->someone_died)
	{
		timestamp = get_time_ms() - philo->rules->start_time;
		printf("%ld %d %s\n", timestamp, philo->id, msg);
	}
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
		if ((str[i] == 45 || str[i] == 43) && (str[i + 1] == 45 || str[i
				+ 1] == 43))
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
