/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 13:47:32 by kwillian          #+#    #+#             */
/*   Updated: 2025/08/23 13:48:28 by kwillian         ###   ########.fr       */
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
