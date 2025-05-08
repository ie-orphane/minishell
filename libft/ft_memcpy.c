/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentale <mbentale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:59:27 by mbentale          #+#    #+#             */
/*   Updated: 2024/11/02 13:20:22 by mbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*tmp_dst;
	unsigned char	*tmp_src;

	if (dst == 0 && src == 0)
		return (NULL);
	tmp_dst = (unsigned char *)dst;
	tmp_src = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		tmp_dst[i] = tmp_src[i];
		i++;
	}
	return (dst);
}
