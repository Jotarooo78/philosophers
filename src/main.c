/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:53:24 by armosnie          #+#    #+#             */
/*   Updated: 2025/05/16 16:43:18 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool init_mutex(t_data *data, t_philo *philo, int i)
{
	while (i < data->nb_philos)
	{
		if (init_philo(&philo[i], i) == false)
			return (ft_putstr_fd("init philo struct failed\n", 1), false);
		i++;
	}
	return (true);
}

bool	init_philo(t_philo *philo, int i)
{
	philo->id = i;
	if (pthread_create(&philo->thread, NULL, &routine, &philo[i])!= 0)
		return (false);
	if (pthread_create(&philo->left_f, NULL, &routine, &philo[i])!= 0)
		return (false);
	if (pthread_create(&philo->right_f, NULL, &routine, &philo[i])!= 0)
		return (false);
	return (true);
}

bool	init_data(int argc, char **argv, t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	data->nb_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->ready = false;
	data->death = false;
	philo = malloc(sizeof(t_philo) * data->nb_philos);
	if (philo == NULL)
		return (free(data), false);
	if (init_mutex(data, philo, i)== false)
		return (ft_putstr_fd("init mutex struct failed\n", 1), false);
	if (parameters_check(data) == false)
		return (ft_putstr_fd("invalid arg\n", 1), false);
	return (true);
}

int	main(int argc, char *argv[])
{
	t_data	*data;

	if (arg_verif(argc, argv) == false)
		return (false);
	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
	if (init_data(argc, argv, data) == false)
		return (free(data), false);
	data->ready = true;
}

// mutex print_mutex

// comment les setup ?