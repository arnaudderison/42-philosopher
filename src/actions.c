/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:12:28 by aderison          #+#    #+#             */
/*   Updated: 2024/10/14 16:12:00 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_philo *philo)
{
	print(philo->info, philo->id, "is sleeping");
	ft_usleep(philo->info->t_sleep);
	philo_thinking(philo);
}

static void	eat_process(t_philo *philo, pthread_mutex_t *first_fork,
		pthread_mutex_t *second_fork)
{
	pthread_mutex_lock(&(philo->info->m_eat));
	philo->is_eating = true;
	philo->times_eaten++;
	philo->last_eat = timestamp();
	print(philo->info, philo->id, "is eating");
	pthread_mutex_unlock(&(philo->info->m_eat));
	ft_usleep(philo->info->t_eat);
	pthread_mutex_lock(&(philo->info->m_eat));
	philo->is_eating = false;
	pthread_mutex_unlock(&(philo->info->m_eat));
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
	ft_usleep(1);
	philo_sleep(philo);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->id % 2 == 0)
	{
		first_fork = philo->fork_r;
		second_fork = &(philo->fork_l);
	}
	else
	{
		first_fork = &(philo->fork_l);
		second_fork = philo->fork_r;
	}
	pthread_mutex_lock(first_fork);
	print(philo->info, philo->id, "has taken a fork");
	if (philo->info->nb_philo == 1)
	{
		ft_usleep(philo->info->t_die * 2);
		return ;
	}
	pthread_mutex_lock(second_fork);
	print(philo->info, philo->id, "has taken a fork");
	eat_process(philo, first_fork, second_fork);
}

void	philo_thinking(t_philo *philo)
{
	print(philo->info, philo->id, "is thinking");
}
