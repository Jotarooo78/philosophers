/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 16:30:34 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/19 14:10:24 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
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

int	simulation_done(t_data *data)
{
	int	i;

	i = 0;
	data->all_ate_enough = 0;
	while (i < data->nb_philos)
	{
		if (data->philos[i].meals_eaten == data->meals_required)
			data->all_ate_enough++;
        if (data->someone_died == 1)
            return (1);
		i++;
	}
    if (data->all_ate_enough == data->nb_philos)
        return (1);
	return (0);
}

void	*rountine_philos(void *arg)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *)arg;
	i = 0;
	while (1 && philo->data->start == 0)
		;
	while (simulation_done(philo) == 0)
	{
		take_forks(philo);
		eat(philo);
		think(philo);
		drop_forks(philo);
		sleep_philo(philo);
		i++;
	}
}
