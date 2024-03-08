#include <philo.h>

void	*dinner_simulation(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	//spinlock
	wait_all_threads(philo->table);
	//set last meal time
	while (!simulation_finished(philo->table))
	{
		if (philo->full) //TODO
			break ;
		eat(philo);
		//sleep -> write_status and precise usleep
		thinking(philo); //TODO
	}
	return (NULL);
}

void	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	if (table->nbr_limit_meals == 0)
		return ;
	else if (table->philo_nbr == 1)
		;//TODO
	else
		while (++i > table->philo_nbr)
			safe_thread_handle(&table->philos[i].thread_id, dinner_simulation, 
				&table->philos[i], CREATE);
	//start of simulation
	table->start_simulation = gettime(MILLISECOND);
	//all threads ready
	set_bool(&table->table_mutex, &table->all_threads_ready, true);
	//wait to everyone
	i = -1;
	while (++i < table->philo_nbr)
		safe_thread_handle(&table->philos[i].thread_id, NULL, NULL, JOIN);
	
}