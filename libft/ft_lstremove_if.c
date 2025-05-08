/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove_if.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:19:41 by ielyatim          #+#    #+#             */
/*   Updated: 2025/05/01 19:06:57 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_lstremove_if(t_list **lst, void *ref, int (*cmp)())
{
	t_list	*current;
	t_list	*prev;
	t_list	*tmp;

	if (!lst || !*lst || !cmp)
		return ;
	current = *lst;
	prev = NULL;
	while (current)
	{
		if (cmp(current->content, ref) != 0)
		{
			prev = current;
			current = current->next;
			continue ;
		}
		tmp = current;
		if (prev)
			prev->next = current->next;
		else
			*lst = current->next;
		current = current->next;
		free(tmp->content);
		free(tmp);
	}
}

t_list	*ft_lstnew(void *content)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (list != NULL)
	{
		list->content = content;
		list->next = NULL;
	}
	return (list);
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current_lst;
	t_list	*tmp;

	if (lst && del)
	{
		current_lst = (*lst);
		while (current_lst)
		{
			del(current_lst->content);
			tmp = current_lst->next;
			free(current_lst);
			current_lst = tmp;
		}
		*lst = NULL;
	}
}

t_list	*ft_lstlast(t_list *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
	}
	return (lst);
}
