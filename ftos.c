/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftos.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 16:48:14 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/09/07 14:54:29 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/includes/libft.h"
#include "fdf.h"

t_slide		*inter(t_slide *res, char *line)
{
	int			i;
	int			j;
	int			k;
	char		*tmp;

	k = 0;
	i = 0;
	res->xslide = (int *)malloc(sizeof(int) * (ft_countwords(line, '\t') + \
	ft_countwords(line, ' ') + 1));
	while (line[i] != '\0')
	{
		while (line[i] != '\0' && (line[i] == ' ' || line[i] == '\t'))
			i++;
		j = i;
		while (line[i] != '\0' && line[i] != ' ' && line[i] != '\t')
			i++;
		tmp = ft_strsub(line, j, i - j);
		res->xslide[k] = atoi(tmp);
		free(tmp);
		k++;
	}
	res->size = k;
	free(line);
	return (res);
}

t_slide		*node_add(t_slide *anywhere, int *line, int size)
{
	t_slide *new;

	new = (t_slide *)malloc(sizeof(t_slide));
	new->xslide = line;
	new->size = size;
	while (anywhere->next != NULL)
	{
		anywhere = anywhere->next;
	}
	anywhere->next = new;
	new->next = NULL;
	return (new);
}

t_slide		*list_slider(int fd, char *line)
{
	int			i;
	t_slide		*head;
	t_slide		*travel;
	t_slide		*current;

	i = -1;
	head = (t_slide *)malloc(sizeof(t_slide));
	current = (t_slide *)malloc(sizeof(t_slide));
	while (get_next_line(fd, &line) > 0)
	{
		if (++i == 0)
		{
			inter(head, line);
			head->next = NULL;
			travel = head;
		}
		else
		{
			inter(current, line);
			travel = node_add(travel, current->xslide, current->size);
		}
	}
	free(current);
	return (head);
}

int			list_size(t_slide *head)
{
	int		i;
	t_slide	*travel;

	travel = head;
	i = 0;
	while (travel != NULL)
	{
		travel = travel->next;
		i++;
	}
	return (i);
}

t_grid		create_2d_array(t_slide *head, int n_elements)
{
	int		k;
	t_grid	grid;

	k = 0;
	grid.grid = (int **)malloc(sizeof(int *) * (n_elements));
	grid.xsize = head->size;
	grid.ysize = n_elements;
	while (head != NULL)
	{
		grid.grid[k] = head->xslide;
		k++;
		head = head->next;
	}
	return (grid);
}
