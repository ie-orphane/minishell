/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mb11junior <mb11junior@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 14:36:38 by mb11junior        #+#    #+#             */
/*   Updated: 2025/07/31 15:21:41 by mb11junior       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

void	*ft_malloc(size_t size)
{
	static t_list	*head;
	t_list			*new;
	void			*ptr;

	if (size == 0)
	{
		ft_lstclear(&head, free);
		return (NULL);
	}
	ptr = malloc(size);
	if (!ptr)
		return (ft_lstclear(&head, free), exit(EXIT_FAILURE), NULL);
	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
	{
		return (ft_lstclear(&head, free), exit(EXIT_FAILURE), NULL);
	}
	new->content = ptr;
	new->next = NULL;
	ft_lstadd_back(&head, new);
	return (ptr);
}
