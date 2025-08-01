/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 11:17:07 by ielyatim          #+#    #+#             */
/*   Updated: 2025/08/01 15:08:20 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrand(size_t len)
{
	int		fd;
	ssize_t	bytes_read;
	char	buffer;
	char	*str;

	fd = open("/dev/random", O_RDONLY);
	if (fd == -1)
		return (perror("open"), NULL);
	str = ft_strdup("");
	while (true)
	{
		bytes_read = read(fd, &buffer, 1);
		if (bytes_read == -1)
			return (perror("read"), close(fd), NULL);
		if (bytes_read == 0)
			break ;
		if (ft_isalnum(buffer) || buffer == '_')
		{
			str = ft_strjoinc(str, buffer);
			if (ft_strlen(str) == len)
				break ;
		}
	}
	return (close(fd), str);
}
