#include "philo.h"

void	ft_check_death(t_data *data)
{
	int	i;

	i = 0;
	while (!data->dead && i < data->number_of_philo)
	{
		if (ft_get_time() - data->philo[i].last_meal_time >= data->time_to_die)
		{
			data->dead = 1;
			if (data->philo[i].full == 0)
			{
				pthread_mutex_lock(&data->print_lock);
				printf("%lu %i died\n",
					ft_get_time() - data->start_time, data->philo[i].id);
				pthread_mutex_unlock(&data->print_lock);
				ft_clean_exit(data);
			}
		}
		i++;
	}
}

void	ft_status(t_data *data)
{
	int	i;
	int	all_full;

	while (!data->dead)
	{
		i = 0;
		all_full = 1;
		while (i < data->number_of_philo && all_full == 1)
			all_full = data->philo[i++].full;
		if (i == data->number_of_philo - 1)
			ft_clean_exit(data);
		ft_check_death(data);
	}
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	i = 0;
	if (!ft_valid_args(argc, argv))
		return (-1);
	ft_init_data(&data, argv);
	ft_start(&data);
	ft_status(&data);
	while (i < data.number_of_philo)
	{
		pthread_join(data.philo[i].thread, NULL);
		i++;
	}
	ft_clean_exit(&data);
	return (0);
}
