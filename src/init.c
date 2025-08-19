/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 13:39:46 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/19 16:11:10 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (!data->forks)
		return (1);
	while (i < data->nb_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			while (i > 0)
			{
				pthread_mutex_destroy(&data->forks[i]);
				i--;
				return (1);
			}
		i++;
	}
	if (pthread_mutex_init(&data->death_mutex, NULL) != 0)
		return (pthread_mutex_destroy(&data->death_mutex), 1);
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (pthread_mutex_destroy(&data->print_mutex), 1);
	return (0);
}

int	init_threads(t_data *data)
{
	int	i;

	i = 0;
	data->threads = malloc(sizeof(pthread_t) * data->nb_philos);
	if (!data->threads)
		return (1);
	while (i < data->nb_philos)
	{
		if (pthread_create(&data->threads[i], NULL, &rountine_philos,
				&data->philos[i]) != 0)
		{
			data->someone_died = 1;
			while (i > 0)
			{
				pthread_join(data->threads[i], NULL);
				i--;
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	data->philos = malloc(sizeof(t_philo) * data->nb_philos);
	if (data->philos == NULL)
		return (1);
	while (i < data->nb_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].meals_eaten = 0;
		data->philos[i].last_meal_time = 0;
		data->philos[i].data = data;
		data->philos[i].left_f = &data->forks[i];
		data->philos[i].right_f = &data->forks[(i + 1) % data->nb_philos];
		i++;
	}
	return (0);
}

t_data	*init_data(char **argv)
{
	int		i;
	t_data	*data;

	i = 0;
	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
	data->nb_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->meals_required = ft_atoi(argv[5]);
    data->start = 0;
	data->someone_died = 0;
	if (parameters_check(data) != 0)
		return (NULL);
	return (data);
}

t_data	*init_all_struct(char **argv)
{
	t_data	*data;

	data = init_data(argv);
	if (data == NULL)
		return (NULL);
	if (parameters_check(data) == 1)
		return (printf("invalid args\n"), data->init_success = 0, data);
	if (init_philosophers(data) != 0)
		return (printf("philo alloc failed\n"), data->init_success = 0,
			data);
	if (init_mutex(data) != 0)
		return (printf("mutex alloc failed\n"), data->init_success = 0,
			data);
    data->init_success = 1;
	return (data);
}
