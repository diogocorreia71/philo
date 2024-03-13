#include "philo.h"

int	data_init(t_global_var *data, char **argv)
{
	data->nbr_phils = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->end = 0;
	if (argv[5])
		data->nbr_meals = ft_atoi(argv[5]);
	else
		data->nbr_meals = -2;
	if (data->nbr_phils < 0 || data->time_to_die < 0
		|| data->time_to_eat < 0 || data->time_to_sleep < 0
		|| data->nbr_meals == -1)
	{
		printf("Invalid Arguments\n");
		return (-1);
	}
	return (0);
}

int	philo_init(t_philo **philo, t_global_var *data)
{
	int	i;

	i = 0;
	*philo = (t_philo *)malloc(sizeof(t_philo) * data->nbr_phils);
	if (*philo == NULL)
		return (-1);
	data->forks = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * data->nbr_phils);
	if (data->forks == NULL)
		return (-1);
	while (i < data->nbr_phils)
	{
		memset((void *)&(*philo)[i], 0, sizeof(t_philo));
		(*philo)[i].data = data;
		(*philo)[i].philo_id = i + 1;
		i++;
	}
	data->all = *philo;
	return (0);
}