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

/**
 * @brief Removes all nodes from te list `lst` that match the given reference
 * 	  value `ref` using the provided comparison function `cmp`.
 *    The content of the removed nodes is deleted using the provided delete
 *    function `del`.
 * 
 * 
 * ```c
 * // Example usage:
 * int	ft_cmp(int *ref, char *content)
 * {
 * 	char * tmp = ft_itoa(*ref);
 * 	int cmp = ft_strcmp(tmp, content);
 * 	free(tmp);
 * 	return (cmp);
 * }
 * 
 * t_list *lst = NULL;
 * for (int i = 0; i < 5; i++)
 * 	ft_lstadd_back(&lst, ft_lstnew(ft_itoa(i)));
 * // "1" -> "2" -> "3" -> "4" -> NULL
 * 
 * int ref = 2;
 * ft_lstremove_if(&lst, &ref, ft_cmp, free);
 * // "1" -> "3" -> "4" -> NULL
 * ```
 * 
 * @param lst A pointer to the head of the list.
 * @param ref The reference value to compare against.
 * @param cmp A function pointer to the comparison function.
 * @param del A function pointer to the delete function for the content.
 */
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
