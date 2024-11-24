/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaslan <alaslan@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 19:16:35 by bsen              #+#    #+#             */
/*   Updated: 2024/11/24 15:48:28 by alaslan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
#include <stdbool.h>
# include <unistd.h>

# define WIDTH 720    // Pencerenin genişliği
# define HEIGHT 550   // Pencerenin yüksekliği
# define TEXWIDTH 64  // Doku genişliği
# define TEXHEIGHT 64 // Doku yüksekliği

# define LEFT_ARROW 123
# define RIGHT_ARROW 124

typedef struct s_image
{
	void	*image; // MLX resim tanıtıcısı
	int		*addr;   // Resim verisinin bellek adresi
}				t_image;

typedef struct s_player
{
	char	player_dir;
	double	x;     // Oyuncunun x koordinatı
	double	y;     // Oyuncunun y koordinatı
	double	dir;   // Oyuncunun bakış açısı
	double	speed; // Oyuncunun hızı
	double	rot;   // Oyuncunun dönüş hızı
}				t_player;

typedef struct s_data
{
	t_image		img;
	t_player	player;
	t_image		*north;
	t_image		*south;
	t_image		*west;
	t_image		*east;
	t_image		*image;
	void		*mlx_ptr;
	void		*win;
	char		*map;
	char		**map2d;
	int			fd;
	char		*mapname;
	int			char_count;
	int			row_length;
	int			x;
	int			y;
	int			longest_line;
	char		*no_text;
	char		*so_text;
	char		*we_text;
	char		*ea_text;
	char		*f;
	char		*c;
	int			where_am_i;
	int			w;
	int			s;
	int			a;
	int			d;
	int			right;
	int			left;
	int			*color;
	double		dir[2];         // Oyuncunun yönü (x, y)
	double		camera_plane[2];       // Kamera düzlemi (x, y)
	double		pos[2];         // Oyuncunun pozisyonu (x, y)
	double		ray_direction[2];      // Işın yönü (x, y)
	double		ray_screen_x;       // Kamera x koordinatı
	int			map_grid_pos[2];        // Harita pozisyonu (x, y)
	double		grid_step_dist[2];  // Kareler arası mesafe (x, y)
	int			ray_step[2];           // Adım yönü (x, y)
	double		border_dist[2];   // Duvarlara olan yan mesafeler (x, y)
	int			hit_axis;              // Çarpan duvar yönü
	double		perp_wall_dist; // Duvarın oyuncuya dik mesafesi
	int			wall_height;            // Duvar çizim yüksekliği
	int			wall_top_pixel;        // Çizim başlangıç noktası
	int			wall_bot_pixel;          // Çizim bitiş noktası
	double		hit_point_x;         // Duvar x koordinatı
	int			tex_column[2];            // Doku koordinatları (x, y)
	double		tex_step;      // Doku adım boyutu
	double		tex_pos;        // Doku pozisyonu
	int			colors[2];         // RGB renkler
}				t_data;

int				gamefunc(t_data *data);
void			texture_control(t_data *data);
int				controls(t_data *data);
int				ft_exit(char *error_massage, t_data *data);
void			map_playable(t_data *data, char **v_map, int x, int y);
int				map_null_check(char **map, int x, int y);
void			char_control(t_data *data, int y);
void			texture_accesible(t_data *data);
void			colorcode(char *f_code, char *c_code, t_data *data, int j);

void			game_create(t_data *data);
void			mlx_create(t_data *data);
void			player_init(t_data *data);
void			xpm_init(t_data *data, int a, int b);
int				key_press(int keyCode, t_data *game);
int				key_unpress(int keyCode, t_data *data);
void			move_player(t_data *data, double moveX, double moveY);
void			handle_movement(t_data *data, double move_x, double move_y);

void			compute_ray_properties(t_data *data, int x);
void			compute_ray_step_and_distance(t_data *data);
void			calculate_collision_distance(t_data *data);
void			compute_wall_dimensions_and_texture(t_data *data);
void			rotate(t_data *data);
void			render_column(t_data *data, int x, int y);
void			ft_free(char **s);
void			map1d(t_data *data);
void			find_player(char **map, t_data *data);
int				set_color(int *f_int, int *c_int, char **f, char **c);
char			**creat_vrmap(char **virtual_map, t_data *data);
void			chech_texture(char *s, t_data *data);
void	set_pixel_color(t_data *data, int x, int y, int color);
void	render_texture(t_data *data, int x, int y);
void	ft_mlx2(t_data *data, int c);
void	xpm_init(t_data *data, int a, int b);
void	mlx_create(t_data *data);
bool	check_player(t_data *data);
void clear_color(char ***f, char ***c, char *f_code, char *c_code);
int	exit_cross();





#endif
