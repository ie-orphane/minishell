/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 09:58:28 by ielyatim          #+#    #+#             */
/*   Updated: 2025/05/20 11:37:58 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_error(char *type, char *err)
{
	printf(RED "%s" BLACK ":" RESET " %s.\n", type, err);
}

char	*env_key(char *str)
{
	int		i;
	char	*key;

	i = 1;
	if (ft_strncmp(str, "$?", 2) == 0)
		return (ft_strdup("$?"));
	while (str[i] && ft_isalnum(str[i]))
		i++;
	key = ft_substr(str, 0, i);
	return (key);
}

char	*env_value(char *key)
{
	char	*value;

	if (ft_strcmp(key, "$?") == 0)
		return (ft_itoa(g_exit_status));
	value = getenv(key + 1);
	if (!value)
		value = "";
	return (ft_strdup(value));
}
