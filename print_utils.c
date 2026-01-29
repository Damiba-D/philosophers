/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 15:04:31 by daniel            #+#    #+#             */
/*   Updated: 2026/01/29 18:08:07 by daniel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

void	ft_putendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s == NULL || fd < 0)
		return ;
	while (s[i] != '\0')
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
	ft_putchar_fd('\n', fd);
}

void	wr_str(char *s)
{
	ft_putstr_fd(s, 1);
}

void	write_action(t_data *master, char *action, t_philo *philo)
{
	int	time;

	if (check_dead(master))
		return ;
	pthread_mutex_lock (&master->mutexes.write_lock);
	time = get_time() - master->rules.start_time;
	printf ("%d %d %s\n", time, philo->philo_id, action);
	pthread_mutex_unlock (&master->mutexes.write_lock);
}
