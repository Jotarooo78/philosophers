/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_conditions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:30:47 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/25 17:08:26 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	death_by_starvation(t_data *data, int i)
{
	pthread_mutex_lock(&data->philos[i].meal_time);
	if (get_time_last_meal(&data->philos[i]) > data->time_to_die)
	{
		print_status(&data->philos[i], "died", "\033[31m");
		pthread_mutex_lock(&data->death_mutex);
		data->is_over = 1;
		pthread_mutex_unlock(&data->death_mutex);
		pthread_mutex_unlock(&data->philos[i].meal_time);
		return (1);
	}
	pthread_mutex_unlock(&data->philos[i].meal_time);
	return (0);
}

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
	int		i;

	while (1)
	{
		i = 0;
		if (data->is_over == 1)
			return ;
		while (i < data->nb_philos)
		{
			if (death_by_starvation(data, i))
				i++;
		}
		if (argv[5] && all_ate_enough(data->philos) != 0)
			return ;
		// loop_count++;
		usleep(500); // Vérifier toutes les 1ms
	}
}

	// int		loop_count;
	// long	last_print;
	// long	current_time;
	// long	time_since_meal;

	// loop_count = 0;
	// last_print = 0;
	// if (data->nb_philos == 1)
	// {
	// 	while (get_current_time(data) < data->time_to_die)
	// 		usleep(1000);
	// 	print_status(data->philos, "died", "\033[31m");
	// 	pthread_mutex_lock(&data->death_mutex);
	// 	data->is_over = 1;
	// 	pthread_mutex_unlock(&data->death_mutex);
	// 	return ;
	// }
	// usleep(5000);

	// current_time = get_current_time(data);
	// 	// Debug toutes les 100ms
	// 	if (current_time - last_print >= 100)
	// 	{
	// 		printf("[MONITOR] Time: %ld, Checking %d philosophers\n",
	// 			current_time, data->nb_philos);
	// 		last_print = current_time;
	// 	}

				// pthread_mutex_lock(&data->philos[i].meal_time);
			// time_since_meal = get_time_last_meal(&data->philos[i]);
			// // Si proche de la mort, afficher plus de détails
			// if (time_since_meal >= data->time_to_die - 5)
			// {
			// 	printf("[CRITICAL] Philo %d: time_since_meal=%ld (limit=%ld)\n",
			// 		data->philos[i].id, time_since_meal, data->time_to_die);
			// }
			// if (time_since_meal >= data->time_to_die)
			// {
			// 	pthread_mutex_unlock(&data->philos[i].meal_time);
			// 	print_status(&data->philos[i], "died", "\033[31m");
			// 	pthread_mutex_lock(&data->death_mutex);
			// 	data->is_over = 1;
			// 	pthread_mutex_unlock(&data->death_mutex);
			// 	return ;
			// }
			// pthread_mutex_unlock(&data->philos[i].meal_time);
