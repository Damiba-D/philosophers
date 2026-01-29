/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 01:57:03 by daniel            #+#    #+#             */
/*   Updated: 2026/01/29 18:11:39 by daniel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	grab_forks(t_data *master, t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock (philo->l_fork);
		write_action (master, "has taken a fork", philo);
		pthread_mutex_lock (philo->r_fork);
		write_action (master, "has taken a fork", philo);
		return ;
	}
	pthread_mutex_lock (philo->r_fork);
	write_action (master, "has taken a fork", philo);
	pthread_mutex_lock (philo->l_fork);
	write_action (master, "has taken a fork", philo);
	return ;
}

void	philo_eats(t_data *master, t_philo *philo)
{
	grab_forks(master, philo);
	pthread_mutex_lock (&master->mutexes.eat_lock);
	write_action (master, "is eating", philo);
	philo->t_lastmeal = get_time ();
	philo->meal_count++;
	if (philo->meal_count == master->rules.meal_limit)
		philo->eat_limit = true;
	pthread_mutex_unlock (&master->mutexes.eat_lock);
	usleep_manager(master, master->rules.t_eat);
	pthread_mutex_unlock (philo->r_fork);
	pthread_mutex_unlock (philo->l_fork);
}

void	philo_sleeps(t_data *master, t_philo *philo)
{
	write_action (master, "is sleeping", philo);
	usleep_manager (master, master->rules.t_sleep);
}

void	philo_thinks(t_data *master, t_philo *philo)
{
	write_action (master, "is thinking", philo);
}

void	*philo_routine(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	if (philo->philo_id % 2 == 0)
		usleep_manager (philo->mstr_link, 10);
	while (!check_dead(philo->mstr_link))
	{
		philo_eats(philo->mstr_link, philo);
		if (check_dead(philo->mstr_link))
			break ;
		philo_sleeps(philo->mstr_link, philo);
		if (check_dead(philo->mstr_link))
			break ;
		philo_thinks(philo->mstr_link, philo);
	}
	return (NULL);
}