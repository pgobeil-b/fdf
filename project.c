/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 15:18:02 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/09/07 15:32:16 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "minilibx_macos/mlx.h"

void	do_rot(int *x, int *y, int *z, t_proj input)
{
	int tempx;
	int tempy;

	if (input.rot_y != 0)
	{
		tempx = *x;
		*x = tempx * cos(DTOR(input.rot_y)) + *z * sin(DTOR(input.rot_y));
		*z = -tempx * sin(DTOR(input.rot_y)) + *z * cos(DTOR(input.rot_y));
	}
	if (input.rot_x != 0)
	{
		tempy = *y;
		*y = tempy * cos(DTOR(input.rot_x)) + *z * sin(DTOR(input.rot_x));
		*z = -tempy * sin(DTOR(input.rot_x)) + *z * cos(DTOR(input.rot_x));
	}
	if (input.rot_z != 0)
	{
		tempy = *y;
		tempx = *x;
		*x = tempx * cos(DTOR(input.rot_z)) - tempy * sin(DTOR(input.rot_z));
		*y = tempx * sin(DTOR(input.rot_z)) + tempy * cos(DTOR(input.rot_z));
	}
}

void	do_ortho(int *x, int *y, int z)
{
	if (z != 0)
	{
		*y += sin(DTOR(45)) * z;
		*x += cos(DTOR(45)) * z;
	}
}

t_proj	do_projection(t_proj input)
{
	input.zval *= input.zoom;
	input.zval += (input.zval * input.z_flat) / input.zoom;
	input.row *= input.zoom;
	input.column *= input.zoom;
	if (input.p == 0)
		do_iso(&input.column, &input.row, input.zval);
	else
		do_ortho(&input.column, &input.row, input.zval);
	input.row += (HEIGTH - (input.size_row * input.zoom)) / 2;
	input.row += input.off_y;
	input.column += input.off_x;
	input.column += (WIDTH - (input.size_col * input.zoom)) / 2 + 100;
	if (input.rot_x != 0 || input.rot_y != 0 || input.rot_z != 0)
		(do_rot(&input.column, &input.row, &input.zval, input));
	return (input);
}
