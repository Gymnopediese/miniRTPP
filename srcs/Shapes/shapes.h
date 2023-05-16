/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 12:42:18 by albaud            #+#    #+#             */
/*   Updated: 2023/05/16 10:48:24 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H
# define SIZE 4
# define MAX_DEGREE 4
# include "../header.h"

void		find_delta(t_eqt2 *eq);
t_v3		v_units(const t_v3 *a);
void		find_xs(t_eqt2 *eq);
void		set_hit_point(t_hit *hit, t_ray *ray, t_obj *obj, double d);

void		m_clean(double a[SIZE][SIZE]);
void		m_mult(double a[SIZE][SIZE], double b[SIZE][SIZE]);
void		m_copy(double dest[SIZE][SIZE], double src[SIZE][SIZE]);
double		determin(double matrix[4][4], int k);
void		m_one(double t[SIZE][SIZE]);

int			paraboloid_intersect(t_ray *ray, t_obj *cylindre, t_hit *hit);
t_v3		*paraboloid2_intersect(t_ray *ray, t_obj *cylindre, t_v3 *hit);
t_v3		m_3mults(const t_v3 *p, const double m[4][4]);
t_v3		m_3mult(const t_v3 *p, const double m[4][4]);
void		m_print(double t[SIZE][SIZE], char *name);
void		m_transform(t_obj *obj, t_scene *scene);
int			hyperboloid_intersect(t_ray *ray, t_obj *cylindre, t_hit *hit);
t_v3		*cone_intersect(t_ray *ray, t_obj *cone, t_v3 *hit);
int			cylindre_intersect(t_ray *ray, t_obj *cylindre, t_hit *hit);
int			plan_intersect(t_ray *ray, t_obj *plan, t_hit *hit);
void		iterate_objects(t_scene *scene);
t_v3		*hyperboloid2_intersect(t_ray *ray, t_obj *cylindre, t_v3 *hit);
int			sphere_intersect(t_ray *r, t_obj *sphere, t_hit *hit);
t_hit		*sphere_reflection(t_hit *hit, t_v3 *origine);
// t_v3		sphere_reflection(t_ray *ray, t_obj *sphere, t_v3 *hit);

void		rotation(t_obj *obj, double t[SIZE][SIZE]);
void		m_inverse(double comatr[4][4], int f);

void		local_to_global(t_v3 *r, const t_obj *obj);
void		global_to_local(const t_ray *r, t_ray *new, const t_obj *obj);

// Sphere

t_v3		damier(const t_obj *obj, t_v3 *uv);
t_v3		texture(const t_obj *obj, t_v3 *uv);

// return true if ray intersect sphere
void		sphere_function(t_ray *ray, double *sols);
void		sphere_normal(t_hit *hit, int mode);
int			no_condition(const t_ray *local);
t_v3		sphere_uv(t_v3 *hit, int mode);

void		torus_normal(t_hit *hit, int mode);
t_v3		torus_uv(t_v3 *hit, int mode);
void		torus_function(t_ray *ray, double *sols);

void		plan_function(const t_ray *ray, double *sols);
void		plan_normal(t_hit *hit, int mode);
t_v3		plan_uv(t_v3 *hit, int mode);

void		cylindre_function(t_ray *ray, double *sols);
void		cylindre_normal(t_hit *hit, int mode);
t_v3		cylindre_uv(t_v3 *hit, int mode);
int			cylindre_condition(const t_ray *local);

void		capsule_function(t_ray *ray, double *sols);
void		capsule_normal(t_hit *hit, int mode);
t_v3		capsule_uv(t_v3 *hit, int mode);
int			capsule_condition(const t_ray *local);

void		cone_function(t_ray *ray, double *sols);
void		cone_normal(t_hit *hit, int mode);
t_v3		cone_uv(t_v3 *hit, int mode);
int			cone_condition(const t_ray *local);

void		hyperboloid_function(t_ray *ray, double *sols);
void		hyperboloid_normal(t_hit *hit, int mode);
t_v3		hyperboloid_uv(t_v3 *hit, int mode);
int			hyperboloid_condition(const t_ray *local);

void		hyperboloid2_function(t_ray *ray, double *sols);
void		hyperboloid2_normal(t_hit *hit, int mode);
t_v3		hyperboloid2_uv(t_v3 *hit, int mode);
int			hyperboloid2_condition(const t_ray *local);

void		paraboloid_function(t_ray *ray, double *sols);
void		paraboloid_normal(t_hit *hit, int mode);
t_v3		paraboloid_uv(t_v3 *hit, int mode);
int			paraboloid_condition(const t_ray *local);

void		paraboloid2_function(t_ray *ray, double *sols);
void		paraboloid2_normal(t_hit *hit, int mode);
t_v3		paraboloid2_uv(t_v3 *hit, int mode);
int			paraboloid2_condition(const t_ray *local);

void		cube_function(const t_ray *ray, double *sols);
void		cube_normal(t_hit *hit, int mode);
t_v3		cube_uv(t_v3 *hit, int mode);
int			cube_condition(const t_ray *local);

int			get_obj_point(const t_ray *ray,
				const t_obj *obj, t_hit *hit, int full);

int			get_point(const t_ray *ray, const t_obj *obj, t_hit *hit, int full);

int			get_torus_hit_point(const t_ray *r,
				const t_obj *sphere, t_hit *hit, int full);

int			solve_real_poly(int degree, const double *poly, double *results);

void		ft_bubble(double *arr, int size);

int			get_color(const t_obj *obj, t_hit *hit, int mode);

double		stableness_score(double a, double b);
int			solve_normalized_poly(int degree, const double *poly,
				double *results);
void		calc_shifted_coefs(double shift, int degree,
				const double *src, double *dst);
void		calc_binomials(int num_binoms, int stride, double *dst);
void		calc_powers(double x, int max_power, double *dst);
int			solve_depressed_poly(int degree,
				const double *poly, double *results);
int			solve_depressed_quartic(const double *poly, double *results);
int			solve_depressed_cubic(const double *poly, double *results);
double		cubic_root(double x);
int			solve_depressed_quadratic(const double *poly, double *results);
#endif
