/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 15:29:01 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/11/06 23:25:58 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "fdf.h"
#include "minilibx_macos/mlx.h"

void	zoom_diff(t_mlx *mlx, int key)
{
	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx->grid.zoom += (33 - key) * 2;
	draw_stuff(mlx, 0);
}

void	angle_switch(t_mlx *mlx, int key)
{
	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	if (key == 43)
		mlx->grid.t_z -= 5;
	if (key == 47)
		mlx->grid.t_z += 5;
	if (key == 45)
		mlx->grid.t_y -= 5;
	if (key == 46)
		mlx->grid.t_y += 5;
	if (key == 9)
		mlx->grid.t_x -= 5;
	if (key == 11)
		mlx->grid.t_x += 5;
	draw_stuff(mlx, 0);
}

int		deal_key(int key, t_mlx *mlx)
{
	if (key == 53)
		exit(0);
	if (key == 40 || key == 37)
	{
		mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
		mlx->grid.zp = key == 37 ? mlx->grid.zp - 1 : mlx->grid.zp + 1;
		draw_stuff(mlx, 0);
	}
	if (key == 31 || key == 35)
		zoom_diff(mlx, key);
	if (key == 123 || key == 124 || key == 125 || key == 126)
		offset(mlx, key);
	if (key == 43 || (key >= 45 && key <= 47) || key == 9 || key == 11)
		angle_switch(mlx, key);
	if (key == 257 || key == 258)
	{
		mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
		if (mlx->grid.p == 0)
			mlx->grid.p++;
		else
			mlx->grid.p--;
		draw_stuff(mlx, 0);
	}
	return (0);
}

t_grid	starting_proj(t_grid grid)
{
	grid.zoom = ft_min_val(WIDTH / grid.xsize / 2, HEIGTH / grid.ysize / 2);
	grid.x_off = 0;
	grid.y_off = 0;
	grid.t_x = 0;
	grid.t_y = 0;
	grid.t_z = 0;
	grid.p = 0;
	grid.zp = 0;
	return (grid);
}

int		main(int argc, char **argv)
{
	int		fd;
	char	*line;
	t_slide *head;
	t_grid	grid;
	t_mlx	mlx;

	line = NULL;
	fd = open(argv[1], O_RDONLY);
	if (fd == 0 || argc != 2)
		return (err_ret("Usage : ./fdf <path to map>"));
	if (check_file(argv[1]) == 1)
		return (err_ret("Unsupported map"));
	head = list_slider(fd, line);
	grid = create_2d_array(head, (list_size(head)));
	grid = starting_proj(grid);
	mlx.grid = grid;
	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WIDTH, HEIGTH, "FIL DE FER");
	show_guide(mlx.mlx_ptr, mlx.win_ptr);
	draw_stuff(&mlx, 0);
	mlx_key_hook(mlx.win_ptr, deal_key, (void *)&mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
