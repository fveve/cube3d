/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cinematic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joncurci <joncurci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:06:44 by joncurci          #+#    #+#             */
/*   Updated: 2024/09/04 18:08:56 by joncurci         ###   ########.fr       */
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










char *ft_strjoin_free(char *s1, char *s2)
{
    char *result = ft_strjoin(s1, s2);
    free(s1);
    return result;
}

void free_cinematic_images(t_data *data, int num_images)
{
    int i;

    i = 0;
    while (i < (num_images))
    {
        if (data->bonus_data->cinematic1[i])
		{
            mlx_destroy_image(data->mlx_data->mlx, data->bonus_data->cinematic1[i]);
			//free(data->bonus_data->cinematic1[i]);
		}
		i++;
    }

    // Libérer le tableau
    free(data->bonus_data->cinematic1);
    data->bonus_data->cinematic1 = NULL;
}

/*void load_cinematic_images(t_data *data, char *folder_path, int num_images)
{
    char *file_name;
    char *file_path;
    char *index_str;
    int i;

	int	width = 1920;
	int	height = 1080;

    // Allocation du tableau pour stocker les images
    data->bonus_data->cinematic1 = malloc(sizeof(void*) * num_images);
    if (!data->bonus_data->cinematic1)
        return; // Gérer l'erreur d'allocation

    i = 0;
    while (i < num_images)
    {
        // Construire le nom du fichier (image_001.xpm, image_002.xpm, etc.)
        index_str = ft_itoa(i + 1); // Convertir l'index en chaîne
        if (i + 1 < 10)
            file_name = ft_strjoin("vortex_cinematic(00", index_str); // image_001.xpm
        else if (i + 1 < 100)
            file_name = ft_strjoin("vortex_cinematic(t_data *0", index_str);  // image_010.xpm
        else
            file_name = ft_strjoin("vortex_cinematic(", index_str);   // image_100.xpm
        
        free(index_str); // Libérer la chaîne temporaire

        // Ajouter l'extension et le chemin du dossier
        file_path = ft_strjoin(folder_path, "/");
        file_path = ft_strjoin_free(file_path, file_name);
        file_path = ft_strjoin_free(file_path, ").jpg");
        file_path = ft_strjoin_free(file_path, ".xpm");

        // Charger l'image avec mlx_xpm_file_to_image et la stocker dans le tableau
        data->bonus_data->cinematic1[i] = mlx_xpm_file_to_image(data->mlx_data->mlx, file_path, &width, &height);

        // Gérer l'erreur de chargement si nécessaire
        if (!data->bonus_data->cinematic1[i])
        {
            printf("Erreur lors du chargement de l'image : %s\n", file_path);
            // Libérer les images déjà chargées et quitter la fonction
            free_cinematic_images(data, i);
            free(file_path);
            return;
        }

        free(file_name);
        free(file_path);

        i++;t_data *
    }
}*/
/*void load_cinematic_images(t_data *data, char *folder_path, int num_images)
{
    char *file_name;
    char *file_path;
    char *index_str;
    int i;

	int width = 1920;
	int height = 1080;

    // Allocation du tableau pour stocker les images
    data->bonus_data->cinematic1 = malloc(sizeof(void*) * num_images);
    if (!data->bonus_data->cinematic1)
        return; // Gérer l'erreur d'allocation

    i = 0;
    while (i < num_images)
    {
        // Construire le nom du fichier (image_001.xpm, image_002.xpm, etc.)
        index_str = ft_itoa(i + 1); // Convertir l'index en chaîne
        if (!index_str)
        {
            free_cinematic_images(data, i); // Libérer les images déjà chargées
            return ;
        }
        if (i + 1 < 10)
            file_name = ft_strjoin("vortex_cinematic(00", index_str); // image_001.xpm
        else if (i + 1 < 100)
            file_name = ft_strjoin("vortex_cinematic(0", index_str);  // image_010.xpm
        else
            file_name = ft_strjoin("vortex_cinematic(", index_str);   // image_100.xpm
        free(index_str); // Libérer la chaîne temporaire
        if (!file_name)
        {
            free_cinematic_images(data, i); // Libérer les images déjà chargées
            return ;
        }
        // Ajouter l'extension et le chemin du dossier
        file_path = ft_strjoin(folder_path, "/");
        if (!file_path)
        {
            free(file_name);
            free_cinematic_images(data, i); // Libérer les images déjà chargées
            return ;
        }
        file_path = ft_strjoin_free(file_path, file_name);
        if (!file_path)
        {
            free(file_name);
            free_cinematic_images(data, i); // Libérer les images déjà chargées
            return ;
        }
        free(file_name); // Libérer file_name maintenant que file_path est construit
        file_path = ft_strjoin_free(file_path, ").jpg.xpm");
        if (!file_path)
        {
            free_cinematic_images(data, i); // Libérer les images déjà chargées
            return ;
        }
        // Charger l'image avec mlx_xpm_file_to_image et la stocker dans le tableau
        data->bonus_data->cinematic1[i] = mlx_xpm_file_to_image(data->mlx_data->mlx, file_path, &width, &height);
        // Gérer l'erreur de chargement si nécessaire
        if (!data->bonus_data->cinematic1[i])
        {
            printf("Erreur lors du chargement de l'image : %s\n", file_path);
            // Libérer les images déjà chargées et quitter la fonction
            free_cinematic_images(data, i);
            free(file_path);
            return ;
        }
        free(file_path); // Libérer file_path après l'utilisation
        i++;
    }
}*/
void	play_loading_bar(t_data *data, int i)
{
	if (i == 14)
		mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window, data->bonus_data->cinematic1[5], 0, 0);
	else if (i == 35)
		mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window, data->bonus_data->cinematic1[6], 0, 0);
	else if (i == 50)
		mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window, data->bonus_data->cinematic1[7], 0, 0);
	else if (i == 65)
		mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window, data->bonus_data->cinematic1[8], 0, 0);
	else if (i == 80)
		mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window, data->bonus_data->cinematic1[9], 0, 0);
	else if (i == 100)
		mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window, data->bonus_data->cinematic1[10], 0, 0);
	else if (i == 120)
		mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window, data->bonus_data->cinematic1[11], 0, 0);
	else if (i == 140)
		mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window, data->bonus_data->cinematic1[12], 0, 0);
	else if (i == 162)
		mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window, data->bonus_data->cinematic1[13], 0, 0);
}

