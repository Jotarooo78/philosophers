/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 16:28:03 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/22 18:13:30 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int    determine_priority(int n)
{
    if (n % 2 == 0)
        return (0);
    return (1); 
}

int	routine_alone(t_data *data)
{
	if (data->nb_philos == 1)
	{
		printf("\033[39m%ld philo %d has taken a fork\n", get_current_time(data), data->philos->id);
		usleep(data->time_to_die);
	}
	return (0);
}