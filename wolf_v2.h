/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_v2.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 12:30:38 by ttshivhu          #+#    #+#             */
/*   Updated: 2018/02/19 12:36:47 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_V2
# define WOLF_V2

typedef struct		s_mem
{
	void			*ptr;
	void			*data;
	int				count;
	struct s_mem	*next;
}					t_mem;

#endif
