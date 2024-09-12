/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cinematic1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joncurci <joncurci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:57:43 by joncurci          #+#    #+#             */
/*   Updated: 2024/09/11 16:01:13 by joncurci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static int	numberlen(int n)
{
	int		nb;
	int		len;

	nb = n;
	len = 0;
	if (n <= 0)
		len++;
	while (nb)
	{
		len++;
		nb = nb / 10;
	}
	return (len);
}

static char	*intminimum(void)
{
	char	*result;
	char	*intmin;

	intmin = "-2147483648";
	result = (char *)malloc(sizeof(char) * 12);
	if (!result)
		return (NULL);
	ft_strlcpy(result, intmin, 12);
	return (result);
}

static char	*malloctab(int n)
{
	char	*result;
	int		len;

	len = numberlen(n);
	result = (char *)malloc(sizeof(char) * len + 1);
	if (!result)
		return (NULL);
	return (result);
}

static char	*treatnumber(int n, char *tab, int len)
{
	if (n == 0)
	{
		tab[0] = '0';
		return (tab);
	}
	if (n < 0)
	{
		tab[0] = '-';
		n = -n;
	}
	while (n)
	{
		tab[len - 1] = n % 10 + '0';
		n = n / 10;
		len--;
	}
	return (tab);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		len;

	if (n == -2147483648)
	{
		result = intminimum();
		if (result == NULL)
			return (NULL);
		return (result);
	}
	len = numberlen(n);
	result = malloctab(n);
	if (result == NULL)
		return (NULL);
	result[len] = '\0';
	result = treatnumber(n, result, len);
	return (result);
}
