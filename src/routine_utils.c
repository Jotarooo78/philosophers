/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:50:15 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/20 13:25:48 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int 	all_ate_enough(t_data *data)
{
    int i;

    i = 0;
    data->all_ate_enough = 0;
    while (i < data->nb_philos)
    {
        if (data->philos->meals_eaten == data->meals_required)
            data->all_ate_enough++;
        i++;
    }
    if (data->all_ate_enough == data->nb_philos)
    {
        printf("end\n");
        return (1);
    }
    return (0);
}

int death_by_starvation(t_philo *philo)
{
    if (philo->last_meal_time >= philo->data->time_to_die)
    {
        pthread_mutex_lock(&philo->data->death_mutex);
        print_routine(philo, "died");
        pthread_mutex_unlock(&philo->data->death_mutex);
        return (1);
    }
    return (0);
}

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

