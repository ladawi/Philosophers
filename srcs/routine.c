/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladawi <ladawi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 20:48:40 by ladawi            #+#    #+#             */
/*   Updated: 2022/03/22 21:00:13 by ladawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(size_t id_philo, int time_sleep)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	ft_print_status(id_philo, 's');
	ft_usleep(time_sleep);
	gettimeofday(&time, NULL);
}

void	philo_think(size_t id_philo)
{
	ft_print_status(id_philo, 't');
}

int	is_stop(void)
{
	pthread_mutex_lock(&sg()->lock->philo_ded);
	pthread_mutex_lock(&sg()->lock->eat);
	if (sg()->philo_dead == 1 || sg()->eat_done == 1)
	{
		pthread_mutex_unlock(&sg()->lock->print);
		pthread_mutex_unlock(&sg()->lock->philo_ded);
		pthread_mutex_unlock(&sg()->lock->eat);
		return (1);
	}
	pthread_mutex_unlock(&sg()->lock->philo_ded);
	pthread_mutex_unlock(&sg()->lock->eat);
	return (0);
}

void	*routine(void *arg)
{
	size_t	id_philo;
	int		time_sleep;
	int		time_eat;
	int		nb_philo;
	int		max_eat;

	id_philo = (size_t)(arg);
	pthread_mutex_lock(&sg()->lock->sync);
	time_sleep = sg()->settings->time_tosleep;
	time_eat = sg()->settings->time_toeat;
	nb_philo = sg()->settings->nb_philo;
	pthread_mutex_lock(&sg()->lock->eat);
	max_eat = sg()->settings->nb_eat_max;
	pthread_mutex_unlock(&sg()->lock->eat);
	pthread_mutex_unlock(&sg()->lock->sync);
	if (id_philo % 2 == 0)
		ft_usleep(5);
	while (is_stop() != 1)
	{
		philo_eat(id_philo, time_eat, nb_philo, max_eat);
		philo_sleep(id_philo, time_sleep);
		philo_think(id_philo);
	}
	return (arg);
}
