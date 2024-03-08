#include "philo.h"

int main(int argc, char **argv)
{
	t_table table;

	if (argc == 5 || argc == 6)
	{
		//correct
		// check errors and fill table
		parse_input(&table, argv);
		// creating the program
		data_init(&table);
		dinner_start(&table);
		// free mem
		clean(&table);
	}
	else
		error_exit("Wrong input:\n");
}