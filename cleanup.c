/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 02:47:02 by daniel            #+#    #+#             */
/*   Updated: 2026/01/28 18:38:33 by daniel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fork_cleanup(t_data *master)
{
	int	i;

	i = 0;
	while (i < master->rules.philo_count)
		pthread_mutex_destroy (&master->mutexes.fork_arr[i++]);
}

void	mutex_cleanup(t_data *master)
{
	pthread_mutex_destroy (&master->mutexes.write_lock);
	pthread_mutex_destroy (&master->mutexes.eat_lock);
	pthread_mutex_destroy (&master->mutexes.death_lock);
	fork_cleanup(master);
	free(master->mutexes.fork_arr);
}

void	master_cleanup(t_data *master)
{
	mutex_cleanup(master);
	free(master->philos);
	free(master);
}

