/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 00:55:32 by yfu               #+#    #+#             */
/*   Updated: 2021/03/03 00:56:13 by yfu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	*cross(double *v1, double *v2)
{
	double	*new;

	if (!(new = ft_malloc(3, sizeof(double))))
		return (NULL);
	new[0] = v1[1] * v2[2] - v1[2] * v2[1];
	new[1] = v1[2] * v2[0] - v1[0] * v2[2];
	new[2] = v1[0] * v2[1] - v1[1] * v2[0];
	return (new);
}

double	dot(double *v1, double *v2)
{
	return (v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2]);
}

double	len(double *v)
{
	return (sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]));
}

double	cos_vector(double *v1, double *v2)
{
	return (dot(v1, v2) / len(v1) / len(v2));
}

double	*add_vector(double *v1, double *v2)
{
	double	*v;
	int		ct;

	if (!(v = ft_malloc(3, sizeof(double))))
		return (NULL);
	ct = -1;
	while (++ct < 3)
		v[ct] = v1[ct] + v2[ct];
	return (v);
}
