/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:53:24 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/22 17:50:21 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*rountine_alone_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (simulation_done(philo) == 0)
	{
		printf("routine alone\n");
		pthread_mutex_lock(philo->left_f);
		print_status(philo, "has taken a fork...", "\033[39m");
		pthread_mutex_unlock(philo->left_f);
	}
	while (1)
		usleep(300);
	return (NULL);
}

void	init_threads(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->start);
	if (data->nb_philos > 1)
	{
		while (i < data->nb_philos)
		{
			pthread_create(&data->threads[i], NULL, &rountine_philos,
				&data->philos[i]);
			i++;
		}
	}
	else
		pthread_create(&data->threads[i], NULL, &rountine_alone_philo,
			&data->philos[i]);
	if (data->nb_philos != 1)
		usleep(500);
	pthread_mutex_unlock(&data->start);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (arg_verif(argc, argv) == 1)
		return (1);
	if (init_all_struct(&data, argv) != 0)
		return (cleanup_struct(&data), 1);
	data.start_time = get_time();
	init_threads(&data);
	check_is_over(&data, argv);
	return (cleanup_struct(&data));
}