void load_cinematic_images(t_data *data, char *folder_path, int num_images)
{
    char *file_name = NULL;
    char *file_path = NULL;
    char *index_str = NULL;
    int i;

    //int width = 1920;
    //int height = 1080;
	data->mlx_data->window = resize_window(data, 1920, 1080);

	i = 14;
    // Allocation du tableau pour stocker les images
    data->bonus_data->cinematic1 = malloc(sizeof(void *) * (num_images)); //!!!!!!! + 14
    if (!data->bonus_data->cinematic1)
	{
        return; // Gérer l'erreur d'allocation
	}

	data->bonus_data->cinematic1[0] = mlx_xpm_file_to_image(data->mlx_data->mlx, "./texture/title_screen/title_screen.xpm", &(data->bonus_data->cinematic_w), &(data->bonus_data->cinematic_h));
	data->bonus_data->cinematic1[1] = mlx_xpm_file_to_image(data->mlx_data->mlx, "./texture/title_screen/title_text.xpm", &(data->bonus_data->cinematic_w), &(data->bonus_data->cinematic_h));
	data->bonus_data->cinematic1[2] = mlx_xpm_file_to_image(data->mlx_data->mlx, "./texture/title_screen/title_commands.xpm", &(data->bonus_data->cinematic_w), &(data->bonus_data->cinematic_h));
	data->bonus_data->cinematic1[3] = mlx_xpm_file_to_image(data->mlx_data->mlx, "./texture/title_screen/victory.xpm", &(data->bonus_data->cinematic_w), &(data->bonus_data->cinematic_h));
	data->bonus_data->cinematic1[4] = mlx_xpm_file_to_image(data->mlx_data->mlx, "./texture/title_screen/game_over.xpm", &(data->bonus_data->cinematic_w), &(data->bonus_data->cinematic_h));
	data->bonus_data->cinematic1[5] = mlx_xpm_file_to_image(data->mlx_data->mlx, "./texture/title_screen/loading1.xpm", &(data->bonus_data->cinematic_w), &(data->bonus_data->cinematic_h));
	data->bonus_data->cinematic1[6] = mlx_xpm_file_to_image(data->mlx_data->mlx, "./texture/title_screen/loading2.xpm", &(data->bonus_data->cinematic_w), &(data->bonus_data->cinematic_h));
	data->bonus_data->cinematic1[7] = mlx_xpm_file_to_image(data->mlx_data->mlx, "./texture/title_screen/loading3.xpm", &(data->bonus_data->cinematic_w), &(data->bonus_data->cinematic_h));
	data->bonus_data->cinematic1[8] = mlx_xpm_file_to_image(data->mlx_data->mlx, "./texture/title_screen/loading4.xpm", &(data->bonus_data->cinematic_w), &(data->bonus_data->cinematic_h));
	data->bonus_data->cinematic1[9] = mlx_xpm_file_to_image(data->mlx_data->mlx, "./texture/title_screen/loading5.xpm", &(data->bonus_data->cinematic_w), &(data->bonus_data->cinematic_h));
	data->bonus_data->cinematic1[10] = mlx_xpm_file_to_image(data->mlx_data->mlx, "./texture/title_screen/loading6.xpm", &(data->bonus_data->cinematic_w), &(data->bonus_data->cinematic_h));
	data->bonus_data->cinematic1[11] = mlx_xpm_file_to_image(data->mlx_data->mlx, "./texture/title_screen/loading7.xpm", &(data->bonus_data->cinematic_w), &(data->bonus_data->cinematic_h));
	data->bonus_data->cinematic1[12] = mlx_xpm_file_to_image(data->mlx_data->mlx, "./texture/title_screen/loading8.xpm", &(data->bonus_data->cinematic_w), &(data->bonus_data->cinematic_h));
	data->bonus_data->cinematic1[13] = mlx_xpm_file_to_image(data->mlx_data->mlx, "./texture/title_screen/loading9.xpm", &(data->bonus_data->cinematic_w), &(data->bonus_data->cinematic_h));
    
	while (i < num_images)
    {
        // Construire le nom du fichier (image_001.xpm, image_002.xpm, etc.)
        index_str = ft_itoa(i + 1 - 14); // Convertir l'index en chaîne
        if (!index_str)
        {
            free_cinematic_images(data, i); // Libérer les images déjà chargées
            return;
        }

        if (i + 1 - 14 < 10)
            file_name = ft_strjoin("vortex_cinematic(00", index_str); // image_001.xpm
        else if (i + 1 - 14 < 100)
            file_name = ft_strjoin("vortex_cinematic(0", index_str);  // image_010.xpm
        else
            file_name = ft_strjoin("vortex_cinematic(", index_str);   // image_100.xpm

        free(index_str); // Libérer la chaîne temporaire

        if (!file_name)
        {
            free_cinematic_images(data, i); // Libérer les images déjà chargées
            return ;
        }

        // Ajouter l'extension et le chemin du dossier
        file_path = ft_strjoin(folder_path, "/");
        if (!file_path)
        {
            free(file_name);
            free_cinematic_images(data, i); // Libérer les images déjà chargées
            return ;
        }

        char *tmp_path = file_path;
        file_path = ft_strjoin(file_path, file_name);
        free(tmp_path);
        free(file_name); // Libérer file_name maintenant que file_path est construit

        tmp_path = file_path;
        file_path = ft_strjoin(file_path, ").jpg.xpm");
        free(tmp_path);

        if (!file_path)
        {
            free_cinematic_images(data, i); // Libérer les images déjà chargées
            return;
        }

        // Charger l'image avec mlx_xpm_file_to_image et la stocker dans le tableau
        data->bonus_data->cinematic1[i] = mlx_xpm_file_to_image(data->mlx_data->mlx, file_path, &(data->bonus_data->cinematic_w), &(data->bonus_data->cinematic_h));

        // Gérer l'erreur de chargement si nécessaire
        if (!data->bonus_data->cinematic1[i])
        {
            printf("Erreur lors du chargement de l'image : %s\n", file_path);
            // Libérer les images déjà chargées et quitter la fonction
            free(file_path);
            free_cinematic_images(data, i);
            return;
        }

        free(file_path); // Libérer file_path après l'utilisation

		
		play_loading_bar(data, i); //!!!!!!!!!!!!!!!!!
		i++;
    }
	
}


