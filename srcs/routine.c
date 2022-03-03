/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladawi <ladawi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 20:48:40 by ladawi            #+#    #+#             */
/*   Updated: 2022/03/03 02:29:53 by ladawi           ###   ########.fr       */
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

void	lock_fork(size_t id_philo, int timetoeat, int nb_philo)
{
	pthread_mutex_lock(&sg()->philo_tab[id_philo]->fork);
	ft_print_status(id_philo, 'f');
	if (nb_philo == 1)
		return (ft_usleep(sg()->settings->time_todie));
	if (id_philo + 1 >= (size_t)nb_philo)
		pthread_mutex_lock(&sg()->philo_tab[0]->fork);
	else
		pthread_mutex_lock(&sg()->philo_tab[id_philo + 1]->fork);
	ft_print_status(id_philo, 'f');
}

void	unlock_fork(size_t id_philo, int timetoeat, int nb_philo)
{
	pthread_mutex_unlock(&sg()->philo_tab[id_philo]->fork);
	if (id_philo + 1 >= (size_t)nb_philo)
		pthread_mutex_unlock(&sg()->philo_tab[0]->fork);
	else
		pthread_mutex_unlock(&sg()->philo_tab[id_philo + 1]->fork);
}

void	philo_eat(size_t id_philo, int timetoeat, int nb_philo)
{
	lock_fork(id_philo, timetoeat, nb_philo);
	
	ft_print_status(id_philo, 'e');
	ft_usleep(timetoeat);
	sg()->philo_tab[id_philo]->time_last_eat = set_timestamp();

	unlock_fork(id_philo, timetoeat, nb_philo);
}

void	*routine(void *arg)
{
	size_t	id_philo;
	int		time_sleep;
	int		time_eat;
	int		nb_philo;

	id_philo = (size_t)(arg);
	pthread_mutex_lock(&sg()->lock->sync);
	time_sleep = sg()->settings->time_tosleep;
	time_eat = sg()->settings->time_toeat;
	nb_philo = sg()->settings->nb_philo;
	pthread_mutex_unlock(&sg()->lock->sync);
	if (id_philo % 2 == 1)
		ft_usleep(20);
	while (1)
	{
		
		philo_eat(id_philo, time_eat, nb_philo);
		philo_sleep(id_philo, time_sleep);
		philo_think(id_philo);
	}
	return (arg);
}
