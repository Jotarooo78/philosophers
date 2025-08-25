/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:53:24 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/25 17:07:37 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_threads(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->start);
	// savoir pourquoi on lock start ici et avant la routine
	while (i < data->nb_philos)
	{
		pthread_create(&data->threads[i], NULL, &rountine_philos,
			&data->philos[i]);
		i++;
	}
	usleep(1000);
	data->start_time = get_time();
	pthread_mutex_unlock(&data->start);
	usleep(1000);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (arg_verif(argc, argv) == 1)
		return (1);
	if (init_all_struct(&data, argv) != 0)
		return (cleanup_struct(&data), 1);
	if (data.nb_philos == 1)
		alone_philo(&data);
	else
		init_threads(&data);
	check_is_over(&data, argv);
    printf("main end\n");
	return (cleanup_struct(&data));
}
