/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentale <mbentale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:57:25 by mbentale          #+#    #+#             */
/*   Updated: 2024/11/04 09:10:09 by mbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*find;

	i = 0;
	find = NULL;
	while (s[i])
	{
		if (s[i] == (char)c)
			find = (char *)&s[i];
		i++;
	}
	if (s[i] == (char)c)
		find = (char *)&s[i];
	return (find);
}
