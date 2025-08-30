/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 11:52:33 by kwillian          #+#    #+#             */
/*   Updated: 2025/08/30 17:17:27 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int argc, char **argv)
{
	t_philo			*philos;
	t_rules			rules;
	int				i;

	i = 0;
	if (validator(argc, argv))
		return (0);
	if (init_rules(&rules, argv, argc))
		return (1);
	if (init_mutex(&rules))
		return (1);
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
	if (start_threads(philos, &rules))
		return (1);
	return (0);
}
