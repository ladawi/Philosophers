/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladawi <ladawi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 20:16:10 by ladawi            #+#    #+#             */
/*   Updated: 2022/03/23 19:46:30 by ladawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long int	set_timestamp(void)
{
	struct timeval	t;
	long long int	ret;

	gettimeofday(&t, NULL);
	ret = (ft_get_time(t) - timestart());
	return (ret);
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
	int		i;

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

void	ft_print_status(size_t id, char c)
{
	int	is_philo_ded;
	int	eat_done;

	pthread_mutex_lock(&sg()->lock->print);
	pthread_mutex_lock(&sg()->lock->philo_ded);
	is_philo_ded = sg()->philo_dead;
	pthread_mutex_unlock(&sg()->lock->philo_ded);
	pthread_mutex_lock(&sg()->lock->eat);
	eat_done = sg()->eat_done;
	pthread_mutex_unlock(&sg()->lock->eat);
	id++;
	if (is_philo_ded == 0 && eat_done == 0)
	{
		if (c == 'f')
			printf("%llu %zu has taken a fork\n",
				set_timestamp(), id);
		else if (c == 'e')
			printf("%llu %zu is eating\n", set_timestamp(), id);
		else if (c == 's')
			printf("%llu %zu is sleeping\n", set_timestamp(), id);
		else if (c == 't')
			printf("%llu %zu is thinking\n", set_timestamp(), id);
	}
	pthread_mutex_unlock(&sg()->lock->print);
}
