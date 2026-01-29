/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daniel <daniel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 16:50:57 by ddamiba           #+#    #+#             */
/*   Updated: 2026/01/28 19:56:02 by daniel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (!(c >= '0' && c <= '9'))
		return (0);
	return (1);
}

long	ft_atol(const char *str)
{
	int		i;
	long	res;
	int		sign;
	char	*cpy;

	i = 0;
	res = 0;
	sign = 1;
	cpy = (char *)str;
	while (cpy[i] != '\0' && ((cpy[i] >= '\t' && cpy[i] <= '\r')
			|| cpy[i] == ' '))
		i++;
	if (cpy[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (cpy[i] == '+')
		i++;
	while ((cpy[i] != '\0' && (cpy[i] >= '0' && cpy[i] <= '9')))
	{
		res = (res * 10) + (cpy[i] - '0');
		i++;
	}
	return (res * sign);
}

int	is_valid_int(char *str, int *res)
{
	int	i;
	int lres;

	i = 0;
	if (str[i] == '\0' || (str[i] == '0' && !str[i + 1]))
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '+' && i == 0)
			i++;
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	lres = ft_atol(str);
	if (lres <= 0 || lres > INT_MAX)
		return (0);
	*res = (int)lres;
	return (1);
}

int data_parsing(t_data *master, char **argv)
{
	if (!is_valid_int(argv[1], &master->rules.philo_count))
		return (ft_putendl_fd("Invalid philo count", 2), 0);
	if (!is_valid_int(argv[2], &master->rules.t_die))
		return (ft_putendl_fd("Invalid time to die", 2), 0);
	if (!is_valid_int(argv[3], &master->rules.t_eat))
		return (ft_putendl_fd("Invalid time to eat", 2), 0);
	if (!is_valid_int(argv[4], &master->rules.t_sleep))
		return (ft_putendl_fd("Invalid time to sleep", 2), 0);
	if (argv[5])
	{
		if (!is_valid_int(argv[5], &master->rules.meal_limit))
			return (ft_putendl_fd("Invalid meal limit", 2), 0);
	}
	else
		master->rules.meal_limit = -1;
	master->rules.death_id = -1;
	return (1);
}
