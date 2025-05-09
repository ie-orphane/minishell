/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 09:58:28 by ielyatim          #+#    #+#             */
/*   Updated: 2025/05/09 09:58:31 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	ft_isredir(char *str)
{
	return (ft_strcmp(str, ">>") == 0 || ft_strcmp(str, "<<") == 0
		|| ft_strcmp(str, "<") == 0 || ft_strcmp(str, ">") == 0);
}

bool	ft_ispipe(char *str)
{
	return (ft_strcmp(str, "|") == 0);
}

void	ft_error(char *type, char *err)
{
	printf(RED "%s" BLACK ":" RESET " %s.\n", type, err);
}
