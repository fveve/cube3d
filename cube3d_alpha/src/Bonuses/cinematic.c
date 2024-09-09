/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cinematic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joncurci <joncurci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:57:43 by joncurci          #+#    #+#             */
/*   Updated: 2024/09/09 14:21:33 by joncurci         ###   ########.fr       */
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

void	play_loading_bar(t_data *data, int i)
{
	if (i == 14)
		mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window,
			data->bonus_data->cinematic[5], 0, 0);
	else if (i == 35)
		mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window,
			data->bonus_data->cinematic[6], 0, 0);
	else if (i == 50)
		mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window,
			data->bonus_data->cinematic[7], 0, 0);
	else if (i == 65)
		mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window,
			data->bonus_data->cinematic[8], 0, 0);
	else if (i == 80)
		mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window,
			data->bonus_data->cinematic[9], 0, 0);
	else if (i == 100)
		mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window,
			data->bonus_data->cinematic[10], 0, 0);
	else if (i == 120)
		mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window,
			data->bonus_data->cinematic[11], 0, 0);
	else if (i == 140)
		mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window,
			data->bonus_data->cinematic[12], 0, 0);
	else if (i == 162)
		mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window,
			data->bonus_data->cinematic[13], 0, 0);
}

void	load_cinematic_images(t_data *data, char *folder_path, int num_images)
{
	char	*file_name;
	char	*file_path;
	char	*index_str;
	int		i;
	char	*tmp_path;

	data->mlx_data->window = resize_window(data, 1920, 1080);
	file_name = NULL;
	file_path = NULL;
	index_str = NULL;
	i = 0;
	data->bonus_data->cinematic = malloc(sizeof(void *) * (num_images));
	if (!data->bonus_data->cinematic)
		return ;
	while (i < num_images)
	{
		data->bonus_data->cinematic[i] = NULL;
		i++;
	}
	i = 0;
	data->bonus_data->cinematic[0] = mlx_xpm_file_to_image(data->mlx_data->mlx,
			"./texture/title_screen/title_screen.xpm",
			&(data->bonus_data->cinematic_w), &(data->bonus_data->cinematic_h));
	data->bonus_data->cinematic[1] = mlx_xpm_file_to_image(data->mlx_data->mlx,
			"./texture/title_screen/title_text.xpm",
			&(data->bonus_data->cinematic_w), &(data->bonus_data->cinematic_h));
	data->bonus_data->cinematic[2] = mlx_xpm_file_to_image(data->mlx_data->mlx,
			"./texture/title_screen/title_commands.xpm",
			&(data->bonus_data->cinematic_w), &(data->bonus_data->cinematic_h));
	data->bonus_data->cinematic[3] = mlx_xpm_file_to_image(data->mlx_data->mlx,
			"./texture/title_screen/victory.xpm",
			&(data->bonus_data->cinematic_w), &(data->bonus_data->cinematic_h));
	data->bonus_data->cinematic[4] = mlx_xpm_file_to_image(data->mlx_data->mlx,
			"./texture/title_screen/game_over.xpm",
			&(data->bonus_data->cinematic_w), &(data->bonus_data->cinematic_h));
	data->bonus_data->cinematic[5] = mlx_xpm_file_to_image(data->mlx_data->mlx,
			"./texture/title_screen/loading1.xpm",
			&(data->bonus_data->cinematic_w), &(data->bonus_data->cinematic_h));
	data->bonus_data->cinematic[6] = mlx_xpm_file_to_image(data->mlx_data->mlx,
			"./texture/title_screen/loading2.xpm",
			&(data->bonus_data->cinematic_w), &(data->bonus_data->cinematic_h));
	data->bonus_data->cinematic[7] = mlx_xpm_file_to_image(data->mlx_data->mlx,
			"./texture/title_screen/loading3.xpm",
			&(data->bonus_data->cinematic_w), &(data->bonus_data->cinematic_h));
	data->bonus_data->cinematic[8] = mlx_xpm_file_to_image(data->mlx_data->mlx,
			"./texture/title_screen/loading4.xpm",
			&(data->bonus_data->cinematic_w), &(data->bonus_data->cinematic_h));
	data->bonus_data->cinematic[9] = mlx_xpm_file_to_image(data->mlx_data->mlx,
			"./texture/title_screen/loading5.xpm",
			&(data->bonus_data->cinematic_w), &(data->bonus_data->cinematic_h));
	data->bonus_data->cinematic[10] = mlx_xpm_file_to_image(data->mlx_data->mlx,
			"./texture/title_screen/loading6.xpm",
			&(data->bonus_data->cinematic_w), &(data->bonus_data->cinematic_h));
	data->bonus_data->cinematic[11] = mlx_xpm_file_to_image(data->mlx_data->mlx,
			"./texture/title_screen/loading7.xpm",
			&(data->bonus_data->cinematic_w), &(data->bonus_data->cinematic_h));
	data->bonus_data->cinematic[12] = mlx_xpm_file_to_image(data->mlx_data->mlx,
			"./texture/title_screen/loading8.xpm",
			&(data->bonus_data->cinematic_w), &(data->bonus_data->cinematic_h));
	data->bonus_data->cinematic[13] = mlx_xpm_file_to_image(data->mlx_data->mlx,
			"./texture/title_screen/loading9.xpm",
			&(data->bonus_data->cinematic_w), &(data->bonus_data->cinematic_h));
	while (i < 14)
	{
		if (!data->bonus_data->cinematic[i])
		{
			printf("Error loading texture at index %d\n", i);
			exit_manager(data);
		}
		i++;
	}
	while (i < num_images)
	{
		index_str = ft_itoa(i + 1 - 14);
		if (!index_str)
		{
			free_cinematic_images(data, i);
			return ;
		}
		if (i + 1 - 14 < 10)
			file_name = ft_strjoin("vortex_cinematic(00", index_str);
		else if (i + 1 - 14 < 100)
			file_name = ft_strjoin("vortex_cinematic(0", index_str);
		else
			file_name = ft_strjoin("vortex_cinematic(", index_str);
		free(index_str);
		if (!file_name)
			exit_manager(data);
		file_path = ft_strjoin(folder_path, "/");
		if (!file_path)
		{
			free(file_name);
			exit_manager(data);
		}
		tmp_path = file_path;
		file_path = ft_strjoin(file_path, file_name);
		free(tmp_path);
		free(file_name);
		tmp_path = file_path;
		file_path = ft_strjoin(file_path, ").jpg.xpm");
		free(tmp_path);
		if (!file_path)
			exit_manager(data);
		data->bonus_data->cinematic[i] = mlx_xpm_file_to_image(
				data->mlx_data->mlx, file_path,
				&(data->bonus_data->cinematic_w),
				&(data->bonus_data->cinematic_h));
		if (!data->bonus_data->cinematic[i])
		{
			printf("Erreur lors du chargement de l'image : %s\n", file_path);
			free(file_path);
			exit_manager(data);
		}
		free(file_path);
		play_loading_bar(data, i);
		i++;
	}
}

