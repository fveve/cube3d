/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joncurci <joncurci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 10:20:51 by arafa             #+#    #+#             */
/*   Updated: 2024/09/03 19:09:51 by joncurci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

/*char	*get_next_line(int fd, int to_copy)
{
	static char		buffer[42];
	char			*line;
	char			*new_line;
	int				countread;

	line = ft_strdup(buffer);
	while (!(new_line = ft_strchr(line, '\n')) && (countread = read(fd, buffer, 42)))
	{
		buffer[countread] = '\0';
		line = ft_strjoin(line, buffer);
	}
	if (!ft_strlen(line))
		return (free(line), NULL);
	if (new_line)
	{
		to_copy = new_line - line + 1;
		ft_strcpy(buffer, new_line + 1);
	}
	else
	{
		to_copy = ft_strlen(line);
		buffer[0] = '\0';
	}
	line[to_copy] = '\0';
	return (line);
}*/

char	*ft_strdup(const char *str)
{
	size_t	i;
	size_t	srclen;
	char	*dup;

	i = 0;
	srclen = ft_strlen((char *)str);
	dup = malloc(sizeof(char) * (srclen + 1));
	if (!dup)
		return (NULL);
	while (str[i])
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	totlen;
	char	*join;

	i = 0;
	j = 0;
	totlen = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	join = (char *)malloc(sizeof(char) * (totlen + 1));
	if (!join)
		return (NULL);
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		join[i] = s2[j];
		j++;
		i++;
	}
	join[i] = '\0';
	return (join);
}

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

char	*ft_substr(char const *s, /*unsigned */int start, /*size_t*/int len)
{
	size_t	i;
	size_t	sublen;
	char	*sub;

	i = 0;
	if (start >= /*(unsigned int)*/ft_strlen((char *)s))
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