#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>
#include <errno.h>

//write function macro
#define DEBUG_MODE	0

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_opcode;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}	t_time_code;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
}	t_philo_status;

typedef pthread_mutex_t t_mtx;

// for compiler
typedef struct s_table t_table;

typedef struct	s_fork
{
	t_mtx	fork;
	int		fork_id;
}	t_fork;

typedef struct	s_philo
{
	int		id;
	long	meals_counter;
	bool	full;
	long	last_meal_time;
	t_fork	*first_fork;
	t_fork	*second_fork;
	pthread_t	thread_id;
	t_mtx	philo_mutex;
	t_table	*table;
}	t_philo;

// command line input
typedef struct s_table
{
	long	philo_nbr;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	nbr_limit_meals;
	long	start_simulation; //keep time
	bool	end_simulation; //check when philo dies or all philos are full
	bool	all_threads_ready; //sychro philos
	long	threads_running_nbr;
	pthread_t	monitor;
	t_mtx	table_mutex; //avoid races while reading from table
	t_mtx	write_mutex;
	t_fork	*forks; //array forks
	t_philo	*philos; //array philos
}	t_table;

// utils
void	error_exit(const char *error);
long	gettime(t_time_code time_code);
void	precise_usleep(long usec, t_table *table);
void	clean(t_table *table);
// parsing
void	parse_input(t_table *table, char **argv);
//safe functions
void	*safe_malloc(size_t bytes);
void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data, t_opcode opcode);
//init
void	data_init(t_table *table);
//lock and unlock
bool	simulation_finished(t_table *table);
long	get_long(t_mtx *mutex, long *value);
void	set_long(t_mtx *mutex, long *dest, long value);
bool	get_bool(t_mtx *mutex, bool *value);
void	set_bool(t_mtx *mutex, bool *dest, bool value);
//synchro utils
void	wait_all_threads(t_table *table);
void	increase_long(t_mtx *mutex, long *value);
bool	all_threads_running(t_mtx *mutex, long *threads, long philo_nbr);
//write
void	write_status(t_philo_status status, t_philo *philo, bool debug);
//dinner
void	dinner_start(t_table *table);
void	*dinner_simulation(void *data);
// monitoring
void	*monitor_dinner(void *data);
