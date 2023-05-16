/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poly_solver3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 20:33:00 by albaud            #+#    #+#             */
/*   Updated: 2023/05/15 21:59:25 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

double	cubic_root(double x)
{
	const double	t = pow(fabs(x), 1.0 / 3.0);

	if (x >= 0.0)
		return (t);
	return (-t);
}

/* Depressed polynomials have the form of:
 *   x^n + a*x^(n-2) + ..
 * The coefficient for x^n is 1 and for x^(n-1) is zero.
 * So it gets 3 coefficients for a depressed quartic polynom.
 */
int	solve_depressed_poly(int degree,
	const double *poly, double *results)
{
	if (degree > 0 && poly[0] == 0.0)
	{
		results[0] = 0;
		return (1 + solve_depressed_poly(degree - 1, poly + 1, results + 1));
	}
	if (degree == 4)
		return (solve_depressed_quartic(poly, results));
	if (degree == 3)
		return (solve_depressed_cubic(poly, results));
	if (degree == 2)
		return (solve_depressed_quadratic(poly, results));
	if (degree == 1)
	{
		results[0] = 0.0;
		return (1);
	}
	if (degree == 0)
		return (0);
	return (-1);
}

void	calc_powers(double x, int max_power, double *dst)
{
	int	i;

	dst[0] = 1.0;
	if (max_power >= 1)
		dst[1] = x;
	i = 1;
	while (++i <= max_power)
		dst[i] = x * dst[i - 1];
}
