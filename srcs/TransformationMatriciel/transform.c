/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 23:06:00 by albaud            #+#    #+#             */
/*   Updated: 2023/05/17 09:24:21 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	m_one(double t[SIZE][SIZE])
{
	int	i;

	i = -1;
	while (++i < SIZE)
		t[i][i] = 1;
}

void	_scaling(t_obj *obj, double t[SIZE][SIZE])
{
	m_clean(t);
	m_one(t);
	t[0][0] = obj->scale.x;
	t[1][1] = obj->scale.y;
	t[2][2] = obj->scale.z;
	m_mult(obj->transform, t);
}

void	_tranpose(t_obj *obj, double t[SIZE][SIZE])
{
	m_clean(t);
	m_one(t);
	t[0][3] = obj->pos.x;
	t[1][3] = obj->pos.y;
	t[2][3] = obj->pos.z;
	m_mult(obj->transform, t);
}

void	anim(t_obj *obj)
{
	obj->orientation = (t_v3){
		obj->orientation.x + obj->rotation.x,
		obj->orientation.y + obj->rotation.y,
		obj->orientation.z + obj->rotation.z
	};
	if (obj->orientation.x < -PI)
		obj->orientation.x = PI;
	if (obj->orientation.y < -PI)
		obj->orientation.y = PI;
	if (obj->orientation.z < -PI)
		obj->orientation.z = PI;
	if (obj->orientation.x > PI)
		obj->orientation.x = -PI;
	if (obj->orientation.y > PI)
		obj->orientation.y = -PI;
	if (obj->orientation.z > PI)
		obj->orientation.z = -PI;
	v_cadd(&obj->scale, &obj->scale_anim);
	if (++obj->scale_index > obj->scale_period)
	{
		obj->scale_index = 0;
		v_cnmult(&obj->scale_anim, -1);
	}
}

void	m_transform(t_obj *obj, t_scene *scene)
{
	double	t[SIZE][SIZE];
	double	tx;

	(void) scene;
	m_clean(obj->transform);
	m_one(obj->transform);
	_tranpose(obj, t);
	rotation(obj, t);
	_scaling(obj, t);
	m_copy(obj->inverse_transform, obj->transform);
	tx = determin(obj->inverse_transform, 4);
	if (tx == 0)
		error("scale vector cannot have 0 in it");
	else
		m_inverse(obj->inverse_transform, 4);
	m_print(obj->transform, "NOR");
	m_print(obj->inverse_transform, "INV");
	anim(obj);
}
