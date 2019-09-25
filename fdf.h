/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 18:36:28 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/09/07 15:30:38 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define WIDTH 1000
# define HEIGTH 1000
# define ASCENSION 0255251150
# define NORMAL 0000103255
# define TECH 0xffdb58
# define DTOR(angle) (angle * M_PI)/180
# include <math.h>
# include <stdlib.h>
# include "libft/includes/libft.h"

typedef struct			s_intslide{
	int					*xslide;
	int					size;
	struct s_intslide	*next;
}						t_slide;

typedef struct			s_grid{
	int					**grid;
	int					xsize;
	int					ysize;
	int					zoom;
	int					x_off;
	int					y_off;
	int					zp;
	int					t_z;
	int					t_x;
	int					t_y;
	int					p;
}						t_grid;

typedef	struct			s_mlx{
	void				*mlx_ptr;
	void				*win_ptr;
	t_grid				grid;
}						t_mlx;

typedef struct			s_proj{
	int					zoom;
	int					row;
	int					zval;
	int					column;
	int					size_col;
	int					size_row;
	int					off_x;
	int					off_y;
	int					rot_x;
	int					rot_z;
	int					rot_y;
	int					z_flat;
	int					p;
}						t_proj;

typedef struct			s_cart{
	int					dx;
	int					dy;
	int					sx;
	int					sy;
	int					err;
	int					err2;
}						t_cart;

t_slide					*inter(t_slide *res, char *line);
t_slide					*node_add(t_slide *anywhere, int *line, int size);
t_slide					*list_slider(int fd, char *line);
t_grid					create_2d_array(t_slide *head, int n_elements);

t_proj					do_projection(t_proj input);

int						t_print_all_nodes(t_slide *start);
int						list_size(t_slide *head);
int						check_file(char *path);

void					clear_list(t_slide *head);
void					t_print_2d_array(t_grid *grid);
void					do_iso(int *x, int *y, int z);
void					draw_my_bresenham(t_proj p1,
						t_proj p2, t_mlx mlx, int c);
void					draw_stuff(t_mlx *mlx, int mode);
void					draw_h_lines(t_mlx mlx, t_grid grid, int m);
void					draw_v_lines(t_mlx mlx, t_grid grid, int m);
void					free_list(t_slide *head);
void					offset(t_mlx *mlx, int key);
void					show_guide(void *mlx_ptr, void *win_ptr);

#endif
