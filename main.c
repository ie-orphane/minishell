/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentale <mbentale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 17:06:18 by mbentale          #+#    #+#             */
/*   Updated: 2025/05/24 12:01:18 by mbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	__is_builtin(char **args, t_list **env)
{
	if (ft_strcmp(*args, "echo") == 0)
		ft_echo(args);
	else if (ft_strcmp(*args, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(*args, "cd") == 0)
		ft_cd(args, *env);
	else if (ft_strcmp(*args, "export") == 0)
		ft_export(args + 1, env);
	else if (ft_strcmp(*args, "unset") == 0)
		ft_unset(args + 1, env);
	else if (ft_strcmp(*args, "env") == 0)
		ft_env(*env);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_list	*lst;
	char	**args;
	t_list	*env;

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
			continue ;
		args = lst->content;
		__is_builtin(args, &env);
		ft_lstclear(&lst, ft_strsclear);
	}
	ft_lstclear(&env, env_free);
}
