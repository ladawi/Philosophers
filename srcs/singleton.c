/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladawi <ladawi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 19:55:20 by ladawi            #+#    #+#             */
/*   Updated: 2022/03/19 16:06:46 by ladawi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*sg(void)
{
	static t_data	*all = NULL;

	if (all)
		return (all);
	all = ft_calloc(sizeof(t_data), 1);
	if (all)
		all->settings = ft_calloc(sizeof(t_settings), 1);
	if (all)
		all->lock = ft_calloc(sizeof(t_lock), 1);
	return (all);
}