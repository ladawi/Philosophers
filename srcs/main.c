/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladawi <ladawi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 20:08:02 by ladawi            #+#    #+#             */
/*   Updated: 2022/03/23 14:58:15 by ladawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_eat(int nb_philo)
{
	pthread_mutex_lock(&sg()->lock->eat);
	if ((int)(sg()->philo_done_eating) >= nb_philo)
	{
		sg()->eat_done = 1;
		pthread_mutex_unlock(&sg()->lock->eat);
		pthread_mutex_lock(&sg()->lock->print);
		printf("\033[0;92m%lld | All Philo done eating\033[0m\n",
			set_timestamp());
		pthread_mutex_unlock(&sg()->lock->print);
		return (1);
	}
	pthread_mutex_unlock(&sg()->lock->eat);
	return (0);
}

int	check_stop(int timedeath, int nb_philo)
{
	int	i;
	int	delta;

	i = -1;
	while (++i < nb_philo)
	{
		delta = set_timestamp(sg()->timestart);
		pthread_mutex_lock(&sg()->lock->tle);
		delta = delta - sg()->philo_tab[i]->time_last_eat;
		pthread_mutex_unlock(&sg()->lock->tle);
		if (delta > timedeath)
		{
			pthread_mutex_lock(&sg()->lock->print);
			printf("\033[0;91m%lld | Philo[%d] died\033[0m\n",
				set_timestamp(sg()->timestart), i + 1);
			pthread_mutex_unlock(&sg()->lock->print);
			pthread_mutex_lock(&sg()->lock->philo_ded);
			sg()->philo_dead = 1;
			pthread_mutex_unlock(&sg()->lock->philo_ded);
			return (1);
		}
	}
	return (check_eat(nb_philo));
}

void	ft_free(void)
{
	int	i;
	int	nb_philo;

	nb_philo = sg()->settings->nb_philo;
	i = 0;
	free(sg()->lock);
	while (i < nb_philo)
	{
		free(sg()->philo_tab[i]);
		i++;
	}
	free(sg()->philo_tab);
	free(sg()->settings);
	free(sg());
}

void	set_timestart(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	sg()->timestart = ft_get_time(t);
}

int	main(int ac, char **av)
{
	int	ttd;
	int	nb_philo;

	if (set_settings(ac, av) != 0)
	{
		free(sg()->settings);
		free(sg()->lock);
		free(sg());
		return (1);
	}
	ttd = sg()->settings->time_todie;
	nb_philo = sg()->settings->nb_philo;
	set_timestart();
	set_philo();
	timestart();
	ft_create_all_thread();
	while (1)
	{
		if (check_stop(ttd, nb_philo) != 0)
			break ;
		ft_usleep(5);
	}
	ft_pthread_join_all();
	ft_free();
	return (0);
}
