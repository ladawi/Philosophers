/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladawi <ladawi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:10:06 by ladawi            #+#    #+#             */
/*   Updated: 2022/03/23 14:32:40 by ladawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long int	timestart(void)
{
	static long long int	timestart;

	if (timestart == 0)
	{
		pthread_mutex_lock(&sg()->lock->timestamp);
		timestart = sg()->timestart;
		pthread_mutex_unlock(&sg()->lock->timestamp);
	}
	return (timestart);
}
