/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielyatim <ielyatim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:29:40 by mb11junior        #+#    #+#             */
/*   Updated: 2025/08/01 16:27:55 by ielyatim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

bool	has_output_redirection(char **redirs)
{
	int	i;

	if (!redirs)
		return (false);
	i = 0;
	while (redirs[i])
	{
		if (!ft_strcmp(redirs[i], ">") || !ft_strcmp(redirs[i], ">>"))
			return (true);
		i++;
	}
	return (false);
}

bool	has_input_redirection(char **redirs)
{
	int	i;

	if (!redirs)
		return (false);
	i = 0;
	while (redirs[i])
	{
		if (!ft_strcmp(redirs[i], "<") || !ft_strcmp(redirs[i], "<<"))
			return (true);
		i++;
	}
	return (false);
}

static bool	handle_inout(char *file, int flags, int std)
{
	int	fd;

	fd = open(file, flags, 0644);
	if (fd < 0)
		return (true);
	if (dup2(fd, std) < 0)
		return (close(fd), true);
	close(fd);
	return (false);
}

static char	*filename(char *str)
{
	int		c[5];
	char	*s;

	if ((ft_strcmp("\"\"", str) == 0 || (ft_strchr(str, ' ') && *(str) != '\"'
				&& *(str + ft_strlen(str) - 1) != '\"')))
	{
		ft_err("ambiguous redirect");
		return (NULL);
	}
	ft_bzero(c, sizeof(c));
	s = ft_strdup("");
	while (str[c[0]] != '\0')
	{
		if (!c[2] && ft_isquote(str + c[0]))
		{
			c[3] = str[c[0]];
			c[4] = c[0];
		}
		else if (!c[2] || str[c[0]] != c[3])
			s = ft_strjoinc(s, str[c[0]]);
		c[2] = (c[2] + (str[c[0]] == c[3])) % 2;
		c[3] *= c[2];
		c[0]++;
	}
	return (s);
}

bool	handle_redirections(char **args)
{
	bool	error;
	char	*f;

	error = false;
	while (args && *args)
	{
		if (ft_isredir(*args))
			f = filename(ft_strtrim(*(args + 1), " "));
		if (!f)
			return (false);
		if (!ft_strcmp(*args, "<") || !ft_strcmp(*args, "<<"))
			error = handle_inout(f, O_RDONLY, STDIN_FILENO);
		else if (!ft_strcmp(*args, ">"))
			error = handle_inout(f, O_WRONLY | O_CREAT | O_TRUNC,
					STDOUT_FILENO);
		else if (!ft_strcmp(*args, ">>"))
			error = handle_inout(f, O_WRONLY | O_CREAT | O_APPEND,
					STDOUT_FILENO);
		if (error)
			break ;
		args++;
	}
	if (error)
		perror(RED "larrysh: redir error: " RESET);
	return (!error);
}
