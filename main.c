/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 14:31:21 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/07/17 14:38:15 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "mlx.h"
#include "fdf.h"
#include "libft/includes/libft.h"

int 	deal_key(int key, void *param)
{
	ft_putchar('x');
	return(0);
}

int		main()
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		d;
	int		i;
	int		j;
	int		r;
	int		c;
	int		fd;
	int 	**grid;
	char	*line;
	
	
	d = 250;
	i = -1;
	r = 0;
	c = 0;

	// // get_next_line(fd, &line);
	// ft_putstr(line);
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "popup");
	mlx_string_put(mlx_ptr, win_ptr, 250, 250 ,0250250100, "enweille esti");
	while(d < 500)
	{
		mlx_pixel_put(mlx_ptr, win_ptr, d, d, 0xAAAAAA);
		d++;
	}
	mlx_key_hook(win_ptr, deal_key, (void *)0);
	mlx_loop(mlx_ptr);
	return(0);
}
