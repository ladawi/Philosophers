/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladawi <ladawi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 20:46:28 by ladawi            #+#    #+#             */
/*   Updated: 2022/03/19 15:41:54 by ladawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_create_all_thread(void)
{
	size_t	i;
	int		err;

	i = 0;
	pthread_mutex_lock(&sg()->lock->sync);
	while ((int)i < sg()->settings->nb_philo)
	{
		err = pthread_create(&(sg()->philo_tab[i]->tid),
				NULL, &routine, (void *)i);
		if (err != 0)
			printf("\ncan't create thread\n");
		i++;
	}
	printf("---------\n");
	pthread_mutex_unlock(&sg()->lock->sync);
}

void	ft_pthread_join_all(void)
{
	size_t	i;
	int		err;

	i = 0;
	while ((int)i < sg()->settings->nb_philo)
	{
		err = pthread_join(sg()->philo_tab[i]->tid, NULL);
		if (err != 0)
			printf("\nCan't join thread %s\n", strerror(err));
		i++;
	}
}
