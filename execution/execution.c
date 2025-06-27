/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentale <mbentale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 09:40:06 by mbentale          #+#    #+#             */
/*   Updated: 2025/06/27 10:43:04 by mbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	is_builtin_cmd(char **args)
{
	if (!args || !args[0])
		return (0);
	return (ft_strcmp(args[0], "echo") == 0 || ft_strcmp(args[0], "pwd") == 0
		|| ft_strcmp(args[0], "cd") == 0 || ft_strcmp(args[0], "export") == 0
		|| ft_strcmp(args[0], "unset") == 0 || ft_strcmp(args[0], "env") == 0
		|| ft_strcmp(args[0], "exit") == 0);
}

void	exec_builtin(char **args, t_list **env)
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
	else if (ft_strcmp(*args, "exit") == 0)
		ft_exit(args, env);
}

void	ft_exec(t_list *lst, t_list **env)
{
	char	**args;

	args = lst->content;
	if (!lst->next && is_builtin_cmd(args))
		exec_builtin(args, env);
	else if (lst->next)
		exec_pipe(lst, env);
	else
		execute_cmd(args);
}
