/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:04:17 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/21 17:25:42 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int    join_threads(t_data *data)
{
    int i;

    i = 0;
    if (data->threads)
    {
        while (i < data->nb_philos)
        {
            if (pthread_join(data->threads[i], NULL) != 0)
                return (1);
            i++;
        }
    }
    return (0);
}

int    destroy_mutex(t_data *data)
{
    int i;

    i = 0;
    if (data->forks)
    {
        while (i < data->nb_philos)
        {
            if (data->forks)
            {
                if (pthread_mutex_destroy(&data->forks[i]) != 0)
                    return (1);
                if (pthread_mutex_destroy(&data->philos[i].meal_time) != 0)
                    return (1);
                if (pthread_mutex_destroy(&data->philos[i].meal_total) != 0)
                    return (1);
            }
            i++;
        }
        free(data->forks);
    }
    if (pthread_mutex_destroy(&data->death_mutex) != 0)
        return (1);
    if (pthread_mutex_destroy(&data->print_mutex) != 0)
        return (1);
    return (0);
}

int    cleanup_struct(t_data *data)
{
    if (join_threads(data) != 0)
        return (1);
    if (destroy_mutex(data) != 0)
        return (1);
    if (data->philos)
        free(data->philos);
    if (data->threads)
        free(data->threads);
    return (0);
}