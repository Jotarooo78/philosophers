/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 11:50:15 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/20 17:54:58 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
	{
		perror("");
		return (1);
	}
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

long get_current_time(t_data *data)
{
    long current;

    current = get_time();
    return (current - data->start_time);
}
