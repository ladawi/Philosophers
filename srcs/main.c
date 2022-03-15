/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladawi <ladawi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 20:08:02 by ladawi            #+#    #+#             */
/*   Updated: 2022/03/15 19:38:04 by ladawi           ###   ########.fr       */
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
			pthread_mutex_lock(&sg()->lock->philo_ded);
			sg()->philo_dead = 1;
			pthread_mutex_unlock(&sg()->lock->philo_ded);
			pthread_mutex_lock(&sg()->lock->print);
			printf("\033[0;91m%lld | Philo[%d] died\033[0m\n", set_timestamp(), i );
			// exit(1);
			return (1);
		}
	}
	return (0);
}



void	ft_test()
{
	int		i = 100;
	int		j = 0;
	struct timeval	t;

	gettimeofday(&t, NULL);
	ft_get_time(t);
	// j += i << 3;
	// j += i << 4;

	printf("Slt, <%d>\n", i);
	exit(1);
}

int	main(int ac, char **av)
{
	int	ttd;
	int	nb_philo;

	// ft_test();
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
	// printf("puke\n");

	while (1)
	{
		// printf("MUKMUKMUKMUK\n");
		if (check_dead(ttd, nb_philo) != 0)
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