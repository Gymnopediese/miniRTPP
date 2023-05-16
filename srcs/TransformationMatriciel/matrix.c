/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 01:56:53 by albaud            #+#    #+#             */
/*   Updated: 2023/05/16 01:24:12 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	apply_matrices(t_list *o, t_scene *scene)
{
	while (o)
	{
		m_transform(o->data, scene);
		o = o->next;
	}
}

void	m_clean(double a[SIZE][SIZE])
{
	int		x;
	int		y;

	x = -1;
	while (++x < SIZE)
	{
		y = -1;
		while (++y < SIZE)
		{
			a[x][y] = 0;
		}
	}
}

void	m_copy(double dest[SIZE][SIZE], double src[SIZE][SIZE])
{
	int		x;
	int		y;

	x = -1;
	while (++x < SIZE)
	{
		y = -1;
		while (++y < SIZE)
		{
			dest[x][y] = src[x][y];
		}
	}
}

void	m_print(double t[SIZE][SIZE], char *name)
{
	printf("printing matrix %s\n ", name);
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			printf("%f ", t[i][j]);
		}
		printf("\n");
	}
}
