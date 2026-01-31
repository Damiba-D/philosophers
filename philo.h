/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 22:32:17 by ddamiba           #+#    #+#             */
/*   Updated: 2026/01/31 01:30:33 by daniel           ###   ########.fr       */
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

# define MUT_ERR "Mutex creation error"

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				philo_id;
	int				meal_count;
	bool			eat_limit;
	int				t_lastmeal;
	pthread_t		thread;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_data			*mstr_link;
}	t_philo;

typedef struct s_mutex
{
	pthread_mutex_t	*fork_arr;
	pthread_mutex_t	death_lock;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	write_lock;
}	t_mutex;

typedef struct s_rules
{
	int	philo_count;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	meal_limit;
	int	start_time;
	int	death_id;
}	t_rules;

typedef struct s_data
{
	t_philo	*philos;
	t_mutex	mutexes;
	t_rules	rules;
}	t_data;

int		ft_isdigit(int c);
long	ft_atol(const char *str);
int		is_valid_int(char *str, int *res);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	wr_str(char *s);
int		get_time(void);
int		data_parsing(t_data *master, char **argv);
int		init_fork(t_data *master);
int		init_mutex(t_data *master);
int		init_philo(t_data *master);
int		init_mstr(t_data *master);
void	fork_cleanup(t_data *master);
void	mutex_cleanup(t_data *master);
void	master_cleanup(t_data *master);
bool	check_dead(t_data *master);
bool	eat_limit_reached(t_data *master);
bool	death_detector(t_data *master);
void	controller(t_data *master);
void	write_action(t_data *master, char *action, t_philo *philo);
void	usleep_manager(t_data *master, int time);
void	grab_forks(t_data *master, t_philo *philo);
void	philo_eats(t_data *master, t_philo *philo);
void	philo_sleeps(t_data *master, t_philo *philo);
void	philo_thinks(t_data *master, t_philo *philo);
void	*philo_routine(void *philosopher);
#endif