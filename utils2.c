/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 02:10:19 by daniel            #+#    #+#             */
/*   Updated: 2026/02/09 15:41:31 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	usleep_manager(t_data *master, int time)
{
	long	start;
	long	elapsed;

	start = get_time();
	(void)elapsed;
	while (get_time() - start < time)
	{
		if (check_dead(master))
			return ;
		usleep(500);
	}
}
