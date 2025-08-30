/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 21:17:04 by kwillian          #+#    #+#             */
/*   Updated: 2025/08/30 17:06:45 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_ispace(char c)
{
	return (c == ' ' || c == '\r' || c == '\f'
		|| c == '\t' || c == '\v' || c == '\n');
}

void	int_max_verify(t_rules *rules)
{
	if (rules->time_to_eat > INT_MAX || rules->time_to_sleep > INT_MAX)
	{
		printf("invalid time to eat or sleep\n");
		rules->erro = 1;
	}
	if (rules->time_to_die > 2147483647 || rules->time_to_die <= 0)
	{
		printf("invalid time to die time\n");
		rules->erro = 1;
	}
}

int	validator(int argc, char **argv)
{
	int	i;

	i = 1;
	if (atoi(argv[1]) == 0)
	{
		printf("Please at least 1+ Philosophers\n");
		return (1);
	}
	while (i < argc)
	{
		if (!is_digit(argv[i]))
		{
			printf("please just positive numbers\n");
			return (1);
		}
		i++;
	}
	if (argc < 5 || argc > 6)
	{
		printf("\t Please use: <number_of_philosophers> <time_to_die>\n\
			<time_to_eat> <time_to_sleep>\n\
			[number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	return (0);
}