long	get_elapsed_time_ms(struct timeval start_time)
{
	struct timeval	current_time;
	long			elapsed_time_ms;

	gettimeofday(&current_time, NULL);
	elapsed_time_ms = (current_time.tv_sec * 1000 + current_time.tv_usec
			/ 1000) - (start_time.tv_sec * 1000 + start_time.tv_usec / 1000);
	return (elapsed_time_ms);
}

void	play_cinematic(t_data *data, int num_images, int delay_ms)
{
	int				i;
	struct timeval	start_time;
	long			elapsed_time;

	i = 14;
	while (i < num_images)
	{
		mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window,
			data->bonus_data->cinematic[i], 0, 0);
		usleep(delay_ms * 1000);
		mlx_do_sync(data->mlx_data->mlx);
		i++;
	}
	gettimeofday(&start_time, NULL);
	while (1)
	{
		mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window,
			data->bonus_data->cinematic[3], 0, 0);
		elapsed_time = get_elapsed_time_ms(start_time);
		if (elapsed_time >= 8000)
			break ;
	}
}

void	cinematic(t_data *data, int num_images, int delay_ms)
{
	if (data->bonus_data->cinematic != NULL)
	{
		data->mlx_data->window = resize_window(data, 1920, 1080);
		playsound("cub3d_victory_sound", 0, 1, 0);
		play_cinematic(data, num_images, delay_ms);
		free_cinematic_images(data, num_images);
	}
}
