/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joncurci <joncurci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 11:05:12 by arafa             #+#    #+#             */
/*   Updated: 2024/08/19 14:02:01 by joncurci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

long	ft_atoi( char *nptr)
{
	long	i;
	int		sign;
	long	nbint;

	sign = 1;
	i = 0;
	nbint = 0;
	while (nptr && (nptr[i] == ' ' || nptr[i] == '\n' || nptr[i] == '\t'
			|| nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == '\r'))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1 * sign;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nbint = nbint * 10 + (nptr[i] - 48);
		i++;
	}
	return (nbint * sign);
}

int	ft_strncmp(const char *s1, char *s2, size_t n)
{
	while (*s1 != '\0' && *s1 == *s2 && n > 0)
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

char	*extract_str(char *str)
{
	int	x;
	int	y;

	x = 3;
	while (str[x] && str[x] <= 'A' && str[x] >= 'Z'
		&& str[x] <= 'a' && str[x] >= 'b' && str[x] != '.')
	{
		x++;
	}
	y = x;
	while (str[y] && str[y] != '\n' && (str[y] >= 'A' || str[y] <= 'Z'
			|| str[y] >= 'a' || str[y] <= 'b' || str[y] == '.'))
	{
		y++;
	}
	return (ft_substr(str, x, y - x));
}

char	*ft_substr(char const *s, int start, int len)
{
	char	*tab;
	int		x;
	int		y;

	if (ft_strlen(s) <= start || s == NULL)
		return (NULL);
	else if (len >= ft_strlen(s))
		tab = malloc(sizeof(char) * (ft_strlen(s) + 1));
	else
		tab = malloc(sizeof(char) * (len + 1));
	if (tab == NULL)
	{
		free(tab);
		return (NULL);
	}
	x = start;
	y = 0;
	while (s[x] && y < len)
		tab[y++] = s[x++];
	tab[y] = '\0';
	return (tab);
}
