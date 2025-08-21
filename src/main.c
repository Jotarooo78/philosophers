/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:53:24 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/21 13:56:24 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philos)
	{
		if (pthread_create(&data->threads[i], NULL, &rountine_philos,
				&data->philos[i]) != 0)
		{
			data->is_over = 1;
			while (i > 0)
			{
				pthread_join(data->threads[i], NULL);
				i--;
				return ;
			}
		}
		i++;
	}
	data->start = 1;
}

int	main(int argc, char **argv)
{
	t_data data;

	if (arg_verif(argc, argv) == 1)
		return (1);
	if (init_all_struct(&data, argv) != 0)
		return (cleanup_struct(&data), 1);
	data.start_time = get_time();
	init_threads(&data);
	check_is_over(&data, argv);
	return (cleanup_struct(&data));
}
