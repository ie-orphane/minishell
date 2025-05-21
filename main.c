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

int	main(int argc, char **argv, char **envi)
{
	char	*line;
	t_list	*lst;
	char	**args;
	t_list	*env;

	(void)argc;
	(void)argv;
	env = _env_init(envi);
	while (true)
	{
		line = readline(GREEN BOLD "larrysh> " RESET);
		if (!line)
			break ;
		lst = ft_parse(line);
		args = lst->content;
		if (ft_strcmp(*args, "echo") == 0)
			ft_echo(args);
		else if (ft_strcmp(*args, "export") == 0)
			ft_export(args + 1, &env);
		ft_lstclear(&lst, ft_strsclear);
	}
	ft_lstclear(&env, _env_free);
}
