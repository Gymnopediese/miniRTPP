/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poly_solver.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 16:31:34 by albaud            #+#    #+#             */
/*   Updated: 2023/05/16 11:37:29 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Solve Polynomials of up to the fourth degree. (over real numbers)
 * Algorithms by Ferrari, Tartaglia, Cardano, et al. (16th century Italy)
 */

#include "../header.h"

#include <math.h>

/* poly: pointer to coefficients array of size degree + 1.
 * results: pointer to results output array of size degree.
 */

// double			p;			0
// const double	e = poly[0];	1
// const double	d = poly[1];	2
// const double	c = poly[2];	3

int	poly_1(const double *poly, double *results)
{
	int		i;
	int		num_quad_results;
	double	quadratic[3];
	double	quadratic_results[2];
	double	s;

	quadratic[0] = poly[0];
	quadratic[1] = poly[2];
	quadratic[2] = 1;
	num_quad_results = solve_real_poly(2, quadratic, quadratic_results);
	i = -1;
	while (++i < num_quad_results)
	{
		s = sqrt(quadratic_results[i]);
		results[2 * i] = -s;
		results[2 * i + 1] = s;
	}
	return (2 * num_quad_results);
}

int	solve_depressed_quartic(const double *poly, double *results)
{
	double			helper_cubic[4];
	double			helper_results[3];
	double			quadratic_factor[3];
	double			p;
	int				num_results;

	if (poly[1] == 0)
		return (poly_1(poly, results));
	helper_cubic[0] = -poly[1] * poly[1];
	helper_cubic[1] = poly[2] * poly[2] - 4 * poly[0];
	helper_cubic[2] = 2 * poly[2];
	helper_cubic[3] = 1;
	if (solve_real_poly(3, helper_cubic, helper_results) < 1)
		return (0);
	p = sqrt(helper_results[0]);
	quadratic_factor[0] = poly[2] + p * p - poly[1] / p;
	quadratic_factor[1] = 2 * p;
	quadratic_factor[2] = 2;
	num_results = solve_real_poly(2, quadratic_factor, results);
	quadratic_factor[0] = poly[2] + p * p + poly[1] / p;
	quadratic_factor[1] = -2 * p;
	return (num_results
		+ solve_real_poly(2, quadratic_factor, results + num_results));
}
