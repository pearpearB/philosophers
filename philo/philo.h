/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:13:31 by jabae             #+#    #+#             */
/*   Updated: 2022/08/26 13:49:38 by jabae            ###   ########.fr       */
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
# define INT_MIN -2147483648

# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIE 5

typedef struct s_info
{
	int	num_philo;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	num_must_eat;
	int	isdied; // !!!!!
	unsigned int	time_start;
	pthread_t	monitor;
	pthread_mutex_t	*fork;
	pthread_mutex_t	check_death;
	// pthread_mutex_t	check_num_eat; //
	pthread_mutex_t	print;
}	t_info;

typedef struct s_philo
{
	int	id;
	int	fork_right;
	int	fork_left;
	int	num_eat;
	unsigned int	time_last_eat;
	pthread_t	thread;
	t_info	*info;
}	t_philo;

/* init */
int	init_info(t_info *info);
int	init_philo(t_info *info, t_philo **philo);
unsigned int init_time(void);

/* run */
int check_death(t_philo *philo);
void	run_philo(t_info *info, t_philo *philo);
void	print_status(t_info *info, unsigned int time_act, int id, int status);

/* utils */
void	free_thread(t_info *info, t_philo *philo);
void	wait_time(unsigned int time);
int	ft_atoi(const char *s);

#endif
