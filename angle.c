/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 14:34:27 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/09/07 15:24:39 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "fdf.h"
#include "minilibx_macos/mlx.h"

t_proj	grid_to_input(int row, int column, t_grid map)
{
	t_proj input;

	input.size_col = map.xsize;
	input.size_row = map.ysize;
	input.row = row;
	input.column = column;
	input.zval = map.grid[row][column];
	input.zoom = map.zoom;
	input.off_x = map.x_off;
	input.off_y = map.y_off;
	input.rot_x = map.t_x;
	input.rot_y = map.t_y;
	input.rot_z = map.t_z;
	input.z_flat = map.zp;
	input.p = map.p;
	return (input);
}

void	draw_my_bresenham(t_proj p1, t_proj p2, t_mlx mlx, int c)
{
	t_cart	map;

	map.dx = ft_abs_val(p2.column - p1.column);
	map.dy = ft_abs_val(p2.row - p1.row);
	map.err = (map.dx > map.dy ? map.dx : -map.dy) / 2;
	map.sx = p1.column < p2.column ? 1 : -1;
	map.sy = p1.row < p2.row ? 1 : -1;
	while (1)
	{
		mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, p1.column, p1.row, c);
		if (p1.column == p2.column && p1.row == p2.row)
			break ;
		map.err2 = map.err;
		if (map.err2 > -map.dx)
		{
			map.err -= map.dy;
			p1.column += map.sx;
		}
		if (map.err2 < map.dy)
		{
			map.err += map.dx;
			p1.row += map.sy;
		}
	}
}

void	draw_h_lines(t_mlx mlx, t_grid grid, int m)
{
	int		row;
	int		col;
	int		c;
	t_proj	input1;
	t_proj	input2;

	if (m == 1)
		c = 0000000000;
	row = 0;
	while (row + 1 <= grid.ysize)
	{
		col = 0;
		while (col + 1 < grid.xsize)
		{
			if (m != 1)
				c = ASCENSION;
			input1 = do_projection(grid_to_input(row, col, grid));
			input2 = do_projection(grid_to_input(row, col + 1, grid));
			if (m != 1 && (grid.grid[row][col] != grid.grid[row][col + 1] != 0))
				c = TECH;
			draw_my_bresenham(input1, input2, mlx, c);
			col++;
		}
		row++;
	}
}

void	draw_v_lines(t_mlx mlx, t_grid grid, int m)
{
	int		row;
	int		col;
	int		c;
	t_proj	input1;
	t_proj	input2;

	if (m == 1)
		c = 0000000000;
	row = 0;
	while (row + 1 < grid.ysize)
	{
		col = 0;
		while (col + 1 <= grid.xsize)
		{
			if (m != 1)
				c = NORMAL;
			input1 = do_projection(grid_to_input(row, col, grid));
			input2 = do_projection(grid_to_input(row + 1, col, grid));
			if (m != 1 && (grid.grid[row][col] != grid.grid[row + 1][col]))
				c = TECH;
			draw_my_bresenham(input1, input2, mlx, c);
			col++;
		}
		row++;
	}
}
