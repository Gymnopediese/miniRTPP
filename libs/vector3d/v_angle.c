/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_angle.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 21:14:37 by albaud            #+#    #+#             */
/*   Updated: 2023/05/15 13:51:10 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_v3.h"

//θ = cos^-1 [ (a · b) / (|a| |b|) ]
double	v_angle(const t_v3 *a, const t_v3 *b)
{
	return (acos((v_dotp(a, b) / (v_norm(a) * v_norm(b)))));
}
