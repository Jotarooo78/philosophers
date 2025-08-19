/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:53:24 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/19 10:46:05 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_data *data;
	
	if (arg_verif(argc, argv) == 1)
		return (1);
	data = init_all_struct(argc, argv);
	if (data == NULL)
		return (cleanup_struct(data), 1);
	return (cleanup_struct(data), 0);
}
