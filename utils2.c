/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 02:10:19 by daniel            #+#    #+#             */
/*   Updated: 2026/01/29 18:08:59 by daniel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	usleep_manager(t_data *master, int time)
{
	long	start;
	long	elapsed;

	start = get_time();
	while (1)
	{
		if (check_dead(master))
			return ;
		elapsed = get_time() - start;
		if (elapsed >= time)
			break ;
		usleep(500);
	}
}