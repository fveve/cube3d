/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 14:47:22 by arafa             #+#    #+#             */
/*   Updated: 2024/09/09 12:20:58 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	ft_strlen(const char *s)
{
	int	x;

	x = 0;
	if (!s)
		return (0);
	while (s[x])
		x++;
	return (x);
}

void	ft_strcpy(char *dest, const char *src)
{
	if (!src)
		return ;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
}
