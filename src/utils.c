/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:05:37 by armosnie          #+#    #+#             */
/*   Updated: 2025/05/16 12:51:16 by armosnie         ###   ########.fr       */
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

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

bool	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			return (false);
		i++;
	}
	return (true);
}

bool	arg_verif(int argc, char **argv)
{
	int i;

	i = 0;
	if (argc < 5)
		return (ft_putstr_fd("not enough arg\n", 1), false);
	else if (argc > 6)
		return (ft_putstr_fd("too many arg\n", 1), false);
	while (argv[i])
	{
		if (is_digit(argv[i]) == false)
			return (ft_putstr_fd("incorrect arg format\n", 1), false);
		i++;
	}
	return (true);
}

bool	parameters_check(t_data *data)
{
	if (data->nb_philos < 1 || data->time_to_die < 1 || data->time_to_eat < 1
		|| data->time_to_sleep < 1)
	return (false);
}