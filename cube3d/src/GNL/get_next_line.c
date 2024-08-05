/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 10:20:51 by arafa             #+#    #+#             */
/*   Updated: 2024/07/04 16:57:21 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char *get_next_line(int fd, int to_copy)
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
}
