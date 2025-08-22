/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_conditions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:30:47 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/22 14:05:46 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	death_by_starvation(t_philo *philo, int i)
{
	long last_meal;
	long time;
	
	pthread_mutex_lock(&philo[i].meal_time);
	last_meal = get_time_last_meal(&philo[i]);
	pthread_mutex_unlock(&philo[i].meal_time);
	if (last_meal >= philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->is_over == 0)
		{
			philo->data->is_over = 1;
			pthread_mutex_unlock(&philo->data->death_mutex);
			time = get_current_time(philo->data);
			pthread_mutex_lock(&philo->data->print_mutex);
			printf("\033[31m%ld philo %d died\n", time, philo[i].id);
			pthread_mutex_unlock(&philo->data->print_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philo->data->death_mutex);
		// printf("last meal : %ld\n", philo[i].last_meal_time);
		return (1);
	}
	return (0);
}

// int	death_by_starvation(t_philo *philo, int i)
// {
// 	(void)philo;
// 	i = 0;
// 	return (0);
// }

int	all_ate_enough(t_philo *philo)
{
	int	i;
	int	all_ate_enough;

	all_ate_enough = 0;
	i = 0;
	while (i < philo->data->nb_philos)
	{
		pthread_mutex_lock(&philo[i].meal_total);
		if (philo[i].meals_eaten >= philo->data->meals_required)
			all_ate_enough++;
		pthread_mutex_unlock(&philo[i].meal_total);
		i++;
	}
	if (all_ate_enough == philo->data->nb_philos)
	{
		print_status(philo, "all ate enough", "\033[31m");
		pthread_mutex_lock(&philo->data->death_mutex);
		philo->data->is_over = 1;
		pthread_mutex_unlock(&philo->data->death_mutex);
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
		usleep(1000);
	}
}
