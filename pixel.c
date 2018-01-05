/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/03 13:15:34 by ttshivhu          #+#    #+#             */
/*   Updated: 2018/01/03 13:26:03 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		draw_pixel(t_pixel **ptr, int x, int y)
{
	int		i;

	i = (x * 4) + (y * (*ptr)->sl);
	(*ptr)->c_img[i] = (*ptr)->color;
	(*ptr)->c_img[++i] = (*ptr)->color >> 8;
	(*ptr)->c_img[++i] = (*ptr)->color >> 16;
}

void		vertline(t_pixel *ptr, int x, int start, int end)
{
	while (start < end)
	{
		draw_pixel(&ptr, x, start);
		start++;
	}
}