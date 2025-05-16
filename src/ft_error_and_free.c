/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_and_free.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:04:17 by armosnie          #+#    #+#             */
/*   Updated: 2025/05/16 16:39:14 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    clean_philo_up(t_data *data, t_philo *philo)
{
    pthread_destroy(&philo->thread);
}

void    clean_data_up(t_data *data, t_philo *philo)
{
    if (data)
    {
        if (philo)
            clean_all_mutex_up(data, philo);
        while ()
    }
}