/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:05:37 by armosnie          #+#    #+#             */
/*   Updated: 2025/08/21 10:45:09 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *nbr)
{
	char	*nb;
	int		i;
	int		res;
	int		neg;

	nb = (char *)nbr;
	i = 0;
	res = 0;
	neg = 1;
	while ((nb[i] >= 9 && nb[i] <= 13) || nb[i] == 32)
		i++;
	if (nb[i] == '-' || nb[i] == '+')
	{
		if (nb[i] == '-')
			neg *= -1;
		i++;
	}
	while (nb[i] >= '0' && nb[i] <= '9')
	{
		res = (res * 10) + nb[i] - '0';
		i++;
	}
	return (res * neg);
}

int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

int	arg_verif(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5)
		return (printf("not enough arg\n"), 1);
	else if (argc > 6)
		return (printf("too many arg\n"), 1);
	while (argv[i])
	{
		if (is_digit(argv[i]) == 1)
			return (printf("incorrect arg format\n"), 1);
		i++;
	}
	return (0);
}

int	parameters_check(t_data *data, char **argv)
{
	if (argv[5])
	{
		if (data->meals_required < 1)
			return (1);
	}
	if (data->nb_philos < 1 || data->time_to_die < 1 || data->time_to_eat < 1
		|| data->time_to_sleep < 1)
		return (1);
	return (0);
}
