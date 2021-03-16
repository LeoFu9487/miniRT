/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 02:38:40 by yfu               #+#    #+#             */
/*   Updated: 2021/03/03 02:39:21 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double		*normal_vector_sq(double *point, void *ptr)
{
	double		*ans;
	t_square	*square;

	if (!(ans = ft_malloc(3, sizeof(double))))
		error_exit("normal_vector_sq\n");
	square = ptr;
	ans[0] = square->orientation[0];
	ans[1] = square->orientation[1];
	ans[2] = square->orientation[2];
	(void)point;
	return (ans);
}
