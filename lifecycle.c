#include "philo.h"

void	ft_check_dead(t_philo *philo)
{
	if (ft_get_time() - philo->last_meal_time
		>= philo->data->time_to_die && philo->full == 0)
	{
		philo->data->dead = 1;
		pthread_mutex_lock(&philo->data->print_lock);
		printf("%lu %i died\n",
			ft_get_time() - philo->data->start_time, philo->id);
		pthread_mutex_unlock(&philo->data->print_lock);
		ft_clean_exit(philo->data);
	}
}

void	ft_lock_fork(t_philo *philo)
{
	ft_check_dead(philo);
	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%lu %i has taken a fork\n",
		ft_get_time() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->print_lock);
	pthread_mutex_lock(&philo->next->fork);
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%lu %i has taken a fork\n",
		ft_get_time() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->print_lock);
}

void	ft_eat(t_philo *philo)
{
	ft_check_dead(philo);
	philo->times_eaten++;
	philo->last_meal_time = ft_get_time();
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%lu %i is eating\n",
		ft_get_time() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->print_lock);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->next->fork);
	pthread_mutex_unlock(&philo->fork);
}

void	ft_sleep(t_philo *philo)
{
	ft_check_dead(philo);
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%lu %i is sleeping\n",
		ft_get_time() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->print_lock);
	usleep(philo->data->time_to_sleep * 1000);
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%lu %i is thinking\n",
		ft_get_time() - philo->data->start_time, philo->id);
	pthread_mutex_unlock(&philo->data->print_lock);
}