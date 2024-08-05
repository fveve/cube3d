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

# define	SCREEN_HEIGHT 800

# define	SCREEN_WIDTH 800

# define	TEX_WIDTH	64

# define	TEX_HEIGHT	64

//			   __________		     //
//------------/Structures\----------//

typedef struct s_map_data
{
	double	pos_x;
	double	pos_y;

	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	char	*F;
	char	*C;
	char	**map;

	int F_color;
	int	C_color;
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
	t_img	*img;
	t_img	*texture;

} t_mlx_data;

typedef struct s_trace_data
{
	double		dirX;
	double		dirY;

	double		planeX;
	double		planeY;

	double		sideDistX;
	double		sideDistY;

	double		cameraX;
	double		rayDirX;
	double		rayDirY;

	double		moveSpeed;
	double		rotSpeed;
	double		oldDirX;
	double		oldPlaneX;

	double		deltaDistX;
	double		deltaDistY;
	double		perpWallDist;


	double		WallX;
	double		step;
	double		texPos;

	int			color;
	int			mapX;
	int			mapY;
	int			stepX;
	int			stepY;
	int			hit;
	int			side;
	int			lineHeight;
	int			drawStart;
	int			drawEnd;
	int			h;
	int			w;
	int			ycolor;
	int			xcolor;
	int			texY;
	int			texNum;
	int			texX;

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
void	exit_manager(t_data *data);

//				Error
int		is_position(char c);
int		check_error(t_map_data map_data);

//------------\_________/----------//
#endif