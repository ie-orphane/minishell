/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:25:13 by ielyatim          #+#    #+#             */
/*   Updated: 2025/05/20 11:47:48 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*__expand(char *str)
{
	int		c[4];
	char	*strs[4];

	ft_bzero(c, sizeof(c));
	while (str[c[0]])
	{
		if (!c[2] && ft_isquote(str + c[0]))
			c[3] = str[c[0]];
		if (!(c[2] && c[3] == '\'') && str[c[0]] == '$')
		{
			strs[2] = env_key(str + c[0]);
			if (ft_strlen(strs[2]) == 1)
				return (free(strs[2]), str);
			strs[3] = env_value(strs[2]);
			strs[1] = str;
			str = ft_strreplace(str, strs[2], strs[3], c[0]);
			c[0] += ft_strlen(strs[3]) - 1;
			free(strs[1]);
			free(strs[2]);
		}
		c[2] = (c[2] + (str[c[0]] == c[3])) % 2;
		c[3] *= c[2];
		c[0]++;
	}
	return (str);
}

t_list	*ft_spell(const char *str)
{
	int		c[4];
	t_list	*lst;

	ft_bzero(c, sizeof(c));
	lst = NULL;
	while (str[c[0]] != '\0')
	{
		if (str[c[0]] != ' ')
		{
			c[1] = 0;
			while (str[c[0]] != '\0' && (str[c[0]] != ' ' || c[2]))
			{
				if (!c[2] && ft_isquote(str + c[0]))
					c[3] = str[c[0]];
				c[2] = (c[2] + (str[c[0]] == c[3])) % 2;
				c[3] *= c[2];
				c[0]++;
				c[1]++;
			}
			ft_lstadd_back(&lst, ft_lstnew(ft_substr(str, c[0] - c[1], c[1])));
		}
		if (str[c[0]] != '\0')
			c[0]++;
	}
	return (lst);
}

t_list	*ft_identify(t_list *lst)
{
	t_list	*new;
	t_cmd	*cmd;

	new = NULL;
	while (lst)
	{
		cmd = malloc(sizeof(t_cmd));
		if (!cmd)
			return (NULL);
		if (ft_strlen(lst->content) == 0)
			cmd->type = T_EMPTY;
		else if (ft_strcmp(lst->content, "|") == 0)
			cmd->type = T_PIPE;
		else if (ft_strcmp(lst->content, "<<") == 0)
			cmd->type = T_HER_DOC;
		else if (ft_strcmp(lst->content, ">") == 0)
			cmd->type = T_OUTPUT;
		else if (ft_strcmp(lst->content, ">>") == 0)
			cmd->type = T_APPEND;
		else if (ft_strcmp(lst->content, "<") == 0)
			cmd->type = T_INPUT;
		else if (ft_strchr(lst->content, '\'') || ft_strchr(lst->content, '\"'))
			cmd->type = T_STRING;
		else
			cmd->type = T_ARG;
		cmd->value = ft_strdup(lst->content);
		ft_lstadd_back(&new, ft_lstnew(cmd));
		lst = lst->next;
	}
	return (new);
}

void	__trim(t_cmd *prev, t_cmd *cmd)
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

void	ft_lstexpand(t_list **lst)
{
	t_list	*tmp;
	t_cmd	*cmd;
	t_cmd	*prev;
	char	**arr;
	size_t	i;

	tmp = *lst;
	prev = NULL;
	while (tmp)
	{
		cmd = tmp->content;
		if (!prev || prev->type != T_HER_DOC)
			cmd->value = __expand(cmd->value);
		if (prev && (prev->type == T_APPEND || prev->type == T_OUTPUT
				|| prev->type == T_INPUT) && (ft_strlen(cmd->value) == 0
				|| ft_strchr(cmd->value, ' ')))
			cmd->type = T_NULL;
		else if (prev && ft_strlen(cmd->value) == 0)
			cmd->type = T_NONE;
		else if (cmd->type != T_STRING && ft_strchr(cmd->value, ' '))
		{
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
					cmd = malloc(sizeof(t_cmd));
					cmd->type = T_ARG;
					cmd->value = arr[i];
					ft_lstinsert(&tmp, ft_lstnew(cmd));
					tmp = tmp->next;
				}
				i++;
			}
			free(arr);
		}
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
	lst = ft_identify(lst);
	ft_lstclear(&tmp, free);
	ft_lstexpand(&lst);
	ft_lstremove_if(&lst, &((t_cmd){.type = T_NONE}), ft_cmdcmp_type,
		ft_cmdfree);
	ft_cmditer(&lst, &__trim);
	// ft_lstremove_if(&lst, &((t_cmd){.type = T_EMPTY}), ft_cmdcmp_type,
	// 	ft_cmdfree);
	tmp = lst;
	lst = ft_fill(lst);
	ft_lstclear(&tmp, ft_cmdfree);
	return (lst);
}
