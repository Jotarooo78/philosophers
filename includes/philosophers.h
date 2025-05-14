#ifndef PHILOSOPHERS
# define PHILOSOPHERS

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <sys/time.h>


typedef struct s_philo
{
	int				id;
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
	long			start_time;
	bool			ready;
	pthread_mutex_t	print_mutex;
	bool			someone_died;
	t_philo			*philos;
}					t_data;

// utils

int					ft_atoi(const char *nbr);
void				ft_putstr_fd(char *s, int fd);
bool				is_digit(char *str);

// ft_error_and_free

#endif