/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 22:58:59 by kwillian          #+#    #+#             */
/*   Updated: 2025/08/26 01:10:07 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	debuger(long now, t_philo *philo, int i)
{
	printf("%ld %d died\n", now, philo[i].id);
	philo->rules->someone_died = 1;
}

int	forkado(t_philo *p)
{
	if (p->rules->number_of_philos == 1)
	{
		print_status(p, "has taken a fork");
		usleep(p->rules->time_to_die * 1000);
		pthread_mutex_lock(&p->rules->print);
		printf("%ld %d died\n", (get_time_ms() - p->rules->start_time), p->id);
		p->rules->someone_died = 1;
		pthread_mutex_unlock(&p->rules->print);
		return (0);
	}
	else if (p->id % 2 == 0)
	{
		pthread_mutex_lock(p->right_fork);
		pthread_mutex_lock(p->left_fork);
		print_status(p, "has taken a fork");
		print_status(p, "has taken a fork");
	}
	else if (p->id % 2 != 0)
	{
		pthread_mutex_lock(p->left_fork);
		pthread_mutex_lock(p->right_fork);
		print_status(p, "has taken a fork");
		print_status(p, "has taken a fork");
	}
	return (1);
}

static void	smart_usleep(long ms, t_rules *r)
{
	long	start;

	start = get_time_ms();
	while (get_time_ms() - start < ms)
	{
		pthread_mutex_lock(&r->print);
		if (r->someone_died)
		{
			pthread_mutex_unlock(&r->print);
			break ;
		}
		pthread_mutex_unlock(&r->print);
		usleep(200);
	}
}

void	meal_race(t_philo *p)
{
	pthread_mutex_lock(p->lock_meal);
	p->last_meal = get_time_ms();
	p->meals_eaten++;
	pthread_mutex_unlock(p->lock_meal);
	print_status(p, "is eating");
	smart_usleep(p->rules->time_to_eat, p->rules);
	pthread_mutex_unlock(p->right_fork);
	pthread_mutex_unlock(p->left_fork);
}

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->id % 2 == 0)
		smart_usleep(p->rules->time_to_eat / 2, p->rules);
	while (1)
	{
		if (check_full(p))
			return (NULL);
		if (!forkado(p))
			break ;
		meal_race(p);
		if (check_death(p))
			break ;
		print_status(p, "is sleeping");
		smart_usleep(p->rules->time_to_sleep, p->rules);
		if (check_death(p))
			break ;
		if (p->rules->number_of_philos % 2 == 1)
			smart_usleep(p->rules->time_to_eat / 2, p->rules);
		print_status(p, "is thinking");
	}
	return (NULL);
}
