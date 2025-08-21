#ifndef PHILOSOPHERS
# define PHILOSOPHERS

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal_time;
	pthread_mutex_t	meal_time;
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
	int				is_over;
	int				start;
	long			start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	print_mutex;
	pthread_t		*threads;
	t_philo			*philos;
}					t_data;

// init

void				init_threads(t_data *data);
int					init_all_struct(t_data *data, char **argv);

// philo

void				*rountine_philos(void *arg);
void				print_status(t_philo *philo, char *action, char *color);

// action

void				take_forks(t_philo *philo);
void				eat(t_philo *philo);
void				drop_forks(t_philo *philo);
void				think(t_philo *philo);
void				sleep_philo(t_philo *philo);

// end conditions

void				check_is_over(t_data *data, char **argv);

// routine utils

long				get_current_time(t_data *data);
long				get_time(void);

// ft_error_and_free

int					cleanup_struct(t_data *data);

// utils

int					ft_atoi(const char *nbr);
int					is_digit(char *str);
int					arg_verif(int argc, char **argv);
int					parameters_check(t_data *data, char **argv);

#endif