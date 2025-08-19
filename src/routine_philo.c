/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:30:34 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/19 10:51:57 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int simulation_done(t_data *data)
{
    int i;

    i = 0;
    while (i < data->nb_philos)
    {
        if (&data->philos[i])
    }
}

void    rountine_philos(t_data *data)
{
    int i;

    i = 0;
    while (simulation_done(data) == 0)
}
// long long   get_time(t_data *data)
// {
// 	gettimeofday(&data->start_time, NULL);
// 	return ((data->start_time.tv_sec * 1000) - (data->start_time.tv_usec
// 			/ 1000));
// }

// long long   get_elapsed_time(t_data *time)
// {
    
// }

// void    print_mutex(t_philo *philo)
// {
//     pthread_mutex_lock(&philo->data->print_mutex);
//     printf_routine(philo);
//     pthread_mutex_unlock(&philo->data->print_mutex);
// }

// void    printf_routine(t_philo *philo)
// {
//     if (eat(philo) == true)
//         pr
// }