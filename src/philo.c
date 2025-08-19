/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:30:34 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/19 17:18:07 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
	{
		perror("");
		return (1);
	}
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_routine(t_philo *philo, char *action)
{
	long	time;

	time = (get_time() - philo->data->start_time);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %d %s\n", time, philo->id, action);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int	simulation_done(t_philo *philos)
{
	int	i;

	i = 0;
	philos->data->all_ate_enough = 0;
	while (i < philos->data->nb_philos)
	{
		if (philos[i].meals_eaten == philos->data->meals_required)
			philos->data->all_ate_enough++;
		if (philos[i].last_meal_time > 0 && (get_time()
				- philos[i].last_meal_time) > philos->data->time_to_die)
		{
			philos->data->someone_died = 1;
			pthread_mutex_lock(&philos->data->death_mutex);
			print_routine(philos, "died");
			return (1);
		}
		i++;
	}
	if (philos->data->meals_required > 0
		&& philos->data->all_ate_enough == philos->data->nb_philos)
	{
		return (1);
	}
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
		take_forks(philo);
		eat(philo);
		think(philo);
		drop_forks(philo);
		sleep_philo(philo);
		i++;
	}
	return (NULL);
}
