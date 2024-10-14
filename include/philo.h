/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:02:08 by aderison          #+#    #+#             */
/*   Updated: 2024/10/14 14:59:43 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define RED "\x1B[31m"
# define GREEN "\x1B[32m"
# define YELLOW "\x1B[33m"
# define BLUE "\x1B[34m"
# define RESET "\x1B[0m"

# define MAX_PHILOSOPHERS 20

enum				e_error
{
	COUNT_ARGS,
	INVALID_ARGS,
	LIMIT_PHILO,
	MALLOC,
	NULL_PTR,
	UNKNOWN,
	SUCCESS,
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
}					t_philo;

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
	pthread_mutex_t	m_eat;
	pthread_mutex_t	m_stop;
	pthread_mutex_t	m_dead;
}					t_data;

// utils
int					ft_isdigit(int character);
int					ft_atoi(const char *str);
long long			timestamp(void);
int					ft_usleep(unsigned int ms);
void				print(t_data *data, int id, const char *status);
void				ft_free(unsigned int count, ...);
void				freeall(t_data *data);

// philo
void				error(enum e_error err);
int					data_init(t_data *data, char **argv);
void				philo_sleep(t_philo *philo);
void				philo_eat(t_philo *philo);
//int					is_philo_dead(t_philo *philo);
void				*philo_life(void *phi);
void				philo_thinking(t_philo *philo);
int					philo_init(t_data *data);

#endif
