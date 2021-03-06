/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 16:07:51 by yfu               #+#    #+#             */
/*   Updated: 2020/12/22 12:42:46 by yfu              ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strjoin(char const *s1, char const *s2)
{
	int		l;
	int		l2;
	int		ct;
	char	*str;

	l2 = ft_strlen(s1);
	l = ft_strlen(s1) + ft_strlen(s2);
	if (!s1 || !s2 || l < 0 || !(str = ft_memory(l + 1, sizeof(char), 0, push)))
		return (NULL);
	ct = -1;
	while (++ct < l)
	{
		if (ct < l2)
			str[ct] = s1[ct];
		else
			str[ct] = s2[ct - l2];
	}
	str[l] = '\0';
	return (str);
}
