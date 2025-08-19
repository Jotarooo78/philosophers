/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:14:59 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/19 17:14:44 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

    if (philo->left_f > philo->right_f)
    {
        first = philo->right_f;
        second = philo->left_f;
    }
    else
    {
	    first = philo->left_f;
	    second = philo->right_f;        
    }
		pthread_mutex_lock(first);
        print_routine(philo, "has taken a fork...");
		pthread_mutex_lock(second);
        print_routine(philo, "has taken a fork...");
}

void	eat(t_philo *philo)
{
	print_routine(philo, "is eating...");
	philo->last_meal_time = get_time();
    philo->meals_eaten++;
	usleep(philo->data->time_to_eat * 1000);
}

void	drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_f);
	pthread_mutex_unlock(philo->right_f);
}

void	think(t_philo *philo)
{
	print_routine(philo, "is thinking...");
}

void	sleep_philo(t_philo *philo)
{
	print_routine(philo, "is sleeping...");
	usleep(philo->data->time_to_sleep * 1000);
}