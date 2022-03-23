/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_settings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladawi <ladawi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 19:53:45 by ladawi            #+#    #+#             */
/*   Updated: 2022/03/23 19:52:49 by ladawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_arg_nb(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i <= ac && av[i] != 0)
	{
		if (av[i][j] >= '0' && av[i][j] <= '9')
			j++;
		else if (av[i][j] == 0)
		{
			i++;
			j = 0;
		}
		else
			return (-1);
	}
	return (0);
}

int	set_mutex(void)
{
	if (pthread_mutex_init(&sg()->lock->all, NULL) != 0)
		return (printf("\n Mutex init failed\n"));
	if (pthread_mutex_init(&sg()->lock->timestamp, NULL) != 0)
		return (printf("\n Mutex init failed\n"));
	if (pthread_mutex_init(&sg()->lock->philo_ded, NULL) != 0)
		return (printf("\n Mutex init failed\n"));
	if (pthread_mutex_init(&sg()->lock->sync, NULL) != 0)
		return (printf("\n Mutex init failed\n"));
	if (pthread_mutex_init(&sg()->lock->print, NULL) != 0)
		return (printf("\n Mutex init failed\n"));
	if (pthread_mutex_init(&sg()->lock->eat, NULL) != 0)
		return (printf("\n Mutex init failed\n"));
	if (pthread_mutex_init(&sg()->lock->tle, NULL) != 0)
		return (printf("\n Mutex init failed\n"));
	return (0);
}

int	check_null(void)
{
	if (sg()->settings->nb_philo == 0 || sg()->settings->nb_philo > 250)
		return (1);
	if (sg()->settings->time_todie < 50)
		return (1);
	if (sg()->settings->time_tosleep < 50)
		return (1);
	if (sg()->settings->nb_eat_max == 0)
	{
		sg()->philo_done_eating = sg()->settings->nb_philo;
		sg()->eat_done = 1;
	}
	return (0);
}

int	set_settings(int ac, char **av)
{
	int		nb;

	if (ac != 5 && ac != 6)
		return (printf("\033[0;91mError nb arg\033[0m\n"));
	if (ft_check_arg_nb(ac, av) == -1)
		return (printf("\033[0;91mError input in arg\033[0m\n"));
	set_mutex();
	sg()->philo_done_eating = 0;
	sg()->settings->nb_philo = ft_atoi(av[1]);
	sg()->settings->time_todie = ft_atoi(av[2]);
	sg()->settings->time_toeat = ft_atoi(av[3]);
	sg()->settings->time_tosleep = ft_atoi(av[4]);
	if (ac == 6)
		sg()->settings->nb_eat_max = ft_atoi(av[5]);
	else
		sg()->settings->nb_eat_max = -1;
	if (check_null() == 1)
		return (printf("Error input\n"));
	nb = sg()->settings->nb_philo + 1;
	(sg()->philo_tab) = ft_calloc(sizeof(t_philo *), nb);
	return (ft_check_overflow(av));
}
