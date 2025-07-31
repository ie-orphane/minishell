/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 07:57:25 by mbentale          #+#    #+#             */
/*   Updated: 2025/07/23 17:04:52 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_global	g_global = {
	.env = NULL,
	.exit_status = 0,
};

int	main(int __attribute__((unused)) argc, char __attribute__((unused)) **argv,
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
			ft_lstclear(&lst, ft_dataclear);
			continue ;
		}
		if (((t_data *)lst->content)->args)
			ft_exec(&lst, &g_global.env);
	}
	printf("exit\n");
	return (ft_lstclear(&g_global.env, env_free), g_global.exit_status);
}
