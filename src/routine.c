/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:14:59 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/25 18:05:50 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	take_forks(t_philo *philo)
{
	if (simulation_done(philo) == 1)
		return (1);
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(philo->left_f);
		print_status(philo, "has taken a fork", "\033[39m");
		if (simulation_done(philo) == 1)
			return (pthread_mutex_unlock(philo->left_f), 1);
		pthread_mutex_lock(philo->right_f);
		print_status(philo, "has taken a fork", "\033[39m");
	}
	else
	{
		pthread_mutex_lock(philo->right_f);
		print_status(philo, "has taken a fork", "\033[39m");
		if (simulation_done(philo) == 1)
			return (pthread_mutex_unlock(philo->right_f), 1);
		pthread_mutex_lock(philo->left_f);
		print_status(philo, "has taken a fork", "\033[39m");
	}
	return (0);
}

void	eat(t_philo *philo)
{
	if (simulation_done(philo) == 1)
		return ;
	print_status(philo, "is eating", "\033[36m");
	pthread_mutex_lock(&philo->meal_time);
	philo->last_meal_time = get_current_time(philo->data);
	pthread_mutex_unlock(&philo->meal_time);
	pthread_mutex_lock(&philo->meal_total);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_total);
	usleep(philo->data->time_to_eat * 1000);
}

void	drop_forks(t_philo *philo)
{
	if (philo->id % 2 == 1)
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
	long	time_to_think;

	if (simulation_done(philo) == 1)
		return ;
	print_status(philo, "is thinking", "\033[34m");
	if (philo->data->nb_philos % 2 == 1)
	{
		time_to_think = (philo->data->time_to_eat * 2
				- philo->data->time_to_sleep);
		if (time_to_think < 0)
			time_to_think = 1;
		usleep(time_to_think * 1000);
	}
	else
		usleep(1000);
}

void	sleep_philo(t_philo *philo)
{
	long	start;

	start = get_current_time(philo->data);
	if (simulation_done(philo) == 1)
		return ;
	print_status(philo, "is sleeping", "\033[35m");
	while (1)
	{
		if (simulation_done(philo) == 1)
			return ;
		if (get_current_time(philo->data) - start >= philo->data->time_to_sleep)
			return ;
		usleep(200);
	}
}
