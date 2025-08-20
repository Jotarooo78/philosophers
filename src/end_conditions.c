/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_conditions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:30:47 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/20 18:25:56 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	death_by_starvation(t_philo *philo)
{
	if (philo->data->is_over == 1)
		return (1);
	pthread_mutex_lock(&philo->meal_time);
	if (philo->last_meal_time >= philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
        printf("starve\n");
		print_status(philo, "died", "\033[31m");
		philo->data->is_over = 1;
		pthread_mutex_unlock(&philo->data->death_mutex);
		pthread_mutex_unlock(&philo->meal_time);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_time);
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
    pthread_mutex_lock(&philo->meal_time);
	while (i < philo->data->nb_philos)
	{
		if (philo[i].meals_eaten >= philo->data->meals_required)
			all_ate_enough++;
		i++;
	}
	if (all_ate_enough == philo->data->nb_philos)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
        printf("ate : %d\n", all_ate_enough);
		print_status(philo, "died", "\033[31m");
		philo->data->is_over = 1;
		pthread_mutex_unlock(&philo->data->death_mutex);
        pthread_mutex_unlock(&philo->meal_time);
		return (1);
	}
	pthread_mutex_unlock(&philo->meal_time);
	return (0);
}

void	check_is_over(t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		if (all_ate_enough(data->philos) != 0)
			return ;
		if (death_by_starvation(data->philos) != 0)
			return ;
	}
}
