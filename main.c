/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentale <mbentale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 07:57:25 by mbentale          #+#    #+#             */
/*   Updated: 2025/07/21 19:09:19 by mbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		g_exit_status = 0;

void	ft_dataclear(void *__data)
{
	t_data	*data;

	data = __data;
	if (!data)
		return ;
	ft_strsclear(data->args);
	ft_strsclear(data->redirs);
	free(data);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_list		*lst;
	t_list		*env;

	(void)argc;
	(void)argv;
	env = env_init(envp);
	while (true)
	{
		line = readline(GREEN BOLD "larrysh> " RESET);
		if (!line)
			break ;
		add_history(line);
		lst = ft_parse(line);
		if (!lst)
		{
			free(line);
			continue ;
		}
		ft_exec(lst, &env);
		ft_lstclear(&lst, ft_dataclear);
		free(line);
	}
	ft_lstclear(&env, env_free);
}
