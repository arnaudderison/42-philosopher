/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aderison <aderison@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 18:44:39 by aderison          #+#    #+#             */
/*   Updated: 2024/10/14 14:09:22 by aderison         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	overflow(long sign)
{
	if (sign > 0)
		return (-1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	sign;
	long	nb;
	long	temp;

	i = 0;
	sign = 1;
	nb = 0;
	if (!str)
		return (0);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		++i;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		temp = nb;
		nb = nb * 10 + str[i++] - '0';
		if (temp > nb)
			return (overflow(sign));
	}
	nb = nb * sign;
	return ((int)nb);
}
