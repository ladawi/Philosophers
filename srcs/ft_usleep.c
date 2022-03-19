/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladawi <ladawi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 20:26:31 by ladawi            #+#    #+#             */
/*   Updated: 2022/03/19 15:39:06 by ladawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long unsigned int	ft_get_time(struct timeval arg)
{
	return (arg.tv_sec * 1000 + arg.tv_usec / 1000);
}

void	ft_usleep(long long unsigned int sleep_time)
{
	long long unsigned int	time;
	struct timeval			start;
	struct timeval			end;
	int						philo_dead;

	pthread_mutex_lock(&sg()->lock->philo_ded);
	philo_dead = sg()->philo_dead;
	pthread_mutex_unlock(&sg()->lock->philo_ded);
	gettimeofday(&start, NULL);
	time = ft_get_time(start);
	while (time < ft_get_time(start) + sleep_time && philo_dead == 0)
	{
		usleep(5);
		gettimeofday(&end, NULL);
		time = ft_get_time(end);
		pthread_mutex_lock(&sg()->lock->philo_ded);
		philo_dead = sg()->philo_dead;
		pthread_mutex_unlock(&sg()->lock->philo_ded);
	}
	return ;
}