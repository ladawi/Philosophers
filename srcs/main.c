/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladawi <ladawi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 20:08:02 by ladawi            #+#    #+#             */
/*   Updated: 2022/02/24 22:01:53 by ladawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	set_timestamp();
	if (set_settings(ac, av) != 0)
		return (1);
	set_philo();
	printf("[%d]_", sg()->settings->nb_philo);
	printf("[%d]_", sg()->settings->time_todie);
	printf("[%d]_", sg()->settings->time_toeat);
	printf("[%d]_", sg()->settings->time_tosleep);
	printf("[%d]\n", sg()->settings->nb_eat_max);
	ft_create_all_thread();
	while (1);
	// ft_pthread_join_all();
	return (0);
}