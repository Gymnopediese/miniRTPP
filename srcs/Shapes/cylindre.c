/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindre.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:50:34 by albaud            #+#    #+#             */
/*   Updated: 2023/05/11 01:32:55 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

int	is_cylindre_hit(const t_ray *ray, const t_obj *cylindre)
{
	t_eqt2	e;
	t_ray	r;

	global_to_local(ray, &r, cylindre);
	e.a = r.direction.x * r.direction.x
		+ r.direction.y * r.direction.y;
	e.b = 2 * (r.direction.x * r.origin.x
			+ r.direction.y * r.origin.y);
	e.c = r.origin.x * r.origin.x + r.origin.y * r.origin.y
		- cylindre->diametre / 2 * cylindre->diametre / 2;
	find_delta(&e);
	if (e.delta < 0)
		return (0);
	if (e.x2 < e.x1)
		r.origin = v_ponline(&r.origin, &r.direction, e.x2);
	else
		r.origin = v_ponline(&r.origin, &r.direction, e.x1);
	if (fabs(r.origin.z) > cylindre->hauteur)
		return (0);
	return (1);
}

void	cylindre_equation(t_eqt2 *e, const t_ray *ray, const t_obj *obj)
{
	e->a = ray->direction.x * ray->direction.x
		+ ray->direction.y * ray->direction.y;
	e->b = 2 * (ray->direction.x * ray->origin.x
			+ ray->direction.y * ray->origin.y);
	e->c = ray->origin.x * ray->origin.x + ray->origin.y * ray->origin.y
		- obj->diametre / 2 * obj->diametre / 2;
	find_delta(e);
	if (e->delta < 0)
		return ;
	find_xs(e);
}

int	get_cylindre_hit_point(const t_ray *ray, const t_obj *cylindre, t_hit *hit)
{
	t_eqt2	e;
	t_ray	r;
	double	dist;

	global_to_local(ray, &r, cylindre);
	cylindre_equation(&e, &r, cylindre);

	if (e.delta < 0)
		return (0);
	dist = fmin(e.x1, e.x2);
	if (dist < 0)
		return (0);
	r.origin = v_ponline(&r.origin, &r.direction, dist);
	if (fabs(r.origin.z) > cylindre->hauteur)
		return (0);
	hit->normal = (t_v3){r.origin.x, r.origin.y, 0};
	hit->normal = m_3mult(&hit->normal, cylindre->transform);
	hit->ray.origin = m_3mult(&r.origin, cylindre->transform);
	hit->obj = cylindre;
	return (1);
}
