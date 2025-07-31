/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mb11junior <mb11junior@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:54:22 by ielyatim          #+#    #+#             */
/*   Updated: 2025/07/31 14:44:22 by mb11junior       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_cmdcmp_type(t_cmd *ref, t_cmd *cmd)
{
	return (cmd->type != ref->type);
}

t_cmd	*ft_cmdnew(char *value)
{
	t_cmd	*cmd;
	t_type	type;

	cmd = ft_malloc(sizeof(t_cmd));
	if (ft_strlen(value) == 0)
		type = T_EMPTY;
	else if (ft_strcmp(value, "|") == 0)
		type = T_PIPE;
	else if (ft_strcmp(value, "<<") == 0)
		type = T_HER_DOC;
	else if (ft_strcmp(value, ">") == 0)
		type = T_OUTPUT;
	else if (ft_strcmp(value, ">>") == 0)
		type = T_APPEND;
	else if (ft_strcmp(value, "<") == 0)
		type = T_INPUT;
	else if (ft_strchr(value, '\'') || ft_strchr(value, '\"'))
		type = T_STRING;
	else
		type = T_ARG;
	cmd->type = type;
	cmd->value = ft_strdup(value);
	return (cmd);
}

void	ft_cmdfree(void *content)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)content;
	free(cmd->value);
	free(cmd);
}

bool	ft_cmdis_redir(t_cmd *cmd)
{
	return (cmd->type == T_HER_DOC || cmd->type == T_APPEND
		|| cmd->type == T_INPUT || cmd->type == T_OUTPUT);
}

void	ft_cmditer(t_list **lst, void (*f)(t_cmd *prev, t_cmd *cmd))
{
	t_list	*tmp;
	t_cmd	*prev;

	tmp = *lst;
	prev = NULL;
	while (tmp)
	{
		f(prev, tmp->content);
		prev = tmp->content;
		tmp = tmp->next;
	}
}
