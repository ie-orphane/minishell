/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:06:18 by mbentale          #+#    #+#             */
/*   Updated: 2025/05/19 21:49:31 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(void)
{
	char	*line;
	t_list	*lst;
	char	**args;

	while (true)
	{
		line = readline(GREEN BOLD "larrysh> " RESET);
		if (!line)
			break ;
		lst = ft_parse(line);
		args = lst->content;
		if (ft_strcmp(*args, "echo") == 0)
			ft_echo(args);
		ft_lstclear(&lst, ft_strsclear);
	}
}
