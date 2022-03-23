/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladawi <ladawi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 20:48:40 by ladawi            #+#    #+#             */
/*   Updated: 2022/03/23 19:54:09 by ladawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(size_t id_philo, int time_sleep)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	ft_print_status(id_philo, 's');
	ft_usleep(time_sleep);
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
	t_settings	*info;
	size_t		id_philo;

	id_philo = (size_t)(arg);
	pthread_mutex_lock(&sg()->lock->sync);
	info = sg()->settings;
	pthread_mutex_unlock(&sg()->lock->sync);
	if (id_philo % 2 == 0)
		ft_usleep(5);
	while (is_stop() != 1)
	{
		philo_eat(id_philo, info->time_toeat, info->nb_philo, info->nb_eat_max);
		philo_sleep(id_philo, info->time_tosleep);
		philo_think(id_philo);
	}
	return (arg);
}
