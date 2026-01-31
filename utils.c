/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:46:02 by daniel            #+#    #+#             */
/*   Updated: 2026/01/31 01:32:16 by daniel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

bool	check_dead(t_data *master)
{
	bool	result;

	pthread_mutex_lock (&master->mutexes.death_lock);
	if (master->rules.death_id != -1)
		result = true;
	else
		result = false;
	pthread_mutex_unlock (&master->mutexes.death_lock);
	return (result);
}

bool	eat_limit_reached(t_data *master)
{
	int	i;

	i = 0;
	pthread_mutex_lock (&master->mutexes.eat_lock);
	while (i < master->rules.philo_count)
	{
		if (master->philos[i].eat_limit == false)
			break ;
		i++;
	}
	if (i == master->rules.philo_count)
	{
		pthread_mutex_lock (&master->mutexes.death_lock);
		master->rules.death_id = 1;
		pthread_mutex_unlock (&master->mutexes.death_lock);
		pthread_mutex_unlock (&master->mutexes.eat_lock);
		return (true);
	}
	pthread_mutex_unlock (&master->mutexes.eat_lock);
	return (false);
}

bool	death_detector(t_data *master)
{
	int	i;

	i = 0;
	while (i < master->rules.philo_count)
	{
		pthread_mutex_lock (&master->mutexes.eat_lock);
		if (get_time() - master->philos[i].t_lastmeal > master->rules.t_die)
		{
			pthread_mutex_lock (&master->mutexes.death_lock);
			master->rules.death_id = master->philos[i].philo_id;
			pthread_mutex_lock (&master->mutexes.write_lock);
			printf ("%d %d died\n", get_time() - master->rules.start_time, \
master->philos[i].philo_id);
			pthread_mutex_unlock (&master->mutexes.write_lock);
			pthread_mutex_unlock (&master->mutexes.death_lock);
			pthread_mutex_unlock (&master->mutexes.eat_lock);
			return (true);
		}
		pthread_mutex_unlock (&master->mutexes.eat_lock);
		i++;
	}
	return (false);
}

void	controller(t_data *master)
{
	while (1)
	{
		if (master->rules.meal_limit != -1)
		{
			if (eat_limit_reached(master))
				return ;
		}
		if (death_detector(master))
			return ;
		usleep(500);
	}
}
