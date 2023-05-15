/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 12:42:18 by albaud            #+#    #+#             */
/*   Updated: 2023/05/15 12:26:38 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H
# define SIZE 4
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

void		rotation(t_obj *obj, double t[SIZE][SIZE]);
void		m_inverse(double comatr[4][4], int f);

void		local_to_global(t_v3 *r, const t_obj *obj);
void		global_to_local(const t_ray *r, t_ray *new, const t_obj *obj);


// Sphere

// return true if ray intersect sphere
int			is_sphere_hit(const t_ray *r, const t_obj *sphere);
int			get_sphere_hit_point(const t_ray *r, const t_obj *sphere,
				t_hit *hit);

int			is_cylindre_hit(const t_ray *ray, const t_obj *obj);
int			get_cylindre_hit_point(const t_ray *ray, const t_obj *cylindre,
				t_hit *hit);

int			get_plan_hit_point(const t_ray *ray, const t_obj *plan, t_hit *hit);

#endif
