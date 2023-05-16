/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:11:47 by albaud            #+#    #+#             */
/*   Updated: 2023/05/12 10:34:21 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#define MIN_SCOLOR 0.01

long int	ft_get_color(const t_canvas *cvs, int x, int y)
{
	unsigned char		*pix;
	unsigned long int	col;

	pix = (unsigned char *)ft_get_pixel(cvs, x, y);
	col = 0;
	col = (col << 8) + (((int)pix[3]));
	col = (col << 8) + (((int)pix[2]));
	col = (col << 8) + (((int)pix[1]));
	col = (col << 8) + (((int)pix[0]));
	return (col);
}

void	brightness(t_v3 *tmp_color, const t_v3 *origine_pos,
	const t_hit *hit, const t_scene *scene)
{
	t_list	*objects;
	t_ray	r;

	(void) origine_pos;
	objects = scene->objects;
	r.direction = v_rm(&scene->light->pos, &hit->ray.origin);
	r.origin = hit->ray.origin;
	if (hit_any_obj(scene, &r))
	{
		v_cnmult(tmp_color, 0.0);
		return ;
	}
	v_cmult(tmp_color, &scene->light->color);
	v_cnmult(tmp_color, cos(v_angle(&r.direction, &hit->normal)));
}
