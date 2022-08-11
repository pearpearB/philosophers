/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:13:31 by jabae             #+#    #+#             */
/*   Updated: 2022/08/11 16:31:56 by jabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define INT_MAX 2147483647

typedef struct s_info
{
	unsigned int	num_philo;
	unsigned int	time_die;
	unsigned int	time_eat;
	unsigned int	time_sleep;
	int	num_must_eat;
}	t_info;

typedef struct s_philo
{
	t_info	*info;
	pthread_t	th;
}	t_philo;


/* utils */
int ft_error(char *msg);
long long	ft_atoi(const char *s);

#endif