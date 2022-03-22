/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladawi <ladawi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 21:02:23 by ladawi            #+#    #+#             */
/*   Updated: 2022/03/22 21:12:20 by ladawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# define BUFF_SIZE 200

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_settings
{
	int	nb_philo;
	int	time_todie;
	int	time_toeat;
	int	time_tosleep;
	int	nb_eat_max;
}				t_settings;

typedef struct s_philo
{
	int				nb_eat;
	long long int	time_last_eat;
	size_t			id;
	int				done_eating;
	pthread_t		tid;
	pthread_mutex_t	fork;
}				t_philo;

typedef struct s_lock
{
	pthread_mutex_t	all;
	pthread_mutex_t	timestamp;
	pthread_mutex_t	philo_ded;
	pthread_mutex_t	sync;
	pthread_mutex_t	print;
	pthread_mutex_t	eat;
	pthread_mutex_t	tle;
}				t_lock;

typedef struct s_data
{
	t_settings		*settings;
	t_philo			**philo_tab;
	t_lock			*lock;
	long long int	timestart;
	int				all_thread_launched;
	int				philo_dead;
	int				eat_done;
	size_t			thread_done;
	size_t			philo_done_eating;
}				t_data;

t_data					*sg(void);

void					*ft_memset(void *s, int c, size_t n);
void					*ft_calloc(size_t nmemb, size_t size);
size_t					ft_strlen(const char *s);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
int						ft_atoi(const char *str);
char					*ft_itoa(long int n);

int						check_stop(int timedeath, int nb_philo);
void					ft_usleep(long long unsigned int sleep_time);
void					*routine(void *arg);
void					philo_eat(size_t id_philo,
							int timetoeat, int nb_philo, int eat_max);
void					set_philo(void);
void					ft_create_all_thread(void);
void					ft_pthread_join_all(void);
int						ft_check_arg_nb(int ac, char **av);
int						ft_check_overflow(char **av);
int						set_settings(int ac, char **av);
void					set_philo(void);
void					ft_print_status(size_t id_philo, char c);
long long unsigned int	ft_get_time(struct timeval arg);
long long int			set_timestamp(void);

#endif