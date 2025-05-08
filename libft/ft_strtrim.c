/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentale <mbentale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:52:53 by mbentale          #+#    #+#             */
/*   Updated: 2024/11/06 14:36:25 by mbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	int		start;
	int		end;
	char	*str;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1) - 1;
	while (end >= 0 && ft_strchr(set, s1[end]))
		end--;
	if (start > end)
		return (ft_strdup(""));
	str = (char *)malloc(end - start + 2);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1 + start, end - start + 2);
	return (str);
}
