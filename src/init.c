/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 13:39:46 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/22 13:59:48 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	alloc_struct(t_data *data, char **argv)
{
	int	nb_philo;

	nb_philo = ft_atoi(argv[1]);
	data->philos = malloc(sizeof(t_philo) * nb_philo);
	if (data->philos == NULL)
		return (free(data), 1);
	data->forks = malloc(sizeof(pthread_mutex_t) * nb_philo);
	if (!data->forks)
		return (free(data->forks), free(data), 1);
	data->threads = malloc(sizeof(pthread_t) * nb_philo);
	if (!data->threads)
		return (free(data->threads), free(data->forks), free(data), 1);
	return (0);
}

void	init_mutex(t_data *data)
{
	int i;

	i = 0;
	while (i < data->nb_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		pthread_mutex_init(&data->philos[i].meal_time, NULL);
		pthread_mutex_init(&data->philos[i].meal_total, NULL);
		i++;
	}
	pthread_mutex_init(&data->start, NULL);
	pthread_mutex_init(&data->death_mutex, NULL);
	pthread_mutex_init(&data->print_mutex, NULL);
}

void	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].data = data;
		data->philos[i].last_meal_time = 0;
		data->philos[i].left_f = &data->forks[i];
		if (data->nb_philos == 1)
			data->philos[i].right_f = NULL;
		else
			data->philos[i].right_f = &data->forks[(i + 1) % data->nb_philos];
		data->philos[i].data = data;
		i++;
	}
}

int	init_data(t_data *data, char **argv)
{
	int	i;

	i = 0;
	data->nb_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->meals_required = ft_atoi(argv[5]);
	else
		data->meals_required = 0;
	data->is_over = 0;
	return (0);
}

int	init_all_struct(t_data *data, char **argv)
{
	if (alloc_struct(data, argv) == 1)
		return (printf("alloc failed\n"), 1);
	if (init_data(data, argv) != 0)
		return (printf("init data failed\n"), 1);
	if (parameters_check(data, argv) == 1)
		return (printf("invalid args\n"), 1);
	init_philosophers(data);
	init_mutex(data);
	return (0);
}
