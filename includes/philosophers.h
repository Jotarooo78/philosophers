#ifndef PHILOSOPHERS
# define PHILOSOPHERS

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	int				last_meal_time;
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
	long			meals_required;
	int				someone_died;
	int				all_ate_enough;
	int				init_success;
	int				start;
	int				start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	print_mutex;
	pthread_t		*threads;
	t_philo			*philos;
}					t_data;

// init

t_data				*init_all_struct(char **argv);

// philo

void				*rountine_philos(void *arg);
void				print_routine(t_philo *philo, char *action);
long long			get_time(void);

// ft_error_and_free

void				cleanup_struct(t_data *data);

// utils

int					ft_atoi(const char *nbr);
void				ft_putstr_fd(char *s, int fd);
int					is_digit(char *str);
int					arg_verif(int argc, char **argv);
int					parameters_check(t_data *data);

#endif