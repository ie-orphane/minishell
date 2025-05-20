/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove_if.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:19:41 by ielyatim          #+#    #+#             */
/*   Updated: 2025/05/19 21:48:32 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstremove_if(t_list **lst, void *ref, int (*cmp)(),
		void (*del)(void *))
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
		if (cmp(ref, current->content) != 0)
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
		ft_lstdelone(tmp, del);
	}
}
