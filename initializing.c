/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 18:42:46 by daniel            #+#    #+#             */
/*   Updated: 2026/01/31 01:26:34 by daniel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_fork(t_data *master)
{
	int	i;

	i = 0;
	while (i < master->rules.philo_count)
	{
		if (pthread_mutex_init (&master->mutexes.fork_arr[i], NULL) != 0)
		{
			ft_putendl_fd(MUT_ERR, 2);
			while (i >= 0)
				pthread_mutex_destroy (&master->mutexes.fork_arr[i--]);
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_mutex(t_data *master)
{
	master->mutexes.fork_arr = \
malloc(sizeof(pthread_mutex_t) * master->rules.philo_count);
	if (!master->mutexes.fork_arr)
		return (0);
	if (!init_fork(master))
		return (free(master->mutexes.fork_arr), 0);
	if (pthread_mutex_init(&master->mutexes.write_lock, NULL) != 0)
	{
		fork_cleanup(master);
		return (free(master->mutexes.fork_arr), ft_putendl_fd(MUT_ERR, 2), 0);
	}
	if (pthread_mutex_init(&master->mutexes.eat_lock, NULL) != 0)
	{
		pthread_mutex_destroy (&master->mutexes.write_lock);
		fork_cleanup(master);
		return (free(master->mutexes.fork_arr), ft_putendl_fd(MUT_ERR, 2), 0);
	}
	if (pthread_mutex_init(&master->mutexes.death_lock, NULL) != 0)
	{
		pthread_mutex_destroy (&master->mutexes.write_lock);
		pthread_mutex_destroy (&master->mutexes.eat_lock);
		fork_cleanup(master);
		return (free(master->mutexes.fork_arr), ft_putendl_fd(MUT_ERR, 2), 0);
	}
	return (1);
}

int	init_philo(t_data *master)
{
	int	i;

	i = 0;
	master->philos = malloc(sizeof(t_philo) * master->rules.philo_count);
	if (!master->philos)
		return (0);
	while (i < master->rules.philo_count)
	{
		master->philos[i].eat_limit = false;
		master->philos[i].t_lastmeal = master->rules.start_time;
		master->philos[i].meal_count = 0;
		master->philos[i].philo_id = i + 1;
		master->philos[i].l_fork = &master->mutexes.fork_arr[i];
		if (i == 0)
			master->philos[i].r_fork = \
&master->mutexes.fork_arr[master->rules.philo_count - 1];
		else
			master->philos[i].r_fork = &master->mutexes.fork_arr[i - 1];
		master->philos[i].mstr_link = master;
		i++;
	}
	return (1);
}

int	init_mstr(t_data *master)
{
	master->rules.death_id = -1;
	master->rules.start_time = get_time();
	if (!init_mutex(master))
		return (0);
	if (!init_philo(master))
		return (mutex_cleanup(master), 0);
	return (1);
}
