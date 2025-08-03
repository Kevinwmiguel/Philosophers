/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 22:58:59 by kwillian          #+#    #+#             */
/*   Updated: 2025/08/03 23:13:54 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	//CHECK THE FORKS
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "is eating", 1);
	usleep(philo->rules->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);

	//SLEEP PROCESS
	print_status(philo, "is sleeping", 0);
	usleep(philo->rules->time_to_sleep);

	//waiting process
	print_status(philo, "is thinking", 0);
	return (NULL);
}
