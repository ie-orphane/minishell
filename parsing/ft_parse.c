/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:25:13 by ielyatim          #+#    #+#             */
/*   Updated: 2025/05/08 09:26:17 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_lstshow(t_list *lst)
{
	printf("{\n");
	while (lst)
	{
		printf("  %s,\n", (char *)lst->content);
		lst = lst->next;
	}
	printf("}\n");
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
				if (!c[2] && (str[c[0]] == '\'' || str[c[0]] == '\"'))
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

void	ft_lstexpand(t_list **__lst)
{
	int		i[2];
	char	*strs[4];
	t_list	*lst;

	lst = *__lst;
	while (lst)
	{
		i[0] = 0;
		strs[0] = lst->content;
		while (strs[0][i[0]])
		{
			if (strs[0][i[0]++] != '$')
				continue ;
			i[1] = 0;
			while (strs[0][i[0] + i[1]] && strs[0][i[0] + i[1]] != ' ')
				i[1]++;
			strs[2] = ft_substr(strs[0], i[0] - 1, i[1] + 1);
			strs[3] = getenv(strs[2] + 1);
			if (!strs[3])
				strs[3] = "";
			strs[1] = lst->content;
			lst->content = ft_strreplace(strs[0], strs[2], strs[3]);
			free(strs[1]);
			free(strs[2]);
			i[0] += i[1] + ft_strlen(strs[3]);
		}
		lst = lst->next;
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
			if (!c[2])
			{
				if (str[c[0]] == '\'' || str[c[0]] == '\"')
					c[3] = str[c[0]];
				else if (str[c[0]] == '|' || str[c[0]] == '<'
					|| str[c[0]] == '>')
				{
					ft_lstadd_back(&new, ft_lstnew(ft_substr(str, b, c[0]
								- b)));
					ft_lstadd_back(&new, ft_lstnew(ft_substr(str, c[0], 1)));
					b = c[0] + 1;
				}
			}
			c[2] = (c[2] + (str[c[0]] == c[3])) % 2;
			c[3] *= c[2];
			c[0]++;
		}
		if (c[2] && c[3])
			return (ft_lstclear(&new, free), NULL);
		ft_lstadd_back(&new, ft_lstnew(ft_substr(str, b, c[0] - b)));
		lst = lst->next;
	}
	return (new);
}

void	ft_trim(t_list **ptr)
{
	t_list	*lst;
	char	*str;
	int		c[5];
	char	*tmp;
	char	*s;

	lst = *ptr;
	while (lst)
	{
		ft_bzero(c, sizeof(c));
		str = lst->content;
		s = ft_strdup("");
		while (str[c[0]] != '\0')
		{
			if (!c[2] && (str[c[0]] == '\'' || str[c[0]] == '\"'))
			{
				c[3] = str[c[0]];
				c[4] = c[0];
			}
			else if (!c[2] || str[c[0]] != c[3])
			{
				tmp = s;
				s = ft_strjoinc(s, str[c[0]]);
				free(tmp);
			}
			c[2] = (c[2] + (str[c[0]] == c[3])) % 2;
			c[3] *= c[2];
			c[0]++;
		}
		lst->content = s;
		free(str);
		lst = lst->next;
	}
}

t_list	*ft_parse(char *line)
{
	t_list	*lst;
	t_list	*tmp;

	lst = NULL;
	lst = ft_spell(line);
	ft_lstexpand(&lst);
	tmp = lst;
	lst = ft_lstsplit(lst);
	ft_lstclear(&tmp, free);
	if (!lst)
		return (printf("SyntaxError: Unclosed quote.\n"), NULL);
	ft_trim(&lst);
	ft_lstremove_if(&lst, "", ft_strcmp);
	ft_lstshow(lst);
	return (lst);
}
