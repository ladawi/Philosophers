/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladawi <ladawi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 20:26:31 by ladawi            #+#    #+#             */
/*   Updated: 2022/03/15 19:30:23 by ladawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned	mult1000(unsigned n) 
{
	unsigned r;

	r = (n << 10) - (n << 5) + (n << 3);
	return (r);
}

unsigned	div1000(unsigned n)
{
	unsigned q;
	unsigned r;
	unsigned t;
	t = (n >> 7) + (n >> 8) + (n >> 12);
	q = (n >> 1) + t + (n >> 15) + (t >> 11) + (t >> 14);
	q = q >> 9;
	r = n - (mult1000(q));
	return q + ((r + 24) >> 10);
}

long long unsigned int	ft_get_time(struct timeval arg)
{
	unsigned i = 10;
	// printf("[%d], %d\n", arg.tv_usec / 1000, div1000(arg.tv_usec));
	// printf("[%d], %d\n", arg.tv_sec * 1000, mult1000(arg.tv_sec));
	// printf("<%u> {%ld}\n", multu10(multu10(multu10(arg.tv_sec))), arg.tv_sec * 1000);
	return (mult1000(arg.tv_sec) + div1000(arg.tv_usec));
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