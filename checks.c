/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diodos-s <diodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 12:00:05 by diodos-s          #+#    #+#             */
/*   Updated: 2024/03/19 12:00:08 by diodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_all_ate(t_global_var *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->meals_nbr_lock);
	while (i < data->nbr_phils
		&& data->all[i].meals_nbr == data->nbr_meals)
		i++;
	pthread_mutex_unlock(&data->meals_nbr_lock);
	return (i);
}

int	check_philo(t_global_var *data, int *i)
{
	long long tmp;

	while (*i < data->nbr_phils)
	{
		pthread_mutex_lock(&data->meals_nbr_lock);
		if (data->all[*i].meals_nbr != data->nbr_meals)
		{
			pthread_mutex_lock(&data->last_eat_lock);
			tmp = start_time() - data->all[*i].last_eat;
			pthread_mutex_unlock(&data->last_eat_lock);
			if (tmp >= data->time_to_die)
			{
				put_msg(&data->all[*i], 'D');
				pthread_mutex_lock(&data->philo_dead);
				data->end = 1;
				pthread_mutex_unlock(&data->philo_dead);
				pthread_mutex_unlock(&data->meals_nbr_lock);
				return (1);
			}
		}
		pthread_mutex_unlock(&data->meals_nbr_lock);
		*i = *i + 1;
	}
	return (0);
}

void	philo_monitor(t_global_var *data)
{
	int	i;

	while (data->nbr_phils != 1)
	{
		i = 0;
		if (check_philo(data, &i))
			break ;
		if (data->nbr_meals != -2
			&& check_all_ate(data) == data->nbr_phils)
		{
			printf("All philosophers ate\n");
			break ;
		}
	}
	return ;
}
