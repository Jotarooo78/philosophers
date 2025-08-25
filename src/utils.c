/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 16:28:03 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/25 12:28:42 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int    determine_priority(int n)
{
    if (n % 2 == 0)
        return (0);
    return (1); 
}

// int	routine_alone(t_data *data)
// {
// 	if (data->nb_philos == 1)
// 	{
// 		printf("\033[39m%ld philo %d has taken a fork\n", get_current_time(data), data->philos->id);
// 		usleep(data->time_to_die);
// 	}
// 	return (0);
// }


	// if (philo->data->nb_philos == 1)
	// {
	// 	pthread_mutex_lock(philo->left_f);
	// 	print_status(philo, "has taken a fork", "\033[39m");
	// }

    // 	if (philo->data->nb_philos == 1)
	// {
	// 	usleep(philo->data->time_to_die * 1000);
	// 	return ;
	// }
    // 	if (philo->data->nb_philos == 1)
	// 	pthread_mutex_unlock(philo->left_f);