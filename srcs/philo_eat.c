/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladawi <ladawi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 20:59:19 by ladawi            #+#    #+#             */
/*   Updated: 2022/03/22 21:00:40 by ladawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_fork(size_t id_philo, int nb_philo)
{
	pthread_mutex_lock(&sg()->philo_tab[id_philo]->fork);
	ft_print_status(id_philo, 'f');
	if (nb_philo == 1)
		return (ft_usleep(sg()->settings->time_todie));
	if (id_philo + 1 >= (size_t)nb_philo)
	{
		pthread_mutex_lock(&sg()->philo_tab[0]->fork);
	}
	else
	{
		pthread_mutex_lock(&sg()->philo_tab[id_philo + 1]->fork);
	}
	ft_print_status(id_philo, 'f');
}

void	unlock_fork(size_t id_philo, int nb_philo)
{
	pthread_mutex_unlock(&sg()->philo_tab[id_philo]->fork);
	if (id_philo + 1 >= (size_t)nb_philo)
		pthread_mutex_unlock(&sg()->philo_tab[0]->fork);
	else
		pthread_mutex_unlock(&sg()->philo_tab[id_philo + 1]->fork);
}

void	philo_eat(size_t id_philo, int timetoeat, int nb_philo, int eat_max)
{
	lock_fork(id_philo, nb_philo);
	pthread_mutex_lock(&sg()->lock->tle);
	ft_print_status(id_philo, 'e');
	sg()->philo_tab[id_philo]->time_last_eat = set_timestamp();
	pthread_mutex_unlock(&sg()->lock->tle);
	ft_usleep(timetoeat);
	sg()->philo_tab[id_philo]->nb_eat++;
	if (eat_max != -1)
	{
		pthread_mutex_lock(&sg()->lock->eat);
		if (sg()->philo_tab[id_philo]->done_eating == 0
			&& sg()->philo_tab[id_philo]->nb_eat >= eat_max)
		{
			sg()->philo_done_eating++;
			sg()->philo_tab[id_philo]->done_eating = 1;
		}
		pthread_mutex_unlock(&sg()->lock->eat);
	}
	unlock_fork(id_philo, nb_philo);
}
