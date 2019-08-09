/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 18:36:28 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/08/08 18:44:07 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define WIDTH 1000
# define HEIGTH 1000
#include <math.h>

typedef struct 			s_intslide{
	int					*xslide;
	int					size;
	struct s_intslide	*next;
}						t_slide;

typedef struct			s_grid{
	int					**grid;
	int					xsize;
	int					ysize;
}						t_grid;

typedef	struct			s_mlx{
	void				*mlx_ptr;
	void				*win_ptr;
}						t_mlx;

typedef struct			s_proj{
	int					angle;
	int					zoom;
	int 				row;
	int					zval;
	int					column;
	int					size_col;
	int					size_row;
}						t_proj;	

typedef struct			s_cart{
	int					dx;
	int					dy;
	int					sx;
	int					sy;
	int					err;
	int					err2;
}						t_cart;
t_slide		*inter(char *line);
t_slide		*node_add(t_slide *anywhere, int *line, int size);
t_slide		*list_slider(int fd, char *line);
int			t_print_all_nodes(t_slide *start);
void	t_print_2d_array(t_grid *grid);
int			list_size(t_slide *head);
t_grid		create_2d_array(t_slide *head, int n_elements);
void	draw_my_bresenham(t_proj p1, t_proj p2, t_mlx *mlx);
void	draw_h_lines(t_mlx *mlx, t_grid grid);
void	draw_v_lines(t_mlx *mlx, t_grid grid);
int		absolute_value(int x);

#endif