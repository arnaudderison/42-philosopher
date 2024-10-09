/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:02:08 by aderison          #+#    #+#             */
/*   Updated: 2024/10/09 18:09:51 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

# define RED "\x1B[31m"
# define GREEN "\x1B[32m"
# define YELLOW "\x1B[33m"
# define BLUE "\x1B[34m"
# define RESET "\x1B[0m"


enum error 
{
    COUNT_ARGS,
    INVALID_ARGS,
    SUCCESS,
    UNKNOWN,
};

typedef struct s_philo
{
	int				id;
	int				times_eaten;
	bool			is_eating;
	pthread_t		thread;
	long long		last_eat;
	struct s_data	*info;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	fork_l;
}		t_philo;

typedef struct s_data
{
	int				philo_eat;
	int				nb_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	int				stop;
	long long		t_start;
	t_philo			*philo;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_stop;
	pthread_mutex_t	m_eat;
	pthread_mutex_t	m_dead;
}		t_data;

//utils
int	ft_isdigit(int character);

//philo
int error(enum error err);

#endif
