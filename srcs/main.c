/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladawi <ladawi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 20:08:02 by ladawi            #+#    #+#             */
/*   Updated: 2022/03/19 17:00:04 by ladawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_dead(int timedeath, int nb_philo)
{
	int	i;
	int	delta;

	i = -1;
	while (++i < nb_philo)
	{
		pthread_mutex_lock(&sg()->lock->tle);
		delta = set_timestamp() - sg()->philo_tab[i]->time_last_eat;
		pthread_mutex_unlock(&sg()->lock->tle);
		if (delta > timedeath)
		{
			pthread_mutex_lock(&sg()->lock->philo_ded);
			sg()->philo_dead = 1;
			pthread_mutex_unlock(&sg()->lock->philo_ded);
			pthread_mutex_lock(&sg()->lock->print);
			printf("\033[0;91m%lld | Philo[%d] died\033[0m\n", set_timestamp(), i );
			pthread_mutex_unlock(&sg()->lock->print);
			return (1);
		}
	}
	pthread_mutex_lock(&sg()->lock->eat);
	if ((int)(sg()->philo_done_eating) >= nb_philo)
	{
		sg()->eat_done = 1;
		printf("\033[0;92m%lld | All Philo done eating\033[0m\n", set_timestamp());
		pthread_mutex_unlock(&sg()->lock->eat);
		return (1);
	}
	pthread_mutex_unlock(&sg()->lock->eat);
	return (0);
}

int	main(int ac, char **av)
{
	int	ttd;
	int	nb_philo;

	set_timestamp();
	if (set_settings(ac, av) != 0)
		return (1);
	ttd = sg()->settings->time_todie;
	nb_philo = sg()->settings->nb_philo;
	set_philo();
	printf("[%d]_", sg()->settings->nb_philo);
	printf("[%d]_", sg()->settings->time_todie);
	printf("[%d]_", sg()->settings->time_toeat);
	printf("[%d]_", sg()->settings->time_tosleep);
	printf("[%d]\n", sg()->settings->nb_eat_max);
	ft_create_all_thread();
	while (1)
	{
		// printf("MUK\n");
		if (check_dead(ttd, nb_philo) != 0)
			break;
		ft_usleep(1);
	}
	ft_pthread_join_all();
	while (1);
	return (0);
}