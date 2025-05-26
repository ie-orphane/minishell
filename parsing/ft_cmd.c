/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 16:54:22 by ielyatim          #+#    #+#             */
/*   Updated: 2025/05/20 11:47:55 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_cmdcmp_type(t_cmd *ref, t_cmd *cmd)
{
	return (cmd->type != ref->type);
}

void	ft_cmdshow(t_list *lst)
{
	const char	*types[] = {[T_PIPE] = "PIPE", [T_HER_DOC] = "HER_DOC",
	[T_APPEND] = "APPEND", [T_INPUT] = "INPUT", [T_STRING] = "STRING",
	[T_OUTPUT] = "OUTPUT", [T_ARG] = "ARG", [T_EMPTY] = "EMPTY",
	[T_NONE] = "NONE", [T_NULL] = "NULL"};

	printf("{\n");
	while (lst)
	{
		printf("  %s: %s,\n", types[((t_cmd *)lst->content)->type],
			((t_cmd *)lst->content)->value);
		lst = lst->next;
	}
	printf("}\n");
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
