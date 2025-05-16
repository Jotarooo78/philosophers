/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:30:34 by armosnie          #+#    #+#             */
/*   Updated: 2025/05/16 17:26:09 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long get_time(t_data *data)
{
    time_t curtime;
    
    gettimeofday(&data->start_time, NULL);
    curtime = data->start_time.tv_sec * 1000 + data->start_time.tv_usec / 1000;
    return (curtime - (data->start_time));
}

