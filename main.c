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

void	sigint_handler(int sig)
{
	(void)sig;
	g_exit_status = 130;
	rl_replace_line("", 0);
	printf("\n" GREEN BOLD "larrysh> " RESET);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_list	*lst;
	t_list	*env;

	(void)argc;
	(void)argv;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	env = env_init(envp);
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
			ft_exec(lst, &env);
		ft_lstclear(&lst, ft_dataclear);
	}
	printf("exit\n");
	ft_lstclear(&env, env_free);
}
