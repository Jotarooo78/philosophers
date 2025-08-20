/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:50:15 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/20 15:32:26 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int 	all_ate_enough(t_data *data)
{
    int i;

    i = 0;
    if (data->someone_died == 1)
        return (1);
    data->all_ate_enough = 0;
    while (i < data->nb_philos)
    {
        if (data->philos->meals_eaten == data->meals_required)
            data->all_ate_enough++;
        i++;
    }
    if (data->all_ate_enough == data->nb_philos)
    {
        return (1);
    }
    return (0);
}

int death_by_starvation(t_philo *philo)
{
    long time_since_last_meal;

    if (philo->data->someone_died == 1)
        return (1);
    time_since_last_meal = get_current_time(philo->data) - philo->last_meal_time;
    if (time_since_last_meal >= philo->data->time_to_die)
    {
        printf("%ld\n", time_since_last_meal);
        print_routine(philo, "died", "\033[31m");
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
