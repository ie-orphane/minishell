/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:16:52 by ielyatim          #+#    #+#             */
/*   Updated: 2025/05/13 16:05:20 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strreplace(char *__dst, char *__src, char *__sub, size_t __start)
{
	char	*pos;
	size_t	len_src;
	size_t	len_sub;
	size_t	len_dst;
	char	*result;

	if (!__dst || !__src || !__sub || __start >= ft_strlen(__dst))
		return (NULL);
	len_dst = ft_strlen(__dst);
	pos = ft_strnstr(__dst + __start, __src, len_dst - __start);
	if (!pos)
		return (ft_strdup(__dst));
	len_src = ft_strlen(__src);
	len_sub = ft_strlen(__sub);
	result = malloc(len_dst - len_src + len_sub + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, __dst, pos - __dst + 1);
	ft_strlcat(result, __sub, len_dst - len_src + len_sub + 1);
	ft_strlcat(result, pos + len_src, len_dst - len_src + len_sub + 1);
	return (result);
}
