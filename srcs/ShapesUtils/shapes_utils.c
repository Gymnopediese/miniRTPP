/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:30:48 by albaud            #+#    #+#             */
/*   Updated: 2023/05/15 21:49:55 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_v3	v_units(const t_v3 *a)
{
	double	norm;

	norm = v_norm(a);
	return ((t_v3){
		a->x / (norm + 1),
		a->y / (norm + 1),
		a->z / (norm + 1),
	});
}

void	find_delta(t_eqt2 *eq)
{
	eq->delta = eq->b * eq->b - 4 * eq->a * eq->c;
}

void	find_xs(t_eqt2 *eq)
{
	eq->x1 = (-eq->b + sqrt(eq->delta)) / (2.0 * eq->a);
	eq->x2 = (-eq->b - sqrt(eq->delta)) / (2.0 * eq->a);
}

void	ftswap(double *a, double *b)
{
	double	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	ft_bubble(double *arr, int size)
{
	int	flag;
	int	loop;

	flag = 1;
	while (flag)
	{
		loop = -1;
		flag = 0;
		while (++loop < size - 1)
		{
			if (arr[loop] > arr[loop + 1])
			{
				ftswap(&arr[loop], &arr[loop + 1]);
				flag = 1;
			}
		}
	}
}
