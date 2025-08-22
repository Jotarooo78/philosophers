// ## 1. Correction de src/routine.c

//Remplacez la fonction `take_forks` pour gérer le cas d'un seul philosophe et vérifier is_over :

#include "philosophers.h"

void	take_forks(t_philo *philo)
{
	if (simulation_done(philo) == 1)
		return ;
	
	// Cas spécial : un seul philosophe ne peut pas manger
	if (philo->right_f == NULL)
	{
		pthread_mutex_lock(philo->left_f);
		print_status(philo, "has taken a fork...", "\033[39m");
		// Il va mourir car il ne peut pas prendre la deuxième fourchette
		usleep(philo->data->time_to_die * 1000);
		pthread_mutex_unlock(philo->left_f);
		return;
	}
	
	if (determine_priority(philo->id))
	{
		pthread_mutex_lock(philo->left_f);
		if (simulation_done(philo) == 1)
		{
			pthread_mutex_unlock(philo->left_f);
			return;
		}
		print_status(philo, "has taken a fork...", "\033[39m");
		pthread_mutex_lock(philo->right_f);
		if (simulation_done(philo) == 1)
		{
			pthread_mutex_unlock(philo->left_f);
			pthread_mutex_unlock(philo->right_f);
			return;
		}
		print_status(philo, "has taken a fork...", "\033[39m");
	}
	else
	{
		pthread_mutex_lock(philo->right_f);
		if (simulation_done(philo) == 1)
		{
			pthread_mutex_unlock(philo->right_f);
			return;
		}
		print_status(philo, "has taken a fork...", "\033[39m");
		pthread_mutex_lock(philo->left_f);
		if (simulation_done(philo) == 1)
		{
			pthread_mutex_unlock(philo->right_f);
			pthread_mutex_unlock(philo->left_f);
			return;
		}
		print_status(philo, "has taken a fork...", "\033[39m");
	}
}

//Modifiez aussi `drop_forks` pour gérer le cas NULL :

void	drop_forks(t_philo *philo)
{
	if (philo->right_f == NULL)
	{
		if (philo->left_f)
			pthread_mutex_unlock(philo->left_f);
		return;
	}
	
	if (determine_priority(philo->id))
	{
		pthread_mutex_unlock(philo->left_f);
		pthread_mutex_unlock(philo->right_f);
	}
	else
	{
		pthread_mutex_unlock(philo->right_f);
		pthread_mutex_unlock(philo->left_f);
	}
}

// ## 2. Correction de src/philo.c

//Modifiez la fonction `rountine_philos` pour s'assurer que les fourchettes sont toujours relâchées :

void	*rountine_philos(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	
	// Attendre le signal de départ
	pthread_mutex_lock(&philo->data->start);
	pthread_mutex_unlock(&philo->data->start);
	
	// Décalage pour les philosophes pairs pour éviter que tous prennent les fourchettes en même temps
	if (philo->id % 2 == 0)
		usleep(100);
	
	while (simulation_done(philo) == 0)
	{
		take_forks(philo);
		if (simulation_done(philo) == 1)
			break;
		
		// Vérifier si on a pu prendre les deux fourchettes
		if (philo->right_f != NULL)
		{
			eat(philo);
			drop_forks(philo);
		}
		
		if (simulation_done(philo) == 1)
			break;
		sleep_philo(philo);
		if (simulation_done(philo) == 1)
			break;
		think(philo);
	}
	return (NULL);
}

// ## 3. Correction de src/main.c

// Modifiez `init_threads` pour mieux gérer le mutex de démarrage :

void	init_threads(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->start);
	while (i < data->nb_philos)
	{
		if (pthread_create(&data->threads[i], NULL, &rountine_philos,
				&data->philos[i]) != 0)
		{
			pthread_mutex_lock(&data->death_mutex);
			data->is_over = 1;
			pthread_mutex_unlock(&data->death_mutex);
			pthread_mutex_unlock(&data->start);
			while (--i >= 0)
				pthread_join(data->threads[i], NULL);
			return ;
		}
		i++;
	}
	// Donner le signal de départ à tous les threads
	pthread_mutex_unlock(&data->start);
}

// ## 4. Correction de src/end_conditions.c

// Améliorez la fonction `death_by_starvation` :

int	death_by_starvation(t_philo *philo, int i)
{
	long last_meal;
	long time;
	
	pthread_mutex_lock(&philo[i].meal_time);
	last_meal = get_time_last_meal(&philo[i]);
	pthread_mutex_unlock(&philo[i].meal_time);
	
	if (last_meal >= philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->death_mutex);
		if (philo->data->is_over == 0)
		{
			philo->data->is_over = 1;
			pthread_mutex_unlock(&philo->data->death_mutex);
			
			time = get_current_time(philo->data);
			pthread_mutex_lock(&philo->data->print_mutex);
			printf("\033[31m%ld philo %d died\n", time, philo[i].id);
			pthread_mutex_unlock(&philo->data->print_mutex);
			return (1);
		}
		pthread_mutex_unlock(&philo->data->death_mutex);
		return (1);
	}
	return (0);
}

// ## 5. Correction de src/time_functions.c

// Corrigez la fonction `get_time_last_meal` :

long 	get_time_last_meal(t_philo *philo)
{
	long current;
	
	current = get_current_time(philo->data);
	if (philo->last_meal_time == 0)
		return (current);  // Retourner le temps écoulé depuis le début
	return (current - philo->last_meal_time);
}

// ## 6. Ajout dans src/errors.c

// Assurez-vous que le mutex start est bien détruit :

int    destroy_mutex(t_data *data)
{
    int i;

    i = 0;
    if (data->forks)
    {
        while (i < data->nb_philos)
        {
            if (data->forks)
            {
                pthread_mutex_destroy(&data->forks[i]);
                pthread_mutex_destroy(&data->philos[i].meal_time);
                pthread_mutex_destroy(&data->philos[i].meal_total);
            }
            i++;
        }
        free(data->forks);
    }
    pthread_mutex_destroy(&data->start);
    pthread_mutex_destroy(&data->death_mutex);
    pthread_mutex_destroy(&data->print_mutex);
    return (0);
}

// ## Points clés des corrections :

// 1. **Gestion du cas d'un seul philosophe** : Un philosophe seul ne peut pas manger et mourra.

// 2. **Vérification de `simulation_done()` après chaque prise de mutex** : Pour éviter de rester bloqué avec des mutex verrouillés.

// 3. **Libération systématique des mutex** : Avant chaque return dans les fonctions critiques.

// 4. **Synchronisation du démarrage** : Utilisation correcte du mutex `start` pour que tous les philosophes commencent en même temps.

// 5. **Décalage des philosophes pairs** : Pour éviter que tous essaient de prendre les fourchettes simultanément.

// Ces corrections devraient résoudre le problème des threads qui sortent en tenant des locks et éliminer les deadlocks.