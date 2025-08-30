/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 00:10:29 by kwillian          #+#    #+#             */
/*   Updated: 2025/08/30 17:17:37 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	init_mutex(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->number_of_philos)
	{
		pthread_mutex_init(&rules->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&rules->print, NULL);
	return (0);
}

int	init_rules(t_rules *rules, char **argv, int argc)
{
	rules->erro = 0;
	rules->number_of_philos = atoi(argv[1]);
	rules->time_to_die = ft_atoi2(argv[2]);
	rules->time_to_eat = ft_atoi2(argv[3]);
	rules->time_to_sleep = ft_atoi2(argv[4]);
	if (argc == 6)
		rules->must_eat = ft_atoi(argv[5]);
	else
		rules->must_eat = -1;
	if (int_max_verify(rules))
		return (1);
	if (rules->erro == 0)
	{
		rules->someone_died = 0;
		rules->start_time = get_time_ms();
		rules->forks = malloc(sizeof(pthread_mutex_t)
				* rules->number_of_philos);
		if (!rules->forks)
			return (1);
	}
	return (0);
}

int	start_threads(t_philo *philos, t_rules *rules)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	while (i < rules->number_of_philos)
	{
		pthread_create(&philos[i].thread, NULL, routine, &philos[i]);
		i++;
	}
	pthread_create(&monitor, NULL, live_checker, (void *)philos);
	pthread_join(monitor, NULL);
	i = 0;
	while (i < rules->number_of_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	if (philos->rules->full == 1)
	{
		i = 0;
		freedom(philos, rules);
		return (1);
	}
	freedom(philos, rules);
	return (0);
}

t_philo	*create_philos(t_rules *rules)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = malloc(sizeof(t_philo) * rules->number_of_philos);
	if (!philos)
		return (NULL);
	while (i < rules->number_of_philos)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].last_meal = rules->start_time;
		philos[i].rules = rules;
		philos[i].left_fork = &rules->forks[i];
		philos[i].right_fork = &rules->forks[(i + 1) % rules->number_of_philos];
		i++;
	}
	return (philos);
}
