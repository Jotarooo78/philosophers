/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:30:34 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/20 15:17:09 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


void	print_routine(t_philo *philo, char *action, char *color)
{
	long	time;

	time = (get_current_time(philo->data));
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%s%ld philo %d %s\n", color, time, philo->id, action);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
// mettre a jour someone_dead;

int	simulation_done(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->someone_died == 1)
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
		usleep(100);
	while (simulation_done(philo) == 0)
	{
		if (simulation_done(philo) == 0)
			take_forks(philo);
		if (simulation_done(philo) == 0)
			eat(philo);
		if (simulation_done(philo) == 0)
			drop_forks(philo);
		if (simulation_done(philo) == 0)
			think_and_sleep(philo, "is sleeping...");
		if (simulation_done(philo) == 0)			
			think_and_sleep(philo, "is thinking...");			
		i++;
	}
	return (NULL);
}

