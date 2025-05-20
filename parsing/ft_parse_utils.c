/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:04:50 by ielyatim          #+#    #+#             */
/*   Updated: 2025/05/20 14:26:59 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	__split(char *str, int (*c)[4], int *b, t_list **new)
{
	if (!(*c)[2])
	{
		if (ft_isquote(str + (*c)[0]))
			(*c)[3] = str[(*c)[0]];
		else if (ft_isdredir(str + (*c)[0]))
		{
			ft_lstadd_back(new, ft_lstnew(ft_substr(str, *b, (*c)[0] - *b)));
			ft_lstadd_back(new, ft_lstnew(ft_substr(str, (*c)[0], 2)));
			*b = ((*c)[0]++) + 2;
		}
		else if (ft_ispipe(str + (*c)[0]) || ft_issredir(str + (*c)[0]))
		{
			ft_lstadd_back(new, ft_lstnew(ft_substr(str, *b, (*c)[0] - *b)));
			ft_lstadd_back(new, ft_lstnew(ft_substr(str, (*c)[0], 1)));
			*b = (*c)[0] + 1;
		}
	}
}

t_list	*ft_lstsplit(t_list *lst)
{
	int		b;
	int		c[4];
	char	*str;
	t_list	*new;

	new = NULL;
	while (lst)
	{
		ft_bzero(c, sizeof(c));
		str = lst->content;
		b = 0;
		while (str[c[0]] != '\0')
		{
			__split(str, &c, &b, &new);
			c[2] = (c[2] + (str[c[0]] == c[3])) % 2;
			c[3] *= c[2];
			c[0]++;
		}
		ft_lstadd_back(&new, ft_lstnew(ft_substr(str, b, c[0] - b)));
		lst = lst->next;
	}
	return (new);
}

static char	*herdoc(t_cmd *cmd)
{
	char	*doc;
	char	*line;
	char	*tmp;

	if (fork() == 0)
	{
		doc = ft_strdup("");
		while (true)
		{
			ft_putstr_fd(BLACK, 1);
			ft_putstr_fd(cmd->value, 1);
			ft_putstr_fd("> " RESET, 1);
			line = get_next_line(0);
			if (!line || ft_strncmp(line, cmd->value, ft_strlen(line) - 1) == 0)
				return (free(line), doc);
			if (cmd->type != T_STRING)
				line = __expand(line);
			tmp = doc;
			doc = ft_strjoin(doc, line);
			free(line);
			free(tmp);
		}
	}
	wait(NULL);
	return (NULL);
}

static int	redirection(t_list *node)
{
	bool	isherdoc;
	char	*doc;
	t_cmd	*cmd;
	char	*tmp;

	if (!node->next)
	{
		ft_error("SyntaxError", "Unexpected token 'end'");
		return (-1);
	}
	isherdoc = ((t_cmd *)node->content)->type == T_HER_DOC;
	cmd = node->next->content;
	if (cmd->type == T_PIPE || ft_cmdis_redir(cmd) || ft_strcmp(cmd->value,
			"\n") == 0)
	{
		tmp = ft_strreplace("Unexpected token '%s'", "%s", cmd->value, 0);
		ft_error("SyntaxError", tmp);
		free(tmp);
		return (-1);
	}
	if (isherdoc)
	{
		doc = herdoc(cmd);
		if (doc)
		{
			tmp = doc;
			doc = ft_strnon_printable(doc);
			printf("%s\n", doc);
			free(tmp);
			free(doc);
			exit(0);
		}
	}
	return (0);
}

t_list	*ft_fill(t_list *__lst)
{
	char	**arr;
	t_list	*lst;
	t_list	*node;
	char	*content;

	node = __lst;
	arr = NULL;
	lst = NULL;
	while (node)
	{
		content = ((t_cmd *)node->content)->value;
		if (((t_cmd *)node->content)->type == T_PIPE && !arr)
		{
			ft_error("SyntaxError", "Unexpected token '|'");
			break ;
		}
		if (((t_cmd *)node->content)->type == T_PIPE)
		{
			ft_lstadd_back(&lst, ft_lstnew(arr));
			arr = NULL;
		}
		else if (ft_cmdis_redir((t_cmd *)node->content))
		{
			if (redirection(node) == -1)
				break ;
			node = node->next;
		}
		else
			arr = ft_strsadd(arr, ft_strdup(content));
		node = node->next;
	}
	if (arr)
		ft_lstadd_back(&lst, ft_lstnew(arr));
	return (lst);
}
