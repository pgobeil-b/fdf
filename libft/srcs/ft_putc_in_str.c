/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putc_in_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgobeil- <pgobeil-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 11:36:59 by pgobeil-          #+#    #+#             */
/*   Updated: 2019/09/14 12:35:01 by pgobeil-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putc_in_str(char *src, char c, int start, int len)
{
	int cool_len;

	cool_len = len;
	while (len)
	{
		src[start] = c;
		len--;
		start++;
	}
	return (cool_len);
}
