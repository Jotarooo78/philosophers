/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:04:17 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/25 17:11:14 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    join_threads(t_data *data)
{
    int i;

    i = 0;
    printf("before join loop\n");
    while (i < data->nb_philos)
    {
        pthread_join(data->threads[i], NULL);
        i++;
    }
    printf("join loop end\n");
}

void    destroy_mutex(t_data *data)
{
    int i;

    i = 0;
    while (i < data->nb_philos)
    {
        pthread_mutex_destroy(&data->forks[i]);
        pthread_mutex_destroy(&data->philos[i].meal_time);
        pthread_mutex_destroy(&data->philos[i].meal_total);
        i++;
    }
    free(data->forks);
    pthread_mutex_destroy(&data->death_mutex);
    pthread_mutex_destroy(&data->print_mutex);
    pthread_mutex_destroy(&data->start);
}

int    cleanup_struct(t_data *data)
{
    printf("before join function\n");
    join_threads(data);
    printf("after join function\n");
    destroy_mutex(data);
    printf("after mutex function\n");
    if (data->philos)
        free(data->philos);
    if (data->threads)
        free(data->threads);
    printf("clean end function\n");
    return (0);
}