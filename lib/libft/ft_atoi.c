/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:24:57 by yfu               #+#    #+#             */
/*   Updated: 2020/12/22 12:49:25 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
		return (1);
	return (0);
}

int			ft_atoi(const char *str)
{
	long long int	ct[3];

	if (!str || str[0] == 0)
		return (0);
	if (ft_isspace(*str))
		return (ft_atoi(str + 1));
	ct[0] = (str[0] == '+' || str[0] == '-') ? 0 : -1;
	ct[2] = (str[0] == '-') ? -1 : 1;
	ct[1] = 0;
	while (str[++ct[0]])
	{
		if (str[ct[0]] < '0' || str[ct[0]] > '9')
			return (ct[1] * ct[2]);
		ct[1] = 10 * ct[1] + str[ct[0]] - '0';
	}
	return (ct[1] * ct[2]);
}

double		ft_atodouble(char **str)
{
	double	ans;
	double	num;

	if (!str || !(*str))
		return (0.0);
	while (**str && ft_isdigit(**str) == 0 && **str != '.')
		(*str)++;
	ans = (double)ft_atoi(*str);
	while (**str && ft_isdigit(**str))
		(*str)++;
	if (**str != '.')
		return (ans);
	(*str)++;
	num = (double)ft_atoi(*str);
	while (**str && ft_isdigit(**str))
	{
		(*str)++;
		num /= 10.0;
	}
	return (ans + num);
}

double		ft_neg_double(char **str, char *message)
{
	double	sign;

	if (!str || !message || str[0] == 0)
		return (0.0);
	sign = 1.0;
	while (**str && ft_isdigit(**str) == 0 && **str != '.' && **str != '-')
		(*str)++;
	if (**str == 0)
	{
		printf("%s ", message);
		error_exit("not found\n");
	}
	if (**str == '-')
	{
		sign *= -1.0;
		(*str)++;
		if (!ft_isdigit(**str))
			error_exit("negative number in wrong format\n");
	}
	return (sign * ft_atodouble(str));
}
