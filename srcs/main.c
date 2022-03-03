/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladawi <ladawi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 20:08:02 by ladawi            #+#    #+#             */
/*   Updated: 2022/03/03 02:06:33 by ladawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(int timedeath, int nb_philo)
{
	int	i;
	int	delta;
	struct timeval	t;

	i = 0;
	while (++i < nb_philo)
	{
		// gettimeofday(&t, NULL);
		delta = set_timestamp() - sg()->philo_tab[i]->time_last_eat;
		if (delta > timedeath)
		{
			printf("muk\n");
			sg()->philo_dead = 1;
			return (1);
		}
	}
	return (0);
}

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
	// printf("puke\n");
	while (1)
	{
		// printf("MUKMUKMUKMUK\n");
		if (check_dead(sg()->settings->time_todie, sg()->settings->nb_philo) != 0)
			break;
		ft_usleep(1);
	}
	// while (1)
	// {
		// printf("fuck\n");
	// }
	ft_pthread_join_all();
	return (0);
}