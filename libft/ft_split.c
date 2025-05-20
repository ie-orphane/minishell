/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:13:27 by mbentale          #+#    #+#             */
/*   Updated: 2025/05/20 10:18:42 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *str, char *set)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (!ft_strchr(set, str[i]))
		{
			while (!ft_strchr(set, str[i]) && str[i])
				i++;
			count++;
		}
		else
			i++;
	}
	return (count);
}

static char	*word_alloc(const char *str, char *set)
{
	int		i;
	char	*ptr;

	i = 0;
	while (str[i] && !ft_strchr(set, str[i]))
		i++;
	ptr = malloc(sizeof(char) * (i + 1));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (str[i] && !ft_strchr(set, str[i]))
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

static void	*free_all(char **s, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

char	**ft_split(const char *str, char *set)
{
	int		i;
	char	**arr;

	if (str == NULL || !set)
		return (NULL);
	arr = malloc(sizeof(char *) * (count_words(str, set) + 1));
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (*str)
	{
		while (*str && ft_strchr(set, *str))
			str++;
		if (*str)
		{
			arr[i] = word_alloc(str, set);
			if (arr[i] == NULL)
				return (free_all(arr, i));
			i++;
			while (*str && !ft_strchr(set, *str))
				str++;
		}
	}
	arr[i] = NULL;
	return (arr);
}
