/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentale <mbentale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:21:44 by mbentale          #+#    #+#             */
/*   Updated: 2024/11/04 14:42:18 by mbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_src;
	size_t	len_dst;
	size_t	i;

	len_src = ft_strlen(src);
	if (dst == NULL && dstsize == 0)
		return (len_src);
	len_dst = ft_strlen(dst);
	if (dstsize == 0 || dstsize < len_dst)
		return (len_src + dstsize);
	i = len_dst;
	while (*src && i < dstsize - 1)
		dst[i++] = *(src++);
	dst[i] = '\0';
	return (len_dst + len_src);
}
