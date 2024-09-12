/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joncurci <joncurci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 10:20:51 by arafa             #+#    #+#             */
/*   Updated: 2024/09/11 16:07:06 by joncurci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

size_t	substrlen(char const *s, unsigned int start, size_t len)
{
	size_t	i;

	i = start;
	while (s[i] && ((i - start) < len))
	{
		i++;
	}
	return (i - start);
}

char	*ft_substr(char const *s, int start, int len)
{
	size_t	i;
	size_t	sublen;
	char	*sub;

	i = 0;
	if (start >= ft_strlen((char *)s))
	{
		return (ft_strdup(""));
	}
	sublen = substrlen(s, start, len);
	sub = (char *)malloc(sizeof(char) * (sublen + 1));
	if (!sub)
		return (NULL);
	while (i < sublen)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*add_line(int fd, char *buff, char *savedline)
{
	int		readline;
	char	*templine;

	readline = 1;
	while (readline != 0)
	{
		readline = read(fd, buff, BUFFER_SIZE);
		if (readline == -1)
			return (0);
		else if (readline == 0)
			break ;
		buff[readline] = '\0';
		if (!savedline)
			savedline = ft_strdup("");
		templine = savedline;
		savedline = ft_strjoin(templine, buff);
		free(templine);
		templine = NULL;
		if (ft_strchr(buff, '\n'))
			break ;
	}
	return (savedline);
}

static char	*cutline(char *read_line)
{
	size_t	i;
	char	*saved;

	i = 0;
	while (read_line[i] != '\n' && read_line[i] != '\0')
		i++;
	if (read_line[i] == '\0')
		return (0);
	saved = ft_substr(read_line, i + 1, ft_strlen(read_line) - i);
	if (*saved == '\0')
	{
		free(saved);
		saved = NULL;
	}
	read_line[i + 1] = '\0';
	return (saved);
}

char	*get_next_line(int fd)
{
	char		*buff;
	char		*read_line;
	static char	*savedline;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buff = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	read_line = add_line(fd, buff, savedline);
	free(buff);
	buff = NULL;
	if (!read_line)
	{
		if (savedline)
		{
			free(savedline);
			savedline = NULL;
		}
		free(buff);
		return (NULL);
	}
	savedline = cutline(read_line);
	return (read_line);
}
