/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyperboloid2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:50:34 by albaud            #+#    #+#             */
/*   Updated: 2023/05/10 21:30:54 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#define A 1
#define B 1
#define C 1

t_v3	*hyperboloid2_intersect(t_ray *ray, t_obj *cylindre, t_v3 *hit)
{
	double	a;
	double	b;
	double	c;
	double	x;
	t_ray	r;

	double	xm;
	double	ym;
	double	zm;

	xm = B * B * C * C;
	ym = A * A * C * C;
	zm = B * B * A * A;
	global_to_local(ray, &r, cylindre);
	a = r.direction.x * r.direction.x * xm + r.direction.y * r.direction.y * ym - r.direction.z * r.direction.z * zm;
	b = 2 * (r.direction.x * r.origin.x * xm + r.direction.y * r.origin.y * ym - r.direction.z * r.origin.z * zm);
	c = r.origin.x * r.origin.x * xm + r.origin.y * r.origin.y * ym - r.origin.z * r.origin.z * zm + 1;
	x = b * b - 4 * a * c;
	if (x <= 0)
		return (0);
	c = (-b + sqrt(x)) / (2 * a);
	x = (-b - sqrt(x)) / (2 * a);
	// v_4print(&r.origin, "local ray origine\t");
	// v_4print(&r->origin, "ray origine\t");
	// v_4print(&r.direction, "local ray direction\t");
	if (c < x)
		r.origin = v_ponline(&r.origin, &r.direction, c);
	else
		r.origin = v_ponline(&r.origin, &r.direction, x);
	if (c <= 0 || x <= 0 || fabs(r.origin.z) > 2)
		return (0);
	//v_4print(&r.origin, "local\t");
	r.origin = m_3mult(&r.origin, cylindre->transform);
	//v_4print(&r.origin, "gloabal\t");
	hit->x = r.origin.x;
	hit->y = r.origin.y;
	hit->z = r.origin.z;

	return (hit);
}

// t_hit	*sphere_reflection(t_hit *hit, t_v3 *origine)
// {
// 	double	bc;
// 	t_v3	ba;
// 	t_v3	c;
// 	t_v3	res;

// 	ba = v_rm(origine, &hit->ray.origin);
// 	bc = cos(v_angle(&ba, &hit->normal)) * v_dist(&hit->ray.origin, origine);
// 	c = v_unit(&hit->normal);
// 	c = v_ponline(&hit->ray.origin, &c, bc);
// 	res = v_rm(&c, origine);
// 	v_cnmult(&res, 2);
// 	hit->ray.direction = v_rm(&res, &hit->ray.origin);
// 	return (hit);
// }
