/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 14:53:53 by ielyatim          #+#    #+#             */
/*   Updated: 2025/07/21 14:57:50 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*__herdoc(t_cmd *cmd)
{
	char	*doc;
	char	*line;
	char	*tmp;

	if (fork() != 0)
	{
		doc = ft_strdup("");
		while (true)
		{
			ft_putstrs_fd((char *[]){BLACK, cmd->value, "> ", RESET, NULL}, 1);
			line = get_next_line(0);
			tmp = ft_strtrim(line, "\n");
			if (!line || ft_strcmp(tmp, cmd->value) == 0)
				return (free(tmp), get_next_line(-1), free(line), doc);
			free(tmp);
			if (cmd->type != T_STRING)
				line = expand(line);
			tmp = doc;
			doc = ft_strjoin(doc, line);
			free(line);
			free(tmp);
		}
	}
	wait(NULL);
	exit(0);
}

static void	__fdoc(char *redir, char ***redirs, char *doc)
{
	int		fd;
	char	*tmp;
	char	*path;

	tmp = ft_strrand(7);
	path = ft_strjoin("/tmp/", tmp);
	free(tmp);
	fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	ft_putstr_fd(doc, fd);
	close(fd);
	(*redirs) = ft_strsadd((*redirs), ft_strdup(redir));
	(*redirs) = ft_strsadd((*redirs), path);
	free(doc);
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
		return (__fdoc(((t_cmd *)node->content)->value, redirs,
				__herdoc(next_cmd)), false);
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
	if (args)
		ft_lstadd_back(&lst, ft_lstnew(ft_data_new(args, redirs)));
	return (lst);
}
