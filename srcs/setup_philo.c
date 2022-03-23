/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladawi <ladawi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:03:00 by ladawi            #+#    #+#             */
/*   Updated: 2022/03/23 16:04:10 by ladawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*create_philo(int id)
{
	t_philo	*philo;

	philo = ft_calloc(sizeof(t_philo), 1);
	if (philo == 0)
		return (NULL);
	philo->id = id;
	return (philo);
}

void	set_philo(void)
{
	struct timeval	t;
	size_t			i;

	i = 0;
	while ((int)i < sg()->settings->nb_philo)
	{
		sg()->philo_tab[i] = create_philo(i);
		gettimeofday(&t, NULL);
		sg()->philo_tab[i]->time_last_eat = set_timestamp();
		if (pthread_mutex_init(&sg()->philo_tab[i]->fork, NULL) != 0)
		{
			printf("\n mutex init failed\n");
			return ;
		}
		i++;
	}
}
