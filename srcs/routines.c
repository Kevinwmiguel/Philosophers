/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 22:58:59 by kwillian          #+#    #+#             */
/*   Updated: 2025/08/20 21:47:39 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void freedom(t_philo *philos, t_rules *rules)
{
    int i = 0;

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

void *routine(void *arg)
{
    t_philo *p = (t_philo *)arg;

    if (p->id % 2 == 0)
        usleep(1000);
    while (1)
    {
		if (p->meals_eaten == p->rules->must_eat)
		{
			p->rules->full = 1;
			return (NULL);
		}
        if (p->rules->someone_died)
            break;
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
        pthread_mutex_lock(p->lock_meal);
        p->last_meal = get_time_ms();
        p->meals_eaten++;
        pthread_mutex_unlock(p->lock_meal);
        print_status(p, "is eating");
        usleep(p->rules->time_to_eat * 1000);
        pthread_mutex_unlock(p->right_fork);
        pthread_mutex_unlock(p->left_fork);
        if (p->rules->someone_died)
            break;
        print_status(p, "is sleeping");
        usleep(p->rules->time_to_sleep * 1000);
        if (p->rules->someone_died)
            break;
        print_status(p, "is thinking");
    }
    return NULL;
}
