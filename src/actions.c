/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:12:28 by aderison          #+#    #+#             */
/*   Updated: 2024/10/10 02:35:55 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_philo *philo)
{
	print(philo->info, philo->id, "is sleeping");
	ft_usleep(philo->info->t_sleep);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	// Determine which fork to pick up first (to avoid deadlock)
	first_fork = (philo->id % 2 == 0) ? philo->fork_r : &(philo->fork_l);
	second_fork = (philo->id % 2 == 0) ? &(philo->fork_l) : philo->fork_r;
	// Handle the case of a single philosopher
	if (philo->info->nb_philo == 1)
	{
		pthread_mutex_lock(first_fork);
		print(philo->info, philo->id, "has taken a fork");
		ft_usleep(philo->info->t_die + 100);
		pthread_mutex_unlock(first_fork);
		return ;
	}
	// Pick up forks
	pthread_mutex_lock(first_fork);
	print(philo->info, philo->id, "has taken a fork");
	pthread_mutex_lock(second_fork);
	print(philo->info, philo->id, "has taken a fork");
	// Start eating
	pthread_mutex_lock(&(philo->info->m_eat));
	philo->is_eating = true;
	philo->last_eat = timestamp();
	philo->times_eaten++;
	print(philo->info, philo->id, "is eating");
	pthread_mutex_unlock(&(philo->info->m_eat));
	// Simulate eating
	ft_usleep(philo->info->t_eat);
	// Finish eating
	pthread_mutex_lock(&(philo->info->m_eat));
	philo->is_eating = false;
	pthread_mutex_unlock(&(philo->info->m_eat));
	// Put down forks
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
}

void	philo_thinking(t_philo *philo)
{
	print(philo->info, philo->id, "is thinking");
}
