/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cinematic2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joncurci <joncurci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:57:43 by joncurci          #+#    #+#             */
/*   Updated: 2024/09/11 16:01:17 by joncurci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	srclen;

	srclen = ft_strlen(src);
	i = 0;
	if (size != 0)
	{
		while (src[i] && i < size - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (srclen);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}

void	free_cinematic_images(t_data *data, int num_images)
{
	int	i;

	i = 0;
	while (i < (num_images))
	{
		if (data->bonus_data->cinematic[i])
		{
			mlx_destroy_image(data->mlx_data->mlx,
				data->bonus_data->cinematic[i]);
		}
		i++;
	}
	free(data->bonus_data->cinematic);
	data->bonus_data->cinematic = NULL;
}

void	put_good_image(t_data *data, int text)
{
	mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window,
		data->bonus_data->cinematic[text], 0, 0);
}

void	play_loading_bar(t_data *data, int i)
{
	if (i == 14)
		put_good_image(data, 5);
	else if (i == 35)
		put_good_image(data, 6);
	else if (i == 50)
		put_good_image(data, 7);
	else if (i == 65)
		put_good_image(data, 8);
	else if (i == 80)
		put_good_image(data, 9);
	else if (i == 100)
		put_good_image(data, 10);
	else if (i == 120)
		put_good_image(data, 11);
	else if (i == 140)
		put_good_image(data, 12);
	else if (i == 162)
		put_good_image(data, 13);
}
