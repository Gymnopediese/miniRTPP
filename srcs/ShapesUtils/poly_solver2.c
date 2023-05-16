/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poly_solver2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 20:30:31 by albaud            #+#    #+#             */
/*   Updated: 2023/05/16 11:05:10 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

double	stableness_score(double a, double b)
{
	const double	t = fabs(a / b);

	return (t + 1.0 / t);
}

int	solve_normalized_poly(int degree,
	const double *poly, double *results)
{
	const double	shift = -poly[degree - 1] / (double) degree;
	double			shifted_coefs[MAX_DEGREE + 1];
	int				i;
	int				num_results;

	calc_shifted_coefs(shift, degree, poly, shifted_coefs);
	num_results = solve_depressed_poly(degree, shifted_coefs, results);
	i = -1;
	while (++i < num_results)
		results[i] += shift;
	return (num_results);
}

void	calc_shifted_coefs(double shift, int degree,
	const double *src, double *dst)
{
	double	binomials[MAX_DEGREE + 1][MAX_DEGREE + 1];
	double	shift_powers[MAX_DEGREE + 1];
	int		dst_i;
	int		src_i;

	dst_i = -1;
	while (++dst_i <= degree)
		dst[dst_i] = 0;
	calc_binomials(degree + 1,
		sizeof(binomials[0]) / sizeof(binomials[0][0]), binomials[0]);
	calc_powers(shift, degree, shift_powers);
	src_i = -1;
	while (++src_i <= degree)
	{
		dst_i = -1;
		while (++dst_i <= src_i)
			dst[dst_i] += src[src_i] * shift_powers[src_i - dst_i]
				* binomials[src_i][dst_i];
	}
}

void	calc_binomials(int num_binoms, int stride, double *dst)
{
	int			row;
	int			row_idx;
	int			prev_row_idx;
	int			col;

	row = -1;
	while (++row < num_binoms)
	{
		row_idx = row * stride;
		prev_row_idx = (row - 1) * stride;
		col = 0;
		dst[row_idx] = 1;
		while (++col < row)
			dst[row_idx + col] = dst[prev_row_idx + col - 1]
				+ dst[prev_row_idx + col];
		dst[row_idx + row] = 1;
	}
}

int	solve_depressed_quadratic(const double *poly, double *results)
{
	const double	t = sqrt(-poly[0]);

	results[0] = -t;
	results[1] = t;
	return (2);
}
