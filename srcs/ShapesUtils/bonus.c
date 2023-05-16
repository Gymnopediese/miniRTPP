/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 19:08:40 by albaud            #+#    #+#             */
/*   Updated: 2023/05/16 18:30:58 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_v3	col_v(long col)
{
	return ((t_v3){
		(double)((col & 0xFF0000) >> 16) / 255,
		(double)((col & 0xFF00) >> 8) / 255,
		(double)(col & 0xFF) / 255
	});
}

t_v3	damier(const t_obj *obj, t_v3 *uv)
{
	// if (uv->x <= 0)
	// 	uv->x += obj->damier.x;
	// if (uv->y <= 0)
	// 	uv->y += obj->damier.y;
	if ((int)round(uv->x * obj->damier.x) % 2
		&& (int)round(uv->y * obj->damier.y) % 2)
		return (obj->color);
	if ((int)round(uv->x * obj->damier.x) % 2
		&& (int)round(uv->y * obj->damier.y) % 2 == 0)
		return (obj->color2);
	if ((int)round(uv->x * obj->damier.x) % 2 == 0
		&& (int)round(uv->y * obj->damier.y) % 2)
		return (obj->color2);
	return (obj->color);
}

t_v3	texture(const t_obj *obj, t_v3 uv)
{
	uv.x *= obj->texture.x;
	uv.y *= obj->texture.y;
	uv.x = (int)fabs(uv.x) % obj->texture.x;
	uv.y = (int)fabs(uv.y) % obj->texture.y;
	return (col_v(ft_get_color(&obj->texture, (int)uv.x, (int)uv.y)));
}

void	bumpmap(const t_obj *obj, t_v3 uv, t_hit *hit)
{
	t_v3	deformation;

	uv.x *= obj->bumpmap.x;
	uv.y *= obj->bumpmap.y;
	uv.x = (int)fabs(uv.x) % obj->bumpmap.x;
	uv.y = (int)fabs(uv.y) % obj->bumpmap.y;
	deformation = col_v(ft_get_color(&obj->bumpmap, (int)uv.x, (int)uv.y));
	v_cunit(&hit->normal);
	//print_vector(hit->normal, "avanst");
	hit->normal.x += (deformation.x * 2 - 1) / PI * 2;
	hit->normal.y += (deformation.y * 2 - 1) / PI * 2;
	hit->normal.z += (deformation.z) / PI * 2;
	//print_vector(hit->normal, "apres");
}

int	get_color(const t_obj *obj, t_hit *hit, int mode)
{
	t_v3	uv;

	uv = obj->funcs->uv(&hit->ray.origin, mode);
	if (obj->mode == NORMAL)
		hit->color = obj->color;
	else if (obj->mode == DAMIER)
		hit->color = damier(obj, &uv);
	else
		hit->color = texture(obj, uv);
	if (obj->bmap)
		bumpmap(obj, uv, hit);
	return (1);
}
