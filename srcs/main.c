/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kwillian <kwillian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 11:52:33 by kwillian          #+#    #+#             */
/*   Updated: 2025/07/11 12:01:20 by kwillian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int main(int argc, char **argv)
{
    if (argc == 5)
        printf("5");
    else if (argc == 6)
        printf("6");
    else
        printf("Just 5 or 6 arguments\n");
    return (0);
}