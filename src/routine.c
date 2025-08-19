/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:14:59 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/19 14:25:55 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *philo)
{
	int	first;
	int	second;

	first = philo->left_f;
	second = philo->right_f;
	if (first > second)
	{
		pthread_mutex_lock(philo->right_f);
        print_routine(philo->id, "has taken a fork...");
		pthread_mutex_lock(philo->left_f);
        print_routine(philo->id, "has taken a fork...");
	}
	else
	{
		pthread_mutex_lock(philo->left_f);
        print_routine(philo->id, "has taken a fork...");
		pthread_mutex_lock(philo->right_f);
    	print_routine(philo->id, "has taken a fork...");
	}
}

void	eat(t_philo *philo)
{
	print_routine(philo->id, "is eating...");
	philo->last_meal_time = get_time();
	usleep(philo->data->time_to_eat * 1000);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->forks[philo->id]);
	pthread_mutex_unlock(&philo->data->forks[(philo->id + 1)
		% philo->data->nb_philos]);
}

void	think(t_philo *philo)
{
	print_routine(philo->id, "is thinking...");
}

void	sleep_philo(t_philo *philo)
{
	print_routine(philo->id, "is sleeping...");
	usleep(philo->data->time_to_sleep * 1000);
}