/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_local_convertion.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:06:38 by albaud            #+#    #+#             */
/*   Updated: 2023/05/11 12:00:59 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	local_to_global(t_v3 *r, const t_obj *obj)
{
	*r = m_3mult(r, obj->transform);
}

void	global_to_local(const t_ray *r, t_ray *new, const t_obj *obj)
{
	new->origin = m_3mult(&r->origin, obj->inverse_transform);
	new->direction = m_3mults(&r->direction, obj->inverse_transform);
	new->direction = v_unit(&new->direction);
}
