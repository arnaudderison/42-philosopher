/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 20:12:28 by aderison          #+#    #+#             */
/*   Updated: 2024/10/09 23:51:08 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void philo_sleep(t_philo *philo)
{

    if (!philo->info->stop)
    {
        print(philo->info, philo->id, "is sleeping");
        ft_usleep(philo->info->t_sleep);
        philo_thinking(philo);
    }
}

void philo_eat(t_philo *philo)
{
    if (!philo->info->stop)
    {
        pthread_mutex_lock(&(philo->fork_l));
        print(philo->info, philo->id, "has taken a fork");
        // if (philo->info->nb_philo == 1)
	    // {
        //     ft_usleep(philo->info->t_die);
        //     return ;
	    // }
        pthread_mutex_lock(philo->fork_r);
        print(philo->info, philo->id, "has taken a fork");
        pthread_mutex_lock(&(philo->info->m_eat));
        philo->is_eating = true;
        philo->last_eat = timestamp();
        philo->times_eaten++;
        pthread_mutex_unlock(&philo->info->m_eat);
        print(philo->info, philo->id, "is eating");
        ft_usleep(philo->info->t_eat);
        pthread_mutex_lock(&(philo->info->m_eat));
        philo->is_eating = false;
        pthread_mutex_unlock(&(philo->info->m_eat));
        pthread_mutex_unlock(philo->fork_r);
        pthread_mutex_unlock(&(philo->fork_l));
        philo_sleep(philo);
    }
}

void philo_thinking(t_philo *philo)
{
    if (!philo->info->stop)
        print(philo->info, philo->id, "is thinking");
} 
