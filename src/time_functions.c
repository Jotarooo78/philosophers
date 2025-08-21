/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:50:15 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/21 17:51:16 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
	{
		perror("");
		return (1);
	}
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long get_current_time(t_data *data)
{
    long current;

    current = get_time();
    return (current - data->start_time);
}

long 	get_time_last_meal(t_philo *philo)
{
	long current;
	
    current = get_time();
	if (philo->last_meal_time == 0)
		return (current - philo->data->start_time);
	return (current - philo->last_meal_time);
}