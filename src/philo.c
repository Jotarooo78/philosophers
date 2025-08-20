/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:30:34 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/20 13:13:14 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


void	print_routine(t_philo *philo, char *action)
{
	long	time;

	time = (get_current_time(philo->data)); // probleme avec le temps em ms
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld philo %d %s\n", time, philo->id, action);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int	simulation_done(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	printf("simu\n");
	if (all_ate_enough(philo->data) == 1)
			return (1);
	if (death_by_starvation(philo) == 1)
		return (1);
	if (philo->data->someone_died == 1)
	{	
		pthread_mutex_lock(&philo->data->death_mutex);
		return (1);
	}	
	pthread_mutex_lock(&philo->data->death_mutex);
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
	printf("here\n");
	while (simulation_done(philo) == 0)
	{
		printf("%d\n", philo->data->start);
		take_forks(philo);
		eat(philo);
		think(philo);
		drop_forks(philo);
		sleep_philo(philo);
		i++;
	}
	return (NULL);
}
