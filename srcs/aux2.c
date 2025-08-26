/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 13:47:32 by kwillian          #+#    #+#             */
/*   Updated: 2025/08/25 20:52:56 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	check_full(t_philo *p)
{
	pthread_mutex_lock(&p->rules->print);
	if (p->meals_eaten == p->rules->must_eat)
	{
		p->rules->full = 1;
		pthread_mutex_unlock(&p->rules->print);
		return (1);
	}
	if (p->rules->someone_died)
	{
		pthread_mutex_unlock(&p->rules->print);
		return (1);
	}
	pthread_mutex_unlock(&p->rules->print);
	return (0);
}

int	check_death(t_philo *p)
{
	pthread_mutex_lock(&p->rules->print);
	if (p->rules->someone_died)
	{
		pthread_mutex_unlock(&p->rules->print);
		return (1);
	}
	pthread_mutex_unlock(&p->rules->print);
	return (0);
}

void	eat_sleep(t_philo *p)
{
	pthread_mutex_lock(p->lock_meal);
	p->last_meal = get_time_ms();
	p->meals_eaten++;
	pthread_mutex_unlock(p->lock_meal);
	print_status(p, "is eating");
	usleep(p->rules->time_to_eat * 1000);
	pthread_mutex_unlock(p->right_fork);
	pthread_mutex_unlock(p->left_fork);
}

void	freedom(t_philo *philos, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->number_of_philos)
	{
		if (philos[i].lock_meal)
		{
			pthread_mutex_destroy(philos[i].lock_meal);
			free(philos[i].lock_meal);
		}
		i++;
	}
	i = 0;
	while (i < rules->number_of_philos)
	{
		pthread_mutex_destroy(&rules->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&rules->print);
	free(rules->forks);
	free(philos);
}
