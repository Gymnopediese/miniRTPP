/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   torus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 16:30:00 by albaud            #+#    #+#             */
/*   Updated: 2023/05/16 10:48:07 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"

void	torus_normal(t_hit *hit, int mode)
{
	t_v3	t;

	(void) mode;
	t = (t_v3){hit->ray.origin.x, 0, hit->ray.origin.z};
	v_normalize(&t);
	hit->normal = v_rm(&hit->ray.origin, &t);
}

t_v3	torus_uv(t_v3 *hit, int mode)
{
	(void) mode;
	return ((t_v3){atan(hit->z / hit->x), hit->y, 0});
}

void	torus_function(t_ray *local, double *sols)
{
	double		poly[5];

	poly[4] = pow(v_dotp(&local->direction, &local->direction), 2);
	poly[3] = 4 * v_dotp(&local->direction, &local->direction)
		* v_dotp(&local->direction, &local->origin);
	poly[2] = 2 * v_dotp(&local->direction, &local->direction)
		* (v_dotp(&local->origin, &local->origin) - 1.25)
		+ 4 * pow(v_dotp(&local->direction, &local->origin), 2)
		+ 4 * local->direction.y * local->direction.y;
	poly[1] = 4 * (v_dotp(&local->origin, &local->origin) - 1.25)
		* v_dotp(&local->direction, &local->origin)
		+ 8 * local->direction.y * local->origin.y;
	poly[0] = pow((v_dotp(&local->origin, &local->origin) - 1.25), 2)
		- 4 * (0.25 - local->origin.y * local->origin.y);
	solve_real_poly(4, poly, sols);
}
