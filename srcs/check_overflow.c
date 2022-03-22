/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_overflow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladawi <ladawi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 19:51:46 by ladawi            #+#    #+#             */
/*   Updated: 2022/03/22 21:01:07 by ladawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_overflow(char **av)
{
	if (ft_strncmp(av[1], ft_itoa(sg()->settings->nb_philo),
			ft_strlen(av[1])) != 0)
		return (printf("Overflow in input\n"));
	if (ft_strncmp(av[2], ft_itoa(sg()->settings->time_todie),
			ft_strlen(av[2])) != 0)
		return (printf("Overflow in input\n"));
	if (ft_strncmp(av[3], ft_itoa(sg()->settings->time_toeat),
			ft_strlen(av[3])) != 0)
		return (printf("Overflow in input\n"));
	if (ft_strncmp(av[4], ft_itoa(sg()->settings->time_tosleep),
			ft_strlen(av[4])) != 0)
		return (printf("Overflow in input\n"));
	if (sg()->settings->nb_eat_max != -1)
	{
		if (ft_strncmp(av[5], ft_itoa(sg()->settings->nb_eat_max),
				ft_strlen(av[5])) != 0)
			return (printf("Overflow in input\n"));
	}
	return (0);
}
