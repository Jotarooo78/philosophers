/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_conditions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:30:47 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/21 12:06:57 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	death_by_starvation(t_philo *philo, int i)
{
	if (philo->data->is_over == 1)
		return (1);
	pthread_mutex_lock(&philo[i].meal_time);
	printf("p-id %d ; last meal : %ld ; time to die : %ld ; current_time : %ld\n", philo[i].id ,philo[i].last_meal_time, philo->data->time_to_die, get_current_time(philo->data));
	if ((get_current_time(philo->data) - philo[i].last_meal_time) >= philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		print_status(&philo[i], "died", "\033[31m");
		philo->data->is_over = 1;
		pthread_mutex_unlock(&philo->data->death_mutex);
		pthread_mutex_unlock(&philo[i].meal_time);
		return (1);
	}
	pthread_mutex_unlock(&philo[i].meal_time);
	return (0);
}

int	all_ate_enough(t_philo *philo)
{
	int	i;
	int	all_ate_enough;

	all_ate_enough = 0;
	i = 0;
	if (philo->data->is_over == 1)
		return (1);
	while (i < philo->data->nb_philos)
	{
		pthread_mutex_lock(&philo[i].meal_time);
		if (philo[i].meals_eaten >= philo->data->meals_required)
			all_ate_enough++;
		pthread_mutex_unlock(&philo[i].meal_time);
		i++;
	}
	if (all_ate_enough == philo->data->nb_philos)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		print_status(philo, "all ate enough", "\033[31m");
		philo->data->is_over = 1;
		pthread_mutex_unlock(&philo->data->death_mutex);
        pthread_mutex_unlock(&philo[i].meal_time);
		return (1);
	}
	return (0);
}

void	check_is_over(t_data *data, char **argv)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < data->nb_philos)
		{
			if (death_by_starvation(data->philos, i) != 0)
				return ;
			i++;
		}
		if (argv[5])
		{
			if (all_ate_enough(data->philos) != 0)
				return ;
		}
	}
}
