/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mb11junior <mb11junior@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:53:53 by ielyatim          #+#    #+#             */
/*   Updated: 2025/07/31 15:17:51 by mb11junior       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static void	__herdoc(t_cmd *cmd, int fd)
{
	char	*line;

	signal(SIGINT, _sigint_handler);
	while (true)
	{
		line = readline(ft_strreplace(BLACK "%s> " RESET, "%s", cmd->value, 0));
		if (!line)
			ft_err(ft_strreplace("unexpected end of file (wanted '"
					BLACK "%s" RESET "')", "%s", cmd->value, 0));
		if (!line || ft_strcmp(line, cmd->value) == 0)
			break ;
		if (cmd->type != T_STRING)
			line = expand(line);
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
	}
	__exit(0);
}

static void	__fdoc(char ***redirs, t_cmd *next_cmd)
{
	int		fd;
	char	*path;
	int		status;

	path = ft_strjoin("/tmp/", ft_strrand(7));
	fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	signal(SIGINT, SIG_IGN);
	if (fork() == 0)
		__herdoc(next_cmd, fd);
	else
	{
		wait(&status);
		g_global.exit_status = WEXITSTATUS(status);
	}
	signal(SIGINT, sigint_handler);
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
		tmp = ft_strreplace("unexpected token '%s'", "%s", next_cmd->value, 0);
		ft_err(tmp);
		return (true);
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
		return (ft_err("unexpected token '|'"), true);
	if ((cmd)->type == T_PIPE)
	{
		ft_lstadd_back(lst, ft_lstnew(ft_datanew((*args), (*redirs))));
		(*args) = NULL;
		(*redirs) = NULL;
	}
	else if (ft_cmdis_redir(cmd))
	{
		if (!((*__lst)->next))
			return (ft_err("unexpected token 'newline'"), true);
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
		ft_lstadd_back(&lst, ft_lstnew(ft_datanew(args, redirs)));
	return (lst);
}
