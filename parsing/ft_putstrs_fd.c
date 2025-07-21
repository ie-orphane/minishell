/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrs_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:59:46 by ielyatim          #+#    #+#             */
/*   Updated: 2025/07/21 14:59:55 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_putstrs_fd(char **s, int fd)
{
	if (s == NULL || fd < 0)
		return ;
	while (*s)
	{
		ft_putstr_fd(*s, fd);
		s++;
	}
}
