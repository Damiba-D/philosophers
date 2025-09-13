/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 22:43:27 by ddamiba           #+#    #+#             */
/*   Updated: 2025/09/14 00:43:10 by ddamiba          ###   ########.fr       */
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

int	is_valid_int(char *str)
{
	int	i;

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
	if (ft_atol(str) > INT_MAX)
		return (0);
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	int i;

	i = 1;
	(void)env;
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