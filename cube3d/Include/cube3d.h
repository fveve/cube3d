#ifndef CUBE3D_H

# define	CUBE3D_H
//			   _______			  //
//------------/Include\----------//
# include	<mlx.h>
# include	<stdlib.h>
# include	<unistd.h>
# include	<sys/types.h>
# include	<sys/stat.h>
# include	<fcntl.h>
# include	<stdio.h>
# include	<math.h>
//------------\_______/----------//

# define	RGB_Red "\e[0;31m"

# define	RGB_Blue	"\e[0;34m"

# define	KEY_RIGHT 65363

# define	KEY_LEFT 65361

# define	KEY_UP 65362

# define	KEY_DOWN 65364

# define	KEY_W 119

# define	KEY_S 115

# define	KEY_D 100

# define	KEY_A 97

# define	KEY_ESCAPE 65307

//size of the screen

# define	SCREEN_HEIGHT 500

# define	SCREEN_WIDTH 500

//size of each texture
# define	TEX_HEIGHT	64

# define	TEX_WIDTH	64

//			   __________		     //
//------------/Structures\----------//

typedef struct s_map_data
{
	double	pos_x;
	double	pos_y;

	char	*texture_txt[4];//all the texture paths stored in order
	char	*F;
	char	*C;
	char	**map;

	int F_color;//final floor color
	int	C_color;//final ceailing color
} t_map_data;

typedef struct s_img
{
	void	*img;

	int		bits_per_pixel;
	int		line_length;
	int		endian;

	char	*addr;
} t_img;

typedef struct s_mlx_data
{
	void	*mlx;
	void	*window;
	t_img	*img;//current frame which is  redrawn each time
	t_img	*texture[4];// all the texture stored in an array

} t_mlx_data;

typedef struct s_trace_data
{
	double		dirX;//direction of the player, meaning where is the player looking
	double		dirY;//direction of the player

	double		planeX;//camera plane of the player, meaning how much do the player see
	double		planeY;//camera plane of the player

	double		sideDistX;//the distance the ray has to travel form our current position to the fist x side (vertical side)
	double		sideDistY;//the distance the ray has to travel form our current position to the fist y side (horizontal side)

	double		cameraX;//x coordinate in camera space, meaning the x position in the camera plane
	double		rayDirX;//current x coordinates + the position inside the square we're in
	double		rayDirY;//current y coordinates + the position inside the square we're in

	double		moveSpeed;
	double		rotSpeed;
	double		oldDirX;//used to rotate the y direction vector  
	double		oldPlaneX;//used to rotate the y plane vector  

	double		deltaDistX;//distance the ray has to travel to go form our x side position to the next x side (meaning the side of the square in front of our position), calculated using Pythagoras formula A^2 + B^2 = C^2
	double		deltaDistY;//distance the ray has to travel to go form our y side position to the next y side (meaning the side of the square in front of our position)
	double		perpWallDist;//length of the ray (which extend until it hit a wall)


	double		WallX;//the exact value of where the wall was hit
	double		step;//how much to increase the textiure coordinate per pixels
	double		texPos;//starting texture coordinates

	int			color;//color of the pixel
	int			mapX;//current x coordinates
	int			mapY;//current y coordinates
	int			stepX;//what x direction to step in : in front of (+1) or behind (-1)
	int			stepY;//what y direction to step in : in front of (+1) or behind (-1)
	int			hit;//is there a wall hit ?
	int			side;//was it a west side (like Tupac lmao) or East side wall hit 
	int			lineHeight;//height of the line to draw on the screen
	int			drawStart;//where the wall drawing start
	int			drawEnd;//where the wall drawing end
	int			h;//useless variable, might replace or delete later
	int			w;//useless variable, might replace or delete later
	int			texY;//x coordinate of the texture
	int			texX;//y coordinate of the texture

	unsigned int buffer[SCREEN_HEIGHT][SCREEN_WIDTH];

	t_map_data	*map_data;
	t_mlx_data	*mlx_data;
} t_trace_data;

typedef struct s_data
{
	t_trace_data	*trace_data;
	t_mlx_data		*mlx_data;
	t_map_data		*map_data;
} t_data;

//------------\__________/----------//

//			   _________		    //
//------------/Functions\----------//

//				Main
void	init_data(t_data *data, char **argv);
int		ft_render(t_data *data);
int		input(int key, t_data *data);


//				parsing
int		is_printable(char *s);
void	parse_map(t_map_data *map_data, char *file);

//			get_next_line
char	*get_next_line(int	fd, int	copy);

//				tools
long	ft_atoi( char *nptr);
char	*extract_str(char *str);
char	*ft_substr(char const *s, int	start, int	len);
int		ft_strncmp(const char *s1, char *s2, size_t n);
int		ft_strlen2(char **tab);

//			render     tools
double	ft_abs(double nb);
int		get_pixel(t_img *data, int x, int y);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
void	draw_buffer(t_trace_data *data);

//				gnl_tools
int		ft_strlen(const char *s);
char	*ft_strdup(char *src);
char	*ft_strchr(char *s, int	c);
char	*ft_strjoin(char *s1, char *s2);
void	ft_strcpy(char *dest,const char *src);

//				debug
void	print_tab(char **tab);
void	print_map_data(t_map_data *map_data);

//			exit_manager
void	free_tab(char **tab);
int	exit_manager(t_data *data);

//				Error
int		is_position(char c);
int		check_error(t_data *data, t_map_data map_data);

//------------\_________/----------//
#endif