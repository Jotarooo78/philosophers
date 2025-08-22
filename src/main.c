/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:53:24 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/22 18:28:33 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	usleep(200);
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
	if (routine_alone(&data) == 1)
		return (0);
	init_threads(&data);
	check_is_over(&data, argv);
	return (cleanup_struct(&data));
}
