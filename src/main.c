/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:53:24 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/21 11:26:06 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	if (arg_verif(argc, argv) == 1)
		return (1);
	data = init_all_struct(argv);
	if (data->init_success == 0)
		return (cleanup_struct(data), 1);
	data->start_time = get_time();
	data->start = 1;
	if (init_threads(data) != 0)
		return (printf("threads alloc failed\n"), cleanup_struct(data), 1);
	check_is_over(data, argv);
	return (cleanup_struct(data));
}
