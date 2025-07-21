/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mb11junior <mb11junior@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 16:04:37 by mb11junior        #+#    #+#             */
/*   Updated: 2025/07/21 16:07:53 by mb11junior       ###   ########.fr       */
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

void	execute_cmd(char **args, t_list **env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (handle_redirections(args) < 0)
		{
			perror("redirection error");
			exit(EXIT_FAILURE);
		}
		ft_execvpe(args[0], args, env);
		perror("larrysh");
		exit(127);
	}
	waitpid(pid, &status, 0);
	update_exit_status(status); 
}

void exec_with_redir(t_data *data, t_list **env, bool is_builtin)
{
	pid_t pid;
	int  status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return;
	}
	if (pid == 0)
	{
		if (handle_redirections(data->redirs) < 0)
		{
			perror("redirection");
			exit(EXIT_FAILURE);
		}
		if (is_builtin)
			exec_builtin(data->args, env);
		else
			execute_cmd(data->args, env);
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, &status, 0);
	update_exit_status(status);
}

void	update_exit_status(int status)
{
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status = 128 + WTERMSIG(status);
}
