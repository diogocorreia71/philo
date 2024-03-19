/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diodos-s <diodos-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 12:00:31 by diodos-s          #+#    #+#             */
/*   Updated: 2024/03/19 12:08:47 by diodos-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_alive(t_global_var *data)
{
	pthread_mutex_lock(&data->philo_dead);
	if (data->end == 1)
	{
		pthread_mutex_unlock(&data->philo_dead);
		return (1);
	}
	pthread_mutex_unlock(&data->philo_dead);
	return (0);
}

int	philo_take_forks(t_philo *philo)
{
	if (check_alive(philo->data))
		return (1);
	if (!(philo->philo_id % 2))
	{
		pthread_mutex_lock(&(philo->data->forks
			[philo->philo_id % philo->data->nbr_phils]));
		if (!check_alive(philo->data))
			put_msg(philo, 'R');
		pthread_mutex_lock(&(philo->data->forks[philo->philo_id - 1]));
		if (!check_alive(philo->data))
			put_msg(philo, 'L');
	}
	else
	{
		pthread_mutex_lock(&(philo->data->forks[philo->philo_id - 1]));
		if (!check_alive(philo->data))
			put_msg(philo, 'L');
		pthread_mutex_lock(&(philo->data->forks
			[philo->philo_id % philo->data->nbr_phils]));
		if (!check_alive(philo->data))
			put_msg(philo, 'R');
	}
	return (0);
}

int	philo_eat(t_philo *philo)
{
	if (check_alive(philo->data))
	{
		pthread_mutex_unlock(&(philo->data->forks[philo->philo_id - 1]));
		pthread_mutex_unlock(&(philo->data->forks
			[philo->philo_id % philo->data->nbr_phils]));
		return (1);
	}
	put_msg(philo, 'E');
	pthread_mutex_lock(&philo->data->last_eat_lock);
	philo->last_eat = start_time();
	pthread_mutex_unlock(&philo->data->last_eat_lock);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_lock(&philo->data->meals_nbr_lock);
	philo->meals_nbr++;
	pthread_mutex_unlock(&philo->data->meals_nbr_lock);
	pthread_mutex_unlock(&(philo->data->forks[philo->philo_id - 1]));
	pthread_mutex_unlock(&(philo->data->forks
		[philo->philo_id % philo->data->nbr_phils]));
	return (0);
}

int	philo_think_sleep(t_philo *philo)
{
	if (check_alive(philo->data))
		return (1);
	put_msg(philo, 'S');
	if (check_alive(philo->data))
		return (1);
	usleep(philo->data->time_to_sleep * 1000);
	if (check_alive(philo->data))
		return (1);
	put_msg(philo, 'T');
	return (0);
}

void	*thread_start(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo->philo_id % 2)
			usleep(4000);
		if (philo_take_forks(philo))
			break ;
		if (philo_eat(philo))
			break ;
		pthread_mutex_lock(&philo->data->meals_nbr_lock);
		if (philo->data->nbr_meals == philo->meals_nbr)
		{
			pthread_mutex_unlock(&philo->data->meals_nbr_lock);
			break ;
		}
		pthread_mutex_unlock(&philo->data->meals_nbr_lock);
		if (philo_think_sleep(philo))
			break ;
	}
	return (NULL);
}
