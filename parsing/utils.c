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

#include "main.h"

void	ft_err(char *err)
{
	ft_putstr_fd(RED, STDERR_FILENO);
	ft_putstr_fd("larrysh", STDERR_FILENO);
	ft_putstr_fd(BLACK ":" RESET " ", STDERR_FILENO);
	ft_putendl_fd(err, STDERR_FILENO);
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
		return (ft_itoa(g_global.exit_status));
	value = env_get(g_global.env, key + 1);
	if (!value)
		value = "";
	return (ft_strdup(value));
}
