/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paraboloid2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:50:34 by albaud            #+#    #+#             */
/*   Updated: 2023/05/17 13:05:15 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	paraboloid2_function(t_ray *ray, double *sols)
{
	t_eqt2	e;

	e.a = ray->direction.x * ray->direction.x
		- ray->direction.y * ray->direction.y;
	e.b = 2 * (ray->direction.x * ray->origin.x
			- ray->direction.y * ray->origin.y)
		- ray->direction.z;
	e.c = ray->origin.x * ray->origin.x
		- ray->origin.y * ray->origin.y
		- ray->origin.z;
	find_delta(&e);
	if (e.delta < 0)
		return ;
	sols[0] = (-e.b + sqrt(e.delta)) / (2.0 * e.a);
	sols[1] = (-e.b - sqrt(e.delta)) / (2.0 * e.a);
}

int	paraboloid2_condition(const t_ray *local)
{
	return (fabs(local->origin.z) < 1.01
		&& fabs(local->origin.y) < 1.01 && fabs(local->origin.x) < 1.01);
}
