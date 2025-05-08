/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:17:49 by ielyatim          #+#    #+#             */
/*   Updated: 2025/05/08 09:21:03 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinc(const char *__str, char c)
{
	size_t	len;
	char	*str;

	if (!__str)
		return (NULL);
	len = ft_strlen(__str);
	str = (char *)malloc(len + 2);
	if (!str)
		return (NULL);
	ft_strlcpy(str, __str, len + 2);
	str[len] = c;
	str[len + 1] = '\0';
	return (str);
}
