/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 13:13:31 by jabae             #+#    #+#             */
/*   Updated: 2022/08/29 21:38:04 by jabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>
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
	pid_t			*pid;
	int				num_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				num_must_eat;
	int				num_full_philo;
	long long		time_start;
	sem_t			*fork;
	sem_t			*eat_sem;
	// sem_t			*eat_count_sem;
	sem_t			*check_sem;
	sem_t			*print_sem;
}	t_info;

typedef struct s_philo
{
	int				id;
	// int				fork_right; // 왜 포크 인덱스가 없지??
	// int				fork_left;
	int				num_eat;
	long long		time_last_eat;
	pthread_t		thread;
	t_info			*info;
}	t_philo;

/* init */
int				init_info(t_info *info);
int				init_philo(t_info *info, t_philo **philo);
int				init_process(t_info *info, t_philo **philo)
long long		init_time(void);

/* run */
void			run_philo(t_info *info, t_philo *philo);

/* utils */
int				check_death(t_info *info);
void			print_philo(t_info *info, int id, int status);
int				check_end(t_info *info, t_philo *philo, int i);
void			wait_time(long long time, t_philo *philo);
int				ft_atoi(const char *s);

#endif
