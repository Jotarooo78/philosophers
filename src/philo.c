/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:30:34 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/21 14:47:59 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


void	print_status(t_philo *philo, char *action, char *color)
{
	long	time;

	pthread_mutex_lock(&philo->data->print_mutex);
	time = (get_current_time(philo->data));
	printf("%s%ld philo %d %s\n", color, time, philo->id, action);
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
	int		i;
	t_philo	*philo;

	philo = (t_philo *)arg;
	i = 0;
	while (philo->data->start == 0)
		;
	while (simulation_done(philo) == 0)
	{
		take_forks(philo);
		eat(philo);
		drop_forks(philo);
		if (simulation_done(philo) == 0)
			sleep_philo(philo);
		if (simulation_done(philo) == 0)
			think(philo);			
		i++;
	}
	return (NULL);
}

