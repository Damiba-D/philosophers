/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 22:43:27 by ddamiba           #+#    #+#             */
/*   Updated: 2026/01/23 17:25:01 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



int	main(int argc, char **argv)
{
	int i;

	i = 1;
	if (argc < 5 || argc > 6)
		return (printf("Incorrect number of args\n"));
	while (i < argc)
	{
		if (!is_valid_int(argv[i]))
			return (printf("Arg %d is invalid\n", i));
		else 
			printf("Arg %d: %ld\n", i, ft_atol(argv[i]));
		i++;
	}
}