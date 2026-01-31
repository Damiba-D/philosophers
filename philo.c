/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 22:43:27 by ddamiba           #+#    #+#             */
/*   Updated: 2026/01/31 01:28:30 by daniel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_simulation(t_data *master)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < master->rules.philo_count)
	{
		if (pthread_create (&master->philos[i].thread, NULL, \
&philo_routine, &master->philos[i]) != 0)
		{
			while (j < i)
				pthread_join(master->philos[j++].thread, NULL);
			return ;
		}
		i++;
	}
	controller(master);
	i = 0;
	while (i < master->rules.philo_count)
	{
		pthread_join(master->philos[i].thread, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data	*master;

	if (argc < 5 || argc > 6)
		return (printf("Incorrect number of args\n"));
	master = malloc(sizeof(t_data));
	if (!master)
		return (ft_putendl_fd("Allocation error", 2), -1);
	if (!data_parsing(master, argv))
		return (free(master), -1);
	if (master->rules.philo_count == 1)
	{
		printf("0 1 has taken a fork\n");
		usleep(master->rules.t_die * 1000);
		printf("%i 1 died\n", master->rules.t_die);
		return (free(master), 0);
	}
	if (!init_mstr(master))
		return (free(master), -1);
	start_simulation(master);
	master_cleanup(master);
}
