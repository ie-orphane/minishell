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

void	exec_builtin(t_list **lst, t_list **env)
{
	t_data	*data;

	data = (*lst)->content;
	if (ft_strcmp(*data->args, "echo") == 0)
		ft_echo(data->args);
	else if (ft_strcmp(*data->args, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(*data->args, "cd") == 0)
		ft_cd(data->args, *env);
	else if (ft_strcmp(*data->args, "export") == 0)
		ft_export(data->args + 1, env);
	else if (ft_strcmp(*data->args, "unset") == 0)
		ft_unset(data->args + 1, env);
	else if (ft_strcmp(*data->args, "env") == 0)
		ft_env(*env);
	else if (ft_strcmp(*data->args, "exit") == 0)
		ft_exit(lst);
}

void	execute_cmd(char **args, t_list **env)
{
	if (!is_valid_command(args[0], *env))
	{
		print_error(args[0], "command not found");
		__exit(127);
	}
	ft_execvpe(args[0], args, env);
	perror("larrysh");
	__exit(127);
}

static void	execute(char **args, char **redirs, t_list **env)
{
	pid_t	pid;
	int		status;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (handle_redirections(redirs) < 0)
			perror_and_exit("larrysh: redirection error");
		execute_cmd(args, env);
		__exit(EXIT_SUCCESS);
	}
	waitpid(pid, &status, 0);
	update_exit_status(status);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
}

void	ft_exec(t_list **lst, t_list **env)
{
	t_data	*data;
	int		saved_stdout;
	int		saved_stdin;

	data = (*lst)->content;
	if ((*lst)->next)
		exec_pipe(*lst);
	else if (is_builtin_cmd(data->args))
	{
		saved_stdout = dup(STDOUT_FILENO);
		saved_stdin = dup(STDIN_FILENO);
		if (handle_redirections(data->redirs) < 0)
			perror("larrysh: redirection error");
		else
			exec_builtin(lst, env);
		dup2(saved_stdout, STDOUT_FILENO);
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdout);
		close(saved_stdin);
	}
	else
		execute(data->args, data->redirs, env);
	ft_lstclear(lst, ft_dataclear);
}
