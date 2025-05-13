/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:53:24 by armosnie          #+#    #+#             */
/*   Updated: 2025/05/13 17:53:38 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	init_struct(int argc, char **argv, t_data *data)
{
	data->nb_philos = argv[1];
	data->time_to_die = argv[2];
	data->time_to_eat = argv[3];
	data->time_to_sleep = argv[4];
	data->must_eat = argv[5];
	data->start_time;
	data->forks;
	data->print_mutex;
	data->someone_died = 0;
	data->philos;
}
int	main(int argc, char *argv[])
{
    t_data *data;

	if (argc > 2 && argc < 7)
	{
        data = mallloc(sizeof(t_data));
        if (data == NULL)
            return (NULL);
		init_struct(argc, argv, data);
	}
	else
		return (printf("wrong number of arg\n"), 1);
}