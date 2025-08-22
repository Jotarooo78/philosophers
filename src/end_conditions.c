/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_conditions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:30:47 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/22 11:59:08 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	death_by_starvation(t_philo *philo, int i)
{
	long last_meal;
	
	pthread_mutex_lock(&philo[i].meal_time);
	last_meal = get_time_last_meal(philo);
	if (last_meal >= philo->data->time_to_die)
	{
		print_status(&philo[i], "died", "\033[31m");
		// printf("last meal : %ld\n", philo[i].last_meal_time);
		pthread_mutex_lock(&philo->data->death_mutex);
		philo->data->is_over = 1;
		pthread_mutex_unlock(&philo->data->death_mutex);
		pthread_mutex_unlock(&philo[i].meal_time);
		return (1);
	}
	pthread_mutex_unlock(&philo[i].meal_time);
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
	}
}
