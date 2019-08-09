/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 14:34:27 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/08/08 18:51:04 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "minilibx_macos/mlx.h"
#include <stdio.h>
#include <unistd.h>

 
void 	do_iso(int *x, int *y, int z)
{
	int	tmp_x;
	int	tmp_y;

	tmp_x = *x;
	tmp_y = *y;
	*y = (tmp_x + tmp_y ) * sin(0.523599) -z;
	*x = (tmp_x - tmp_y) * cos(0.523599);

}

t_proj	grid_to_input(int row, int column, t_grid map)
{
	t_proj input;
	input.size_col = map.xsize;
	input.size_row = map.ysize;
	input.row = row;
	input.column = column;
	input.zval = map.grid[row][column];
	input.zoom = 30;
	return(input);
}

t_proj	do_projection(t_proj input)
{
	input.zval *= input.zoom;
	input.row *= input.zoom;
	input.column *= input.zoom;
	input.column += (WIDTH - (input.size_col * input.zoom)) / 2;
	input.row += (HEIGTH - (input.size_row * input.zoom)) / 2;
	do_iso(&input.column, &input.row, input.zval);
	return (input);	
}

void	draw_my_bresenham(t_proj p1, t_proj p2, t_mlx *mlx)
{	
	t_cart map;
	int		test;

	test = 0;
	printf("%s\n", "enter the bressenham");
	map.dx = absolute_value(p2.column - p1.column);
	map.dy = absolute_value(p2.row - p1.row);
	map.err = (map.dx > map.dy ? map.dx : -map.dy) / 2;
	map.sx = p1.column < p2.column ? 1 : -1;
	map.sy = p1.row < p2.row ? 1 : -1;
	printf("%s%d%s%d%s%d%s%d\n", "x1 ", p1.column, " y1 ", p1.row, " x2 ", p2.column, " y2 ", p2.row);
	while(1)
	{
		mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, p1.column, p1.row, 0250250100);
		if(p1.column == p2.column && p1.row == p2.row)
			break;
		map.err2 = map.err;
		if(map.err2 > -map.dx)
		{
			map.err -= map.dy;
			p1.column += map.sx; 
		}
		if(map.err2 < map.dy) 
		{
			map.err += map.dx;
			p1.row += map.sy;
		}
		if (p1.column == p2.column)
			printf("%d%s%d%s%d\n", test++, " x1 : ", p1.column, " y1 : ", p1.row);
		// sleep(1);
	}
	printf("exit\n");
}

void	draw_h_lines(t_mlx *mlx, t_grid grid)
{
	int	row;
	int col;
	t_proj input1;
	t_proj input2;

	row = 0;
	while (row + 1 <= grid.ysize)
	{
		col = 0;
		while (col + 1 < grid.xsize)
		{
			input1 = do_projection(grid_to_input(row, col, grid));
		//	printf("%s%d%s%d\n", "p1 z:", input.zval, "p2 z:", input2.zval);
			input2 = do_projection(grid_to_input(row, col + 1, grid)); 
			draw_my_bresenham(input1, input2, mlx);
		//	printf("%s\n", "drawing segment");
			col++;
		//	printf("%s%d\n", "col :", col);
		}
		row++;
	}
	printf("%s\n", "exit");
}

void	draw_v_lines(t_mlx *mlx, t_grid grid)
{
	int	row;
	int col;
	t_proj input1;
	t_proj input2;

	row = 0;
	while (row + 1 < grid.ysize)
	{
		col = 0;
		while (col + 1 <= grid.xsize)
		{
			input1 = do_projection(grid_to_input(row, col, grid));
		//	printf("%s%d%s%d\n", "p1 z:", input.zval, "p2 z:", input2.zval);
			input2 = do_projection(grid_to_input(row + 1, col, grid));
			draw_my_bresenham(input1, input2, mlx);
		//	printf("%s\n", "drawing segment");
			col++;
		//	printf("%s%d\n", "col :", col);
		}
		row++;
	}
	printf("%s\n", "exit");
}