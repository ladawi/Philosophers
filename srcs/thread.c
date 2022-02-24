/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladawi <ladawi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 20:46:28 by ladawi            #+#    #+#             */
/*   Updated: 2022/02/24 22:25:48 by ladawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_create_all_thread(void)
{
	size_t	i;
	int		err;

	i = 0;
	pthread_mutex_lock(&sg()->lock->test);
	while ((int)i < sg()->settings->nb_philo)
	{
		err = pthread_create(&(sg()->philo_tab[i]->tid),
				NULL, &routine, (void *)i);
		if (err != 0)
			printf("\ncan't create thread\n");
		i++;
	}
	printf("muk\n");
	pthread_mutex_unlock(&sg()->lock->test);
	// pthread_mutex_lock(&sg()->lock->all);
	// sg()->all_thread_launched = 1;
	// pthread_mutex_unlock(&sg()->lock->all);
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
