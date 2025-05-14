/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:53:24 by armosnie          #+#    #+#             */
/*   Updated: 2025/05/14 18:53:30 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool arg_verif(int argc, char **argv)
{
	int	i;

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

bool init_philo(pthread_t *thread, t_philo *philo)
{
	philo->id = 0;
	philo->left_f = NULL;
	philo->right_f = NULL;
	if (pthread_create(thread, NULL, &routine, philo) == false)
		return (false);
	return (true);
}

bool	init_data(int argc, char **argv, t_data *data)
{
	t_philo *philo;
	
	data->nb_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->ready = false;
	data->start_time = ;
	data->print_mutex = ;
	data->someone_died = false;
	philo = malloc(sizeof(t_philo) * data->nb_philos);
	if (philo == NULL)
		return (free(data), false);
}

int	main(int argc, char *argv[])
{
    t_data *data;

	if (arg_verif(argc, argv) == false)
		return (false);
	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
	if (init_data(argc, argv, data) == false)
		return (free(data), false);
	
	
}