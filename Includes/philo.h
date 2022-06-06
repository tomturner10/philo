#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <string.h>

typedef struct s_philo
{
	int				id;
	int				times_eaten;
	unsigned long	last_meal_time;
	int				full;
	struct s_data	*data;
	struct s_philo	*next;
	pthread_mutex_t	fork;
	pthread_t		thread;
}			t_philo;

typedef struct s_data {
	int				number_of_philo;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	int				number_of_times_philo_must_eat;
	t_philo			*philo;
	unsigned long	start_time;
	int				dead;
	pthread_mutex_t	print_lock;
}			t_data;

int				ft_atoi(const char *nptr);
int				ft_valid_args(int argc, char **argv);
void			ft_init_philos(t_data *data);
void			ft_init_data(t_data *data, char **argv);
void			ft_start(t_data *data);
void			ft_clean_exit(t_data *data);
unsigned long	ft_get_time(void);
void			*philosopher(void *voidPhilo);
void			ft_check_dead(t_philo *philo);
void			ft_lock_fork(t_philo *philo);
void			ft_eat(t_philo *philo);
void			ft_sleep(t_philo *philo);

#endif
