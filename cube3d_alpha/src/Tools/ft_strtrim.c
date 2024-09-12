/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arafa <arafa@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 17:07:59 by joncurci          #+#    #+#             */
/*   Updated: 2024/09/12 16:16:46 by arafa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

char	*ft_strtrim(char const *s1, char const *set);

void	*ft_memset(void *b, int c, size_t len)
{
	char	*p;

	p = (char *)b;
	while (len > 0)
	{
		p[len - 1] = c;
		len--;
	}
	return (b);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	b;
	void	*p;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	b = count * size;
	p = malloc(b);
	if (p == NULL)
		return (NULL);
	else
		ft_memset(p, 0,b);
	return (p);
}

static size_t	setcountbeg(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s1[i])
	{
		j = 0;
		while (set[j])
		{
			if (s1[i] == set[j])
			{
				i++;
				break ;
			}
			if (s1[i] != set[j])
				j++;
		}
		if (set[j] == '\0')
			break ;
	}
	return (i);
}

static size_t	setcountend(char const *s1, char const *set)
{
	int		setlen;
	size_t	s1len;

	s1len = ft_strlen(s1) - 1;
	while (s1len >= 0)
	{
		setlen = ft_strlen(set) - 1;
		while (setlen >= 0)
		{
			if (s1[s1len] == set[setlen])
			{
				s1len--;
				break ;
			}
			if (s1[s1len] != set[setlen])
				setlen--;
		}
		if (setlen == -1)
			break ;
	}
	return (ft_strlen(s1) - (s1len + 1));
}

static size_t	memorylen(char const *s1, char const *set)
{
	size_t	trimlen;
	size_t	memlen;

	trimlen = setcountend(s1, set) + setcountbeg(s1, set);
	memlen = ft_strlen(s1) - trimlen;
	return (memlen);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	memlen;
	char	*string;
	size_t	start;

	i = 0;
	if (s1[0] == '\0')
		return (ft_calloc(1, 1));
	start = setcountbeg(s1, set);
	memlen = memorylen(s1, set);
	string = ft_substr(s1, start, memlen);
	return (string);
}
/*
#include <stdio.h>

int	main(void)
{
	const char	str1[] = "ccccuuuu~les pelicans coucou ?!~cocuococucoucc";
	const char	set1[] = "cou";
	char	*string1;

	string1 = ft_strtrim(str1, set1);
	printf("Old String = %s\n", str1);
	printf("New String = %s\n", string1);
	printf("setcountbeg = %zu\n", setcountbeg(str1, set1));
	printf("setcountend = %zu\n", setcountend(str1, set1));
	printf("Total = %zu\n", setcountend(str1, set1) + setcountbeg(str1, set1));
	printf("memlen = %zu\n", memorylen(str1, set1));
	free(string1);
	return (0);
}*/