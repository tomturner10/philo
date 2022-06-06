#include "Includes/philo.h"

void	ft_init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philo = (t_philo *)malloc(data->number_of_philo * sizeof(t_philo));
	while (i < data->number_of_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].times_eaten = 0;
		data->philo[i].data = data;
		data->philo[i].full = 0;
		pthread_mutex_init(&data->philo[i].fork, NULL);
		if (i + 1 == data->number_of_philo)
			data->philo[i].next = &data->philo[0];
		else
			data->philo[i].next = &data->philo[i + 1];
		i++;
	}
}

void	ft_init_data(t_data *data, char **argv)
{
	memset(data, 0, sizeof(t_data));
	data->number_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->dead = 0;
	if (argv[5] != NULL)
		data->number_of_times_philo_must_eat = ft_atoi(argv[5]);
	else
		data->number_of_times_philo_must_eat = -1;
	pthread_mutex_init(&data->print_lock, NULL);
	ft_init_philos(data);
}

void	*philosopher(void *voidPhilo)
{
	t_philo	*philo;

	philo = (t_philo *)voidPhilo;
	philo->last_meal_time = ft_get_time();
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%i made\n",philo->id);
	pthread_mutex_unlock(&philo->data->print_lock);
	if (philo->id % 2 == 0)
		usleep(philo->data->time_to_eat / 2 * 1000);
	while (philo->data->dead == 0 && philo->times_eaten
		!= philo->data->number_of_times_philo_must_eat)
	{
		ft_lock_fork(philo);
		ft_eat(philo);
		ft_sleep(philo);
	}
	if (philo->times_eaten == philo->data->number_of_times_philo_must_eat)
		philo->full = 1;
	return (NULL);
}

void	ft_start(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = ft_get_time();
	while (i < data->number_of_philo)
	{
		pthread_create(&data->philo[i].thread,
			NULL, &philosopher, &data->philo[i]);
		data->philo[i].last_meal_time = data->start_time;
		i++;
	}
}
