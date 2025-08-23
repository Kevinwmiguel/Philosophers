/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 22:58:59 by kwillian          #+#    #+#             */
/*   Updated: 2025/08/23 13:48:23 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	debuger(long now, t_philo *philo, int i)
{
	printf("%ld %d died\n\n", now, philo[i].id);
	philo->rules->someone_died = 1;
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

void	forkado(t_philo *p)
{
	if (p->id % 2)
	{
		pthread_mutex_lock(p->right_fork);
		print_status(p, "has taken a fork");
		pthread_mutex_lock(p->left_fork);
		print_status(p, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(p->left_fork);
		print_status(p, "has taken a fork");
		pthread_mutex_lock(p->right_fork);
		print_status(p, "has taken a fork");
	}
}

void	*routine(void *arg)
{
	t_philo	*p;

	p = (t_philo *)arg;
	if (p->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		if (check_full(p))
			return (NULL);
		forkado(p);
		eat_sleep(p);
		if (check_death(p))
			break ;
		print_status(p, "is sleeping");
		usleep(p->rules->time_to_sleep * 1000);
		if (check_death(p))
			break ;
		print_status(p, "is thinking");
	}
	return (NULL);
}
