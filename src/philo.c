/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:30:34 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/25 12:21:42 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_status(t_philo *philo, char *action, char *color)
{
	long	time;

	time = (get_current_time(philo->data));
	if (simulation_done(philo) == 1)
		return ;
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%s%ld %d %s\n", color, time, philo->id, action);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int	simulation_done(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->is_over == 1)
	{
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
	return (0);
}

void	*rountine_philos(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->start);
	pthread_mutex_unlock(&philo->data->start);
	if (philo->id % 2 == 0)
		usleep(100);
	while (simulation_done(philo) == 0)
	{
		take_forks(philo);
		if (simulation_done(philo) == 1)
		{
			drop_forks(philo);
			break ;
		}
		eat(philo);
		drop_forks(philo);
		if (simulation_done(philo) == 1)
			break ;
		sleep_philo(philo);
		if (simulation_done(philo) == 1)
			break ;
		think(philo);
	}
	return (NULL);
}
