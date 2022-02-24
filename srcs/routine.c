/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladawi <ladawi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 20:48:40 by ladawi            #+#    #+#             */
/*   Updated: 2022/02/24 22:26:05 by ladawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	pthread_mutex_lock(&sg()->lock->test);
	pthread_mutex_unlock(&sg()->lock->test);
	printf("ok\n");
	return (arg);
}
