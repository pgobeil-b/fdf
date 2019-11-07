/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 15:17:36 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/11/06 23:26:22 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "minilibx_macos/mlx.h"

void	do_iso(int *x, int *y, int z)
{
	int	tmp_x;
	int	tmp_y;

	tmp_x = *x;
	tmp_y = *y;
	*y = (tmp_x + tmp_y) * sin(0.523599) - z;
	*x = (tmp_x - tmp_y) * cos(0.523599);
}

void	show_guide(void *mlx_ptr, void *win_ptr)
{
	mlx_string_put(mlx_ptr, win_ptr, 30, 30, 0000140100, "\"esc\" to quit");
	mlx_string_put(mlx_ptr, win_ptr, 30, 50, 0000140100, "\"</>\" turn in x");
	mlx_string_put(mlx_ptr, win_ptr, 30, 70, 0000140100, "\"m/n\" turn in y");
	mlx_string_put(mlx_ptr, win_ptr, 30, 90, 0000140100, "\"v/b\" turn in z");
	mlx_string_put(mlx_ptr, win_ptr, 30, 110, 0000140100, "\"o/p\" zoom");
	mlx_string_put(mlx_ptr, win_ptr, 30, 130, 0000140100, "\"k/l\" PUMP!");
	mlx_string_put(mlx_ptr, win_ptr, 30, 150, 0000140100, "\"shft\" iso mode");
}

void	offset(t_mlx *mlx, int key)
{
	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	if (key == 123)
		mlx->grid.x_off -= 10;
	if (key == 124)
		mlx->grid.x_off += 10;
	if (key == 126)
		mlx->grid.y_off -= 10;
	if (key == 125)
		mlx->grid.y_off += 10;
	draw_stuff(mlx, 0);
}

int		check_file(char *path)
{
	int		fd;
	int		i;
	int		len;
	char	*line;
	int		j;

	i = 0;
	fd = open(path, O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		if (i == 0)
			len = ft_countwords(line, ' ') + ft_countwords(line, '\t');
		else if (ft_countwords(line, ' ') + ft_countwords(line, '\t') != len)
			return (1);
		i++;
		j = -1;
		while (line[++j] != '\0')
			if ((line[j] < 48 || line[j] > 57) && line[j]\
			!= ' ' && line[j] != '\t')
				return (1);
		free(line);
	}
	close(fd);
	return (0);
}

void	draw_stuff(t_mlx *mlx, int mode)
{
	draw_h_lines(*(mlx), mlx->grid, mode);
	draw_v_lines(*(mlx), mlx->grid, mode);
}
