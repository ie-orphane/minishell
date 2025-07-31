/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 17:04:50 by ielyatim          #+#    #+#             */
/*   Updated: 2025/07/21 14:59:35 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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

char	*expand(char *str)
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
			strs[3] = env_value(strs[2]);
			strs[1] = str;
			str = ft_strreplace(str, strs[2], strs[3], c[0]);
			c[0] += ft_strlen(strs[3]) - 1;
			free(strs[1]);
			free(strs[2]);
			free(strs[3]);
		}
		if (c[0] >= 0)
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
