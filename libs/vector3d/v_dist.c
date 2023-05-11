/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_dist.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 20:50:41 by albaud            #+#    #+#             */
/*   Updated: 2022/12/11 20:22:47 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_v3.h"

double	v_dist(const t_v3 *a, const t_v3 *b)
{
	return (sqrtf(pow(a->x - b->x, 2)
			+ pow(a->y - b->y, 2)
			+ pow(a->z - b->z, 2)));
}
