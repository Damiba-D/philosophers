/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 22:32:17 by ddamiba           #+#    #+#             */
/*   Updated: 2026/01/23 17:34:29 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <stdbool.h>

typedef struct s_philo
{
	int philo_id;
	int meal_count;
	int t_lastmeal;
	pthread_t thread;
	pthread_mutex_t *l_fork;
	pthread_mutex_t *r_fork;
}	t_philo;

typedef struct s_mutex
{
	pthread_mutex_t *fork_arr;
	pthread_mutex_t death_lock;
	pthread_mutex_t eat_lock;
	pthread_mutex_t write_lock;
}	t_mutex;

typedef struct s_rules
{
	int philo_count;
	int t_die;
	int t_eat;
	int t_sleep;
	int meal_limit;
	int start_time;
	bool no_deaths;
}	t_rules;

typedef struct s_data
{
	t_philo *philos;
	t_mutex	*mutexes;
	t_rules rules;
}	t_data;


int		ft_isdigit(int c);
long	ft_atol(const char *str);
int		is_valid_int(char *str);

#endif