/*void play_cinematic(t_data *data, int num_images, int delay_ms)
{
    int i;

    i = 14;
    while (i < (num_images))
    {
        // Afficher l'image actuelle
        mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window, data->bonus_data->cinematic1[i], 0, 0);

        // Attendre le temps spécifié (en millisecondes)
        usleep(delay_ms * 1000); // Convertir ms en microsecondes pour usleep
		mlx_do_sync(data->mlx_data->mlx);
        // Optionnel : gérer les événements pendant la cinématique
        i++;
    }
        // Afficher l'image actuelle
        mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window, data->bonus_data->cinematic1[3], 0, 0);

        // Attendre le temps spécifié (en millisecondes)
        usleep(20000 * 1000); // Convertir ms en microsecondes pour usleep
		mlx_do_sync(data->mlx_data->mlx);

}*/

long get_elapsed_time_ms(struct timeval start_time)
{
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    long elapsed_time_ms = (current_time.tv_sec * 1000 + current_time.tv_usec / 1000) - 
                           (start_time.tv_sec * 1000 + start_time.tv_usec / 1000);
    return elapsed_time_ms;
}

void play_cinematic(t_data *data, int num_images, int delay_ms)
{
    int i;
    struct timeval start_time;
    long elapsed_time;

    i = 14;
    while (i < num_images)
    {
        // Afficher l'image actuelle
        mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window, data->bonus_data->cinematic1[i], 0, 0);

        // Attendre le temps spécifié (en millisecondes)
        usleep(delay_ms * 1000); // Convertir ms en microsecondes pour usleep
        mlx_do_sync(data->mlx_data->mlx);

        // Optionnel : gérer les événements pendant la cinématique
        i++;
    }

    // Afficher la dernière image et attendre 20 secondes (20000 ms)

    // Obtenir le temps de début
    gettimeofday(&start_time, NULL);

    // Boucle pour attendre jusqu'à ce que 20 secondes se soient écoulées
    while (1)
    {
    mlx_put_image_to_window(data->mlx_data->mlx, data->mlx_data->window, data->bonus_data->cinematic1[3], 0, 0);
        elapsed_time = get_elapsed_time_ms(start_time);
        if (elapsed_time >= 15000) // 20000 millisecondes = 20 secondes
            break;
    }

}







void cinematic(t_data *data, int num_images, int delay_ms)
{
    // Charger les images depuis le dossier
	//load_cinematic_images(data, "./texture/vortex_cinematic", num_images);

    // Si les images sont bien chargées, jouer la cinématique
    if (data->bonus_data->cinematic1 != NULL)
    {
		data->mlx_data->window = resize_window(data, 1920, 1080);
		
		playsound("cub3d_victory_sound", 0, 1, 0);
        play_cinematic(data, num_images, delay_ms);
        
        // Libérer les images de la mémoire après la cinématique
        free_cinematic_images(data, num_images);
    }
}







//!!!!! ----- MY STRJOIN -----------------

/*char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	size_t	totlen;
	char	*join;

	i = 0;
	j = 0;
	totlen = ft_strlen(s1) + ft_strlen(s2);
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
}*/

//!    -------------------------------------