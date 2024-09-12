/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_tools2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 16:08:53 by arafa             #+#    #+#             */
/*   Updated: 2024/09/11 14:59:06 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	ft_strlen2(char **tab)
{
	int	x;

	x = 0;
	if (!tab)
		return (0);
	while (tab[x])
		x++;
	return (x);
}

char	**tab_dup(char **tab)
{
	char	**temp;
	int		x;

	if (!tab)
		return (NULL);
	x = 0;
	temp = malloc(sizeof(char *) * (ft_strlen2(tab) + 1));
	if (!temp)
		return (NULL);
	while (tab[x])
	{
		temp[x] = ft_strdup(tab[x]);
		if (!temp[x])
		{
			free_tab(temp);
			return (NULL);
		}
		x++;
	}
	temp[x] = NULL;
	return (temp);
}

int	is_position(char c)
{
	return ((c == 'W' || c == 'N' || c == 'S' || c == 'E'));
}
