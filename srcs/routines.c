/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 22:58:59 by kwillian          #+#    #+#             */
/*   Updated: 2025/08/17 20:19:55 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	freedom(t_philo *philos, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->number_of_philos)
	{
		if (philos[i].lock_meal)
		{
			pthread_mutex_destroy(philos[i].lock_meal);
			pthread_mutex_destroy(philos[i].right_fork);
			pthread_mutex_destroy(philos[i].left_fork);
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
	exit(1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->rules->someone_died != 1)
	{
		if (philo->meals_eaten == philo->rules->must_eat)
		{
			freedom(philo, philo->rules);
			exit(1);
		}
		pthread_mutex_lock(philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
		print_status(philo, "is eating", 1);
		usleep(philo->rules->time_to_eat * 1000);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		print_status(philo, "is sleeping", 0);
		usleep(philo->rules->time_to_sleep * 1000);
		print_status(philo, "is thinking", 0);
	}
	return (NULL);
}
