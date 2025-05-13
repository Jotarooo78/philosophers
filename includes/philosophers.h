#ifndef PHILOSOPHERS
# define PHILOSOPHERS

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_philo
{
	int				id;
	long			timestamp;
	int				meals_eaten;
	pthread_t		thread;
	pthread_mutex_t	*left_f;
	pthread_mutex_t	*right_f;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				nb_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	int				someone_died;
	t_philo			*philos;
}					t_data;

#endif