/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 13:14:59 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/20 16:13:31 by armosnie         ###   ########.fr       */
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
	print_routine(philo, "has taken a fork...", "\033[39m");
	pthread_mutex_lock(second);
	print_routine(philo, "has taken a fork...", "\033[39m");
}

void	eat(t_philo *philo)
{
	// pthread_mutex_lock(&philo->data->death_mutex);
	// if (philo->data->meals_required != 0)
	// {
	//     if (all_ate_enough(philo->data) == 1)
	//     {
	//         philo->data->someone_died = 1;
	//         pthread_mutex_unlock(&philo->data->death_mutex);
	//         return ;
	//     }
	// }
	// if (death_by_starvation(philo) == 1)
	// {
	// 	philo->data->someone_died = 1;
	// 	pthread_mutex_unlock(&philo->data->death_mutex);
	// 	return ;
	// }
	// pthread_mutex_unlock(&philo->data->death_mutex);
	pthread_mutex_lock(&philo->meal_time);
	print_routine(philo, "is eating...", "\033[36m");
	philo->meals_eaten++;
	philo->last_meal_time = get_current_time(philo->data);
	pthread_mutex_unlock(&philo->meal_time);
	usleep(philo->data->time_to_eat * 1000);
}

void	drop_forks(t_philo *philo)
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
	pthread_mutex_unlock(first);
	pthread_mutex_unlock(second);
}

void	think(t_philo *philo)
{
	print_routine(philo, "is thinking", "\033[34m");
	usleep(philo->data->time_to_eat * 1000);
}

void	sleep_philo(t_philo *philo)
{
	print_routine(philo, "is sleeping", "\033[35m");
	usleep(philo->data->time_to_sleep * 1000);
}