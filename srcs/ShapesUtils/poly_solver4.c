/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poly_solver4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 21:51:02 by albaud            #+#    #+#             */
/*   Updated: 2023/05/15 21:58:18 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

/* Based on http://en.wikipedia.org/wiki/Cubic_equation#Cardano.27s_method
 *
 * Only provides one real result out of 3 possibly complex results.
 */

// double			s_real; 	0
// double			s_abs		1
// double			s_phase;	2
// double			u_abs;		3
// double			u_phase;	4
// double			u_real;		5
int	solve_depressed_cubic_cond(const double *poly, double *results, double *t)
{
	const double	q = poly[0];
	const double	p = poly[1];
	double			u;

	if (p == 0.0)
	{
		results[0] = cubic_root(-q);
		return (1);
	}
	*t = q * q / 4 + p * p * p / 27;
	if (*t >= 0.0)
	{
		u = cubic_root(-q / 2 + sqrt(*t));
		results[0] = u - p / 3.0 / u;
		return (1);
	}
	return (0);
}

int	solve_depressed_cubic(const double *poly, double *results)
{
	const double	q = poly[0];
	double			t;
	double			vars[6];

	if (solve_depressed_cubic_cond(poly, results, &t))
		return (1);
	vars[0] = -q / 2;
	vars[1] = sqrt(vars[0] * vars[0] - t);
	if (vars[0] >= 0)
		vars[2] = atan(sqrt(-t) / vars[0]) + 0;
	else
		vars[2] = atan(sqrt(-t) / vars[0]) + M_PI;
	vars[3] = cubic_root(vars[1]);
	vars[4] = vars[2] / 3.0;
	vars[5] = vars[3] * cos(vars[4]);
	results[0] = 2 * vars[5];
	return (1);
}

int	solve_real_poly_cond(int degree, const double *poly, double *results)
{
	const double	a = poly[degree];
	double			rev_poly[MAX_DEGREE + 1];
	int				i;
	int				num_results;

	if (degree == 0)
		return (0);
	if (a == 0)
		return (solve_real_poly(degree - 1, poly, results));
	if (degree > MAX_DEGREE)
		return (-1);
	if (degree > 2 && stableness_score(poly[degree], poly[degree - 1])
		> stableness_score(poly[0], poly[1]))
	{
		i = -1;
		while (++i <= degree)
			rev_poly[i] = poly[degree - i];
		num_results = solve_real_poly(degree, rev_poly, results);
		i = -1;
		while (++i < num_results)
			results[i] = 1.0 / results[i];
		return (num_results);
	}
	return (MAXINT);
}

int	solve_real_poly(int degree, const double *poly, double *results)
{
	double			normalized_poly[MAX_DEGREE + 1];
	int				i;
	const double	a = poly[degree];
	int				res;

	res = solve_real_poly_cond(degree, poly, results);
	if (res != MAXINT)
		return (res);
	i = -1;
	while (++i < degree)
		normalized_poly[i] = poly[i] / a;
	normalized_poly[degree] = 1.0;
	return (solve_normalized_poly(degree, normalized_poly, results));
}
