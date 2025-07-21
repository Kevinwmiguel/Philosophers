/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 11:52:33 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/21 23:28:39 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000));
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;

	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&philo->rules->print);
	printf("%ld %d pegou os garfos e está comendo\n",
		get_time_ms(), philo->id);
	pthread_mutex_unlock(&philo->rules->print);
	usleep(philo->rules->must_eat / 1000);

	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);

	return (NULL);
}

void	start_threads(t_philo *philos, t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->number_of_philos)
	{
		pthread_create(&philos[i].thread, NULL, routine, &philos[i]);
		i++;
	}
	i = 0;
	while (i < rules->number_of_philos)
	{
		pthread_join(philos[i].thread, NULL); // DEvo mudar aqui para ficar infinito
		i++;
	}
}

t_philo	*create_philos(t_rules	*rules)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = malloc(sizeof(t_philo) * rules->number_of_philos);
	while (i < rules->number_of_philos)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].last_meal = 0;
		philos[i].rules = rules;
		philos[i].left_fork = &rules->forks[i];
		philos[i].right_fork = &rules->forks[(i + 1) % rules->number_of_philos];
		i++;
	}
	return (philos);
}

void	init_rules(t_rules *rules, char **argv, int argc)
{
	rules->number_of_philos = atoi(argv[1]);
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

int	main(int argc, char **argv)
{
	t_philo		*philos;
	t_rules		*rules;
	int			i;

	i = 0;
	if (argc < 5 || argc > 6)
	{
		printf("Just 5 or 6 arguments\n");
		exit(1);
	}
	rules = malloc(sizeof(t_rules));
	init_rules(rules, argv, argc);
	while (i < rules->number_of_philos)
	{
		pthread_mutex_init(&rules->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&rules->print, NULL);
	philos = create_philos(rules);
	if (!philos)
		return (1);
	while (1)
		start_threads(philos, rules);
	return (0);
}
