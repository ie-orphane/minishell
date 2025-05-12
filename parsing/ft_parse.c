/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 09:25:13 by ielyatim          #+#    #+#             */
/*   Updated: 2025/05/12 18:59:09 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static char	*__expand(char *str)
{
	int		c[4];
	char	*strs[4];

	ft_bzero(c, sizeof(c));
	while (str[c[0]])
	{
		if (!c[2] && str[c[0]] == '\'')
			c[3] = str[c[0]];
		if (!c[2] && c[3] != '\'' && str[c[0]] == '$')
		{
			strs[2] = env_key(str + c[0]);
			c[0]++;
			strs[3] = env_value(strs[2]);
			strs[1] = str;
			str = ft_strreplace(str, strs[2], strs[3]);
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
		lst->content = __expand(lst->content);
		str = lst->content;
		b = 0;
		while (str[c[0]] != '\0')
		{
			__split(str, &c, &b, &new);
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
			if (!c[2] && ft_isquote(str + c[0]))
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
	tmp = lst;
	lst = ft_lstsplit(lst);
	ft_lstclear(&tmp, free);
	if (!lst)
		return (ft_error("SyntaxError", "Unclosed quote"), NULL);
	ft_trim(&lst);
	ft_lstremove_if(&lst, "", ft_strcmp);
	tmp = lst;
	lst = ft_fill(lst);
	ft_lstclear(&tmp, free);
	return (lst);
}
