/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentale <mbentale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 09:40:06 by mbentale          #+#    #+#             */
/*   Updated: 2025/07/24 10:01:40 by mbentale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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

static void	execute_cmd(char **args, t_list **env)
{
	pid_t	pid;
	int		status;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
		if (!is_valid_command(args[0], *env))
		{
			print_error(args[0], "command not found");
			exit(EXIT_FAILURE);
		}
		if (handle_redirections(args) < 0)
			perror_and_exit("larrysh: redirection error");
		ft_execvpe(args[0], args, env);
		perror("larrysh");
		exit(127);
	}
	waitpid(pid, &status, 0);
	update_exit_status(status);
	signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, sigint_handler);
}

static void	child_process(t_data *data, t_list **env, bool is_builtin)
{
	if (!is_builtin_cmd(data->args) && !is_valid_command(data->args[0], *env))
	{
		print_error(data->args[0], "command not found");
		exit(127);
	}
	if (handle_redirections(data->redirs) < 0)
		perror_and_exit("larrysh: redirection error");
	if (is_builtin)
		exec_builtin(data->args, env);
	else
		execute_cmd(data->args, env);
	exit(EXIT_SUCCESS);
}

static void	exec_with_redir(t_data *data, t_list **env, bool is_builtin)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
		child_process(data, env, is_builtin);
	waitpid(pid, &status, 0);
	update_exit_status(status);
}

void	ft_exec(t_list *lst, t_list **env)
{
	t_data	*data;

	data = lst->content;
	if (!lst->next && is_builtin_cmd(data->args))
	{
		if (data->redirs && data->redirs[0])
			exec_with_redir(data, env, true);
		else
			exec_builtin(data->args, env);
	}
	else if (lst->next)
		exec_pipe(lst, env);
	else
	{
		if (data->redirs && data->redirs[0])
			exec_with_redir(data, env, false);
		else
			execute_cmd(data->args, env);
	}
}
