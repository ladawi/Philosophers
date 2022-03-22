/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladawi <ladawi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 20:16:10 by ladawi            #+#    #+#             */
/*   Updated: 2022/03/20 16:59:54 by ladawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long int	set_timestamp(void)
{
	struct timeval	t;

	pthread_mutex_lock(&sg()->lock->timestamp);
	if (sg()->timestart == 0)
	{
		gettimeofday(&t, NULL);
		sg()->timestart = ft_get_time(t);
	}
	gettimeofday(&t, NULL);
	pthread_mutex_unlock(&sg()->lock->timestamp);
	return (ft_get_time(t) - sg()->timestart);
}

static	int	ft_count_length(unsigned long int n)
{
	int		length;

	length = 1;
	while (n / 10 > 0)
	{
		length++;
		n = n / 10;
	}
	return (length);
}

static	void	ft_fill_number(char *number, long int n, int nb_length)
{
	unsigned long int	num;

	if (n < 0)
	{
		number[0] = '-';
		num = -n;
	}
	else
		num = n;
	while (--nb_length >= 0)
	{
		if (number[nb_length] != '-')
		{
			number[nb_length] = num % 10 + '0';
			num = num / 10;
		}
	}
}

char	*ft_itoa(long int n)
{
	char	*number;
	int		nb_length;
	int	i;

	i = 0;
	if (n < 0)
		nb_length = 1 + ft_count_length(-n);
	else
		nb_length = ft_count_length(n);
	number = (char *)malloc(sizeof(char) * (nb_length + 1));
	if (!(number))
		return (NULL);
	while (i < nb_length)
		number[i++] = 0;
	ft_fill_number(number, n, nb_length);
	number[nb_length] = '\0';
	return (number);
}

void	ft_print_status(size_t id_philo, char c)
{
	int	is_philo_ded;
	int	eat_done;
	pthread_mutex_lock(&sg()->lock->print);
	pthread_mutex_lock(&sg()->lock->philo_ded);
	pthread_mutex_lock(&sg()->lock->eat);
	is_philo_ded = sg()->philo_dead;
	eat_done = sg()->eat_done;
	pthread_mutex_unlock(&sg()->lock->philo_ded);
	pthread_mutex_unlock(&sg()->lock->eat);
	id_philo++;
	if (is_philo_ded == 0 && eat_done == 0)
	{
		if (c == 'f')
		{
			printf("%llu | Philo[%zu] has taken a fork ...\n",
				set_timestamp(), id_philo);
		}
		else if (c == 'e')
		{
			printf("%llu | Philo[%zu] is eating ...\n",
				set_timestamp(), id_philo);
		}
		else if (c == 's')
		{
			printf("%llu | Philo[%zu] is sleeping ...\n",
				set_timestamp(), id_philo);
		}
		else if (c == 't')
		{
			printf("%llu | Philo[%zu] is thinking ...\n",
				set_timestamp(), id_philo);
		}
	}
	pthread_mutex_unlock(&sg()->lock->print);
}
