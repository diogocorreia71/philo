#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t	thread_philo;
	int	philo_id;
	int	meals_nbr;
	int	philo_full;
	long long	last_eat;
	struct s_global_var	*data;
}	t_philo;

typedef struct s_global_var
{
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nbr_meals;
	int	end;
	long long	time_ms;
	int	nbr_phils;
	t_philo	*all;
	pthread_mutex_t	*forks;
	pthread_mutex_t	last_eat_lock;
	pthread_mutex_t meals_nbr_lock;
	pthread_mutex_t	philo_dead;
}	t_global_var;

//init
int	data_init(t_global_var *data, char **argv);
int	philo_init(t_philo **philo, t_global_var *data);

//utils
int	ft_atoi(const char *str);

#endif
