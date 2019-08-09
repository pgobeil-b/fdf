/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 15:29:01 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/08/08 18:34:33 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "fdf.h"
#include "minilibx_macos/mlx.h"

int 	deal_key(int key, void *param, t_mlx *mlx)
{
	if (key == 53)
		exit(0);
	ft_putchar('x');
	return(0);
}


int		absolute_value(int x)
{
	if (x < 0)
		x = -x;
	return(x);
}

int		main()
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		fd;
	int		d;
	char	*line;
	t_slide *head;
	t_grid	grid;
	t_mlx	*mlx;

	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	line = NULL;
	fd = open("maps/42.fdf", O_RDONLY);
	head = list_slider(fd, line);
	grid = create_2d_array(head, (list_size(head)));
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, 1000, 1000, "popup");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 250, 250 ,0250250100, "enweille esti");
	// draw_my_bresenham(input, input2, mlx);
	draw_h_lines(mlx, grid);
	draw_v_lines(mlx, grid);
	mlx_key_hook(mlx->win_ptr, deal_key, (void *)mlx);
	printf("%s\n", "icitte ?");
	mlx_loop(mlx->mlx_ptr);
	return(0);
}
