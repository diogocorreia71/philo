#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_global_var	data;

	if (argc == 5 || argc == 6)
	{
		if (data_init(&data, argv) == -1)
			return (-1);
		if (philo_init(&philo, &data) == -1)
		{
			clean_program(&data, 0);
			return (-1);
		}
		if (mutex_init(&data) == -1)
			return (-1);
		if (data.nbr_phils == 1)
			one_philo(&data);
		else if (thread_init(&data) == -1)
		{
			clean_program(&data, 3);
			return (-1);
		}
	}
	else
		printf("Invalid number of arguments\n");
	return (0);
}