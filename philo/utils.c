/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:24:17 by jabae             #+#    #+#             */
/*   Updated: 2022/08/11 16:43:11 by jabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

int ft_error(char *msg)
{
	write(2, msg, ft_strlen(msg));
	exit(EXIT_FAILURE);
}

long long	ft_atoi(const char *s)
{
	long long	result;
	int			sign;

	sign = 1;
	result = 0;
	while (((*s >= 9 && *s <= 13) || *s == ' ') && *s)
		s++;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign *= -1;
		s++;
	}
	while ((*s >= '0' && *s <= '9') && *s)
	{
		if ((sign > 0 && result > INT_MAX / 10) || \
			(sign < 0 && result > INT_MAX + 1 / 10))
			ft_error("[Error] Out of Integer Range\n");
		result = result * 10 + (*s - '0');
		s++;
	}
	return (sign * result);
}
