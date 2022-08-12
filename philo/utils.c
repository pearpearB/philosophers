/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:24:17 by jabae             #+#    #+#             */
/*   Updated: 2022/08/12 15:06:55 by jabae            ###   ########.fr       */
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

long long	ft_atoui(const char *s)
{
	long long	result;

	result = 0;
	while (((*s >= 9 && *s <= 13) || *s == ' ') && *s)
		s++;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			ft_error("[Error] Out of Unsigned Integer Range\n");
		s++;
	}
	while ((*s >= '0' && *s <= '9') && *s)
	{
		if (sign > 0 && result > UINT_MAX / 10)
			ft_error("[Error] Out of Unsigned Integer Range\n");
		result = result * 10 + (*s - '0');
		s++;
	}
	return (result);
}
