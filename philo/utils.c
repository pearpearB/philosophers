/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:24:17 by jabae             #+#    #+#             */
/*   Updated: 2022/08/16 16:13:35 by jabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	free_thread(t_info *info, t_philo *philo)
// {
	
// }

long long	get_time(void)
{
	struct timeval	tp;

	if (gettimeofday(&tp, NULL) < 0)
		return(ft_error("[Error] Can't get time\n"));
	return (tp.tv_sec * 1000 + tp.tv_usec / 1000);
}

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
	return (-1);
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
			return(ft_error("[Error] Out of Unsigned Integer Range\n"));
		s++;
	}
	while ((*s >= '0' && *s <= '9') && *s)
	{
		if (sign > 0 && result > UINT_MAX / 10)
			return(ft_error("[Error] Out of Unsigned Integer Range\n"));
		result = result * 10 + (*s - '0');
		s++;
	}
	return (result);
}
