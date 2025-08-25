/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 16:28:03 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/25 15:35:38 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*routine_alone(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (simulation_done(philo) == 0)
	{
		pthread_mutex_lock(philo->left_f);
		print_status(philo, "has taken a fork", "\033[39m");
		usleep(philo->data->time_to_die * 1000);
		pthread_mutex_unlock(philo->left_f);
	}
	return (NULL);
}

void	alone_philo(t_data *data)
{
	int i;

	i = 0;
	data->start_time = get_time();
	pthread_create(data->threads, NULL, &routine_alone, &data->philos[i]);
}