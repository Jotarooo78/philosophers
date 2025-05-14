/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:30:34 by armosnie          #+#    #+#             */
/*   Updated: 2025/05/14 18:53:50 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"



long get_time(t_data *data)
{
    struct timeval tv;
    time_t curtime;
    
    gettimeofday(&tv, NULL);
    curtime = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    return (curtime - data->start_time);
}

