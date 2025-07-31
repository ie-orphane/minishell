/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mb11junior <mb11junior@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 07:57:25 by mbentale          #+#    #+#             */
/*   Updated: 2025/07/31 15:15:35 by mb11junior       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_global	g_global = {
	.env = NULL,
	.exit_status = 0,
};

void	__exit(int status)
{
	ft_malloc(0);
	exit(status);
}

int	main(int __attribute__((unused)) argc, char __attribute__((unused)) * *argv,
		char **envp)
{
	char	*line;
	t_list	*lst;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	g_global.env = env_init(envp);
	while (true)
	{
		line = readline(GREEN BOLD "larrysh> " RESET);
		if (!line)
			break ;
		add_history(line);
		lst = ft_parse(line);
		if (!lst || !lst->content)
		{
			free(line);
			continue ;
		}
		if (((t_data *)lst->content)->args)
			ft_exec(&lst, &g_global.env);
	}
	printf("exit\n");
	__exit(g_global.exit_status);
}
