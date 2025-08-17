/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 11:52:33 by kwillian          #+#    #+#             */
/*   Updated: 2025/08/17 21:26:23 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void start_threads(t_philo *philos, t_rules *rules)
{
    int i;
    pthread_t monitor;

    i = 0;
    while (i < rules->number_of_philos)
    {
        pthread_create(&philos[i].thread, NULL, routine, &philos[i]);
        i++;
    }
	if (philos->rules->full == 1)
	{
		i = 0;
		while (i < philos->rules->number_of_philos)
		{
			pthread_cancel(philos[i].thread);
			i++;
		}
		freedom(philos, rules);
		exit(1);
	}
    pthread_create(&monitor, NULL, live_checker, (void *)philos);
    pthread_join(monitor, NULL);
    i = 0;
    while (i < rules->number_of_philos)
    {
        pthread_join(philos[i].thread, NULL);
        i++;
    }
    freedom(philos, rules);
}

t_philo *create_philos(t_rules *rules)
{
    t_philo *philos;
    int i = 0;

    philos = malloc(sizeof(t_philo) * rules->number_of_philos);
    if (!philos) return NULL;
    while (i < rules->number_of_philos)
    {
        philos[i].id = i + 1;
        philos[i].meals_eaten = 0;
        philos[i].last_meal = rules->start_time; /* absoluto */
        philos[i].rules = rules;
        philos[i].left_fork = &rules->forks[i];
        philos[i].right_fork = &rules->forks[(i + 1) % rules->number_of_philos];
        i++;
    }
    return philos;
}

void	init_rules(t_rules *rules, char **argv, int argc)
{
	rules->number_of_philos = atoi(argv[1]);
	if (rules->number_of_philos == 1)
	{
		printf("Just one Philo... he will STARVE\n");
		exit(1);
	}
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		rules->must_eat = ft_atoi(argv[5]);
	else
		rules->must_eat = -1;
	rules->someone_died = 0;
	rules->start_time = get_time_ms();
	rules->forks = malloc(sizeof(pthread_mutex_t) * rules->number_of_philos);
	if (!rules->forks)
		exit(1);
}

void	verify(int argc)
{
	if (argc < 5 || argc > 6)
	{
		printf("Please use: <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n");
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	t_philo			*philos;
	static t_rules	rules;
	int				i;

	i = 0;
	verify(argc);
	init_rules(&rules, argv, argc);
	while (i < rules.number_of_philos)
	{
		pthread_mutex_init(&rules.forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&rules.print, NULL);
	philos = create_philos(&rules);
	if (!philos)
		return (1);
	i = 0;
	while (i < rules.number_of_philos)
	{
		philos[i].lock_meal = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(philos[i].lock_meal, NULL);
		i++;
	}
	start_threads(philos, &rules);
	return (0);
}
