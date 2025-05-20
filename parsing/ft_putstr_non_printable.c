/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_non_printable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:02:56 by ielyatim          #+#    #+#             */
/*   Updated: 2025/05/20 12:01:43 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr_non_printable(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (' ' <= str[i] && str[i] <= '~')
		{
			ft_putchar(str[i++]);
			continue ;
		}
		ft_putchar('\\');
		if (str[i] == '\n')
			ft_putchar('n');
		else if (str[i] == '\t')
			ft_putchar('t');
		else if (str[i] == '\r')
			ft_putchar('r');
		else
		{
			ft_putchar('\\');
			ft_putchar("0123456789abcdef"[(unsigned char)str[i] / 16]);
			ft_putchar("0123456789abcdef"[(unsigned char)str[i] % 16]);
		}
		i++;
	}
}

static char	*__join(char *str, char c)
{
	char	*tmp;

	tmp = str;
	str = ft_strjoinc(str, c);
	free(tmp);
	return (str);
}

char	*ft_strnon_printable(char *__str)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_strdup("");
	while (__str[i] != '\0')
	{
		if (' ' <= __str[i] && __str[i] <= '~')
		{
			str = __join(str, __str[i++]);
			continue ;
		}
		str = __join(str, '\\');
		if (ft_strchr("\n\t\r", __str[i]))
		{
			str = __join(str, (char []){['\n'] = 'n', ['\r'] = 'r',
				['\t'] = 't'}[(int)__str[i++]]);
			continue ;
		}
		str = __join(str, "0123456789abcdef"[(unsigned char)__str[i] / 16]);
		str = __join(str, "0123456789abcdef"[(unsigned char)__str[i++] % 16]);
	}
	return (str);
}
