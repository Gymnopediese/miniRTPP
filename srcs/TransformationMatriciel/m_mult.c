/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_mult.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 20:34:09 by albaud            #+#    #+#             */
/*   Updated: 2023/05/10 22:14:21 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

// t_vector	m_4mult(const t_v3 *p, double m[4][4])
// {
// 	t_vector	r;

// 	r.x = p->x * m[0][0] + p->y * m[0][1] + p->z * m[0][2] + m[0][3];
// 	r.y = p->x * m[1][0] + p->y * m[1][1] + p->z * m[1][2] + m[1][3];
// 	r.z = p->x * m[2][0] + p->y * m[2][1] + p->z * m[2][2] + m[2][3];
// 	r.w = p->x * m[3][0] + p->y * m[3][1] + p->z * m[3][2] + m[3][3];
// 	return (r);
// }

t_v3	m_3mult(const t_v3 *p, const double m[4][4])
{
	t_v3	r;

	r.x = p->x * m[0][0] + p->y * m[0][1] + p->z * m[0][2] + m[0][3];
	r.y = p->x * m[1][0] + p->y * m[1][1] + p->z * m[1][2] + m[1][3];
	r.z = p->x * m[2][0] + p->y * m[2][1] + p->z * m[2][2] + m[2][3];
	return (r);
}

t_v3	m_3mults(const t_v3 *p, const double m[4][4])
{
	t_v3	r;

	r.x = p->x * m[0][0] + p->y * m[0][1] + p->z * m[0][2];
	r.y = p->x * m[1][0] + p->y * m[1][1] + p->z * m[1][2];
	r.z = p->x * m[2][0] + p->y * m[2][1] + p->z * m[2][2];
	return (r);
}

void	m_mult(double a[SIZE][SIZE], double b[SIZE][SIZE])
{
	int		x;
	int		y;
	int		z;
	double	t[SIZE][SIZE];

	x = -1;
	m_clean(t);
	while (++x < SIZE)
	{
		y = -1;
		while (++y < SIZE)
		{
			z = -1;
			while (++z < SIZE)
			{
				t[x][z] += a[x][y] * b[y][z];
			}
		}
	}
	m_copy(a, t);
}
