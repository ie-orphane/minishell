/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:57:31 by ielyatim          #+#    #+#             */
/*   Updated: 2025/05/12 18:57:38 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	ft_ispipe(const char *str)
{
	return (ft_strncmp(str, "|", 1) == 0);
}

bool	ft_issredir(const char *str)
{
	return (ft_strncmp(str, "<", 1) == 0 || ft_strncmp(str, ">", 1) == 0);
}

bool	ft_isdredir(const char *str)
{
	return (ft_strncmp(str, "<<", 2) == 0 || ft_strncmp(str, ">>", 2) == 0);
}

bool	ft_isquote(const char *str)
{
	return (ft_strncmp(str, "\'", 1) == 0 || ft_strncmp(str, "\"", 1) == 0);
}

bool	ft_isredir(const char *str)
{
	return (ft_isdredir(str) || ft_issredir(str));
}
