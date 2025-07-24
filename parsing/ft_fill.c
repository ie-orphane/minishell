/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:53:53 by ielyatim          #+#    #+#             */
/*   Updated: 2025/07/24 10:45:46 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	_sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	exit(130);
}

static void	__herdoc(t_cmd *cmd, int fd)
{
	char	*line;
	char	*tmp;
	int		status;

	signal(SIGINT, SIG_IGN);
	if (fork() == 0)
	{
		signal(SIGINT, _sigint_handler);
		while (true)
		{
			tmp = ft_strreplace(BLACK "%s> " RESET, "%s", cmd->value, 0);
			line = readline(tmp);
			free(tmp);
			if (!line)
			{
				tmp = ft_strreplace("Unexpected end of file (wanted '" BLACK "%s" RESET "')",
						"%s", cmd->value, 0);
				ft_error("EOFError", tmp);
				free(tmp);
			}
			if (!line || ft_strcmp(line, cmd->value) == 0)
				break ;
			if (cmd->type != T_STRING)
				line = expand(line);
			ft_putstr_fd(line, fd);
			ft_putstr_fd("\n", fd);
			free(line);
		}
		free(line);
		exit(0);
	}
	else
	{
		wait(&status);
		g_exit_status = WEXITSTATUS(status);
	}
	signal(SIGINT, sigint_handler);
}

void	__fdoc(char ***redirs, t_cmd *next_cmd)
{
	int		fd;
	char	*tmp;
	char	*path;

	tmp = ft_strrand(7);
	path = ft_strjoin("/tmp/", tmp);
	free(tmp);
	fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	__herdoc(next_cmd, fd);
	close(fd);
	(*redirs) = ft_strsadd((*redirs), ft_strdup("<<"));
	(*redirs) = ft_strsadd((*redirs), path);
}

static bool	__redir(t_list *node, char ***redirs)
{
	t_cmd	*next_cmd;
	char	*tmp;

	next_cmd = node->next->content;
	if (next_cmd->type == T_PIPE || ft_cmdis_redir(next_cmd)
		|| ft_strcmp(next_cmd->value, "\n") == 0)
	{
		tmp = ft_strreplace("Unexpected token '%s'", "%s", next_cmd->value, 0);
		ft_error("SyntaxError", tmp);
		return (free(tmp), true);
	}
	if (((t_cmd *)node->content)->type == T_HER_DOC)
	{
		__fdoc(redirs, next_cmd);
		return (false);
	}
	(*redirs) = ft_strsadd((*redirs),
			ft_strdup(((t_cmd *)node->content)->value));
	(*redirs) = ft_strsadd((*redirs), ft_strdup(next_cmd->value));
	return (false);
}

static bool	__fill(t_list **__lst, t_list **lst, char ***args, char ***redirs)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)(*__lst)->content;
	if ((cmd)->type == T_PIPE && !(*args))
	{
		ft_error("SyntaxError", "Unexpected token '|'");
		return (true);
	}
	if ((cmd)->type == T_PIPE)
	{
		ft_lstadd_back(lst, ft_lstnew(ft_data_new((*args), (*redirs))));
		(*args) = NULL;
		(*redirs) = NULL;
	}
	else if (ft_cmdis_redir(cmd))
	{
		if (!((*__lst)->next))
			return (ft_error("SyntaxError", "Unexpected token 'newline'"),
				true);
		if (__redir((*__lst), redirs))
			return (true);
		(*__lst) = (*__lst)->next;
	}
	else
		(*args) = ft_strsadd((*args), ft_strdup((cmd)->value));
	return (false);
}

t_list	*ft_fill(t_list *__lst)
{
	char	**args;
	char	**redirs;
	t_list	*lst;

	args = NULL;
	redirs = NULL;
	lst = NULL;
	while (__lst)
	{
		if (__fill(&__lst, &lst, &args, &redirs))
			break ;
		__lst = __lst->next;
	}
	if (args || redirs)
		ft_lstadd_back(&lst, ft_lstnew(ft_data_new(args, redirs)));
	return (lst);
}
