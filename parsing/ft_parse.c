/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:25:13 by ielyatim          #+#    #+#             */
/*   Updated: 2025/07/21 14:58:39 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	__trim(t_cmd *prev, t_cmd *cmd)
{
	int		c[5];
	char	*s[3];

	if (cmd->type != T_STRING)
		return ;
	ft_bzero(c, sizeof(c));
	s[1] = ft_strdup("");
	while (cmd->value[c[0]] != '\0')
	{
		if (!c[2] && ft_isquote(cmd->value + c[0]))
		{
			c[3] = cmd->value[c[0]];
			c[4] = c[0];
		}
		else if (!c[2] || cmd->value[c[0]] != c[3])
		{
			s[2] = s[1];
			s[1] = ft_strjoinc(s[1], cmd->value[c[0]]);
			free(s[2]);
		}
		c[2] = (c[2] + (cmd->value[c[0]] == c[3])) % 2;
		c[3] *= c[2];
		c[0]++;
	}
	s[2] = cmd->value;
	cmd->value = s[1];
	free(s[2]);
	if (ft_strlen(s[1]) == 0 && !(prev && ft_cmdis_redir(prev)))
		cmd->type = T_EMPTY;
}

void	__new(t_list **tmp, t_cmd *cmd)
{
	char	**arr;
	size_t	i;

	arr = ft_split(cmd->value, "\n\t ");
	i = 0;
	while (arr[i])
	{
		if (i == 0)
		{
			free(cmd->value);
			cmd->value = arr[i];
		}
		else
		{
			cmd = ft_cmdnew(arr[i]);
			cmd->type = T_ARG;
			ft_lstinsert(tmp, ft_lstnew(cmd));
			tmp = &(*tmp)->next;
		}
		i++;
	}
	free(arr);
}

void	ft_lstexpand(t_list **lst)
{
	t_list	*tmp;
	t_cmd	*cmd;
	t_cmd	*prev;

	tmp = *lst;
	prev = NULL;
	while (tmp)
	{
		cmd = tmp->content;
		if (!prev || prev->type != T_HER_DOC)
			cmd->value = expand(cmd->value);
		if (prev && (prev->type == T_APPEND || prev->type == T_OUTPUT
				|| prev->type == T_INPUT) && (ft_strlen(cmd->value) == 0
				|| ft_strchr(cmd->value, ' ')))
			cmd->type = T_NULL;
		else if (prev && ft_strlen(cmd->value) == 0)
			cmd->type = T_NONE;
		else if (cmd->type != T_STRING && ft_strchr(cmd->value, ' '))
			__new(&tmp, cmd);
		prev = tmp->content;
		tmp = tmp->next;
	}
}

t_list	*ft_parse(char *line)
{
	t_list	*lst;
	t_list	*tmp;

	lst = ft_spell(line);
	tmp = lst;
	lst = ft_lstsplit(lst);
	ft_lstclear(&tmp, free);
	ft_lstremove_if(&lst, "", ft_strcmp, free);
	tmp = lst;
	lst = ft_lstmap(lst, (void *(*)(void *))ft_cmdnew, free);
	ft_lstclear(&tmp, free);
	ft_lstexpand(&lst);
	ft_lstremove_if(&lst, &((t_cmd){.type = T_NONE}), ft_cmdcmp_type,
		ft_cmdfree);
	ft_cmditer(&lst, &__trim);
	tmp = lst;
	lst = ft_fill(lst);
	ft_lstclear(&tmp, ft_cmdfree);
	return (lst);
}
