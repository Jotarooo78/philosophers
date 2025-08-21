/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:14:59 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/21 17:36:27 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *philo)
{
	if (simulation_done(philo) != 0)
		return ;
	if (determine_priority(philo->id))
	{
		pthread_mutex_lock(philo->left_f);
		// print_status(philo, "has taken a fork...", "\033[39m");
		pthread_mutex_lock(philo->right_f);
		// print_status(philo, "has taken a fork...", "\033[39m");
	}
	else
	{
		pthread_mutex_lock(philo->right_f);
		// print_status(philo, "has taken a fork...", "\033[39m");
		pthread_mutex_lock(philo->left_f);
		// print_status(philo, "has taken a fork...", "\033[39m");
	}
}

void	eat(t_philo *philo)
{
	if (simulation_done(philo) != 0)
		return ;
	pthread_mutex_lock(&philo->meal_time);
	// print_status(philo, "is eating...", "\033[36m");
	pthread_mutex_lock(&philo->meal_total);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_total);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->meal_time);
	usleep(philo->data->time_to_eat * 1000);
}

void	drop_forks(t_philo *philo)
{
	if (determine_priority(philo->id))
	{
		pthread_mutex_unlock(philo->left_f);
		pthread_mutex_unlock(philo->right_f);
	}
	else
	{
		pthread_mutex_unlock(philo->right_f);
		pthread_mutex_unlock(philo->left_f);
	}
}

void	think(t_philo *philo)
{
	if (simulation_done(philo) != 0)
		return ;
	// print_status(philo, "is thinking", "\033[34m");
	usleep(philo->data->time_to_sleep * 1000);
}

void	sleep_philo(t_philo *philo)
{
	long start_time;

	start_time = get_time();
	while (1)
	{
		if (simulation_done(philo) != 0)
			return ;
		if ((get_time() - start_time) >= philo->data->time_to_sleep)
			return ;
		usleep(200);
	}
	// print_status(philo, "is sleeping", "\033[35m");
}