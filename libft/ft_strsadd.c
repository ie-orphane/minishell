/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsadd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 09:47:33 by ielyatim          #+#    #+#             */
/*   Updated: 2025/05/09 09:50:58 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsadd(char **_strs, char *str)
{
	size_t	len;
	char	**strs;
	size_t	i;

	if (!str)
		return (NULL);
	len = 0;
	while (_strs && _strs[len])
		len++;
	strs = malloc(sizeof(char *) * (len + 2));
	if (!strs)
		return (NULL);
	i = 0;
	while (i < len)
	{
		strs[i] = _strs[i];
		i++;
	}
	strs[len] = str;
	strs[len + 1] = NULL;
	free(_strs);
	return (strs);
}
