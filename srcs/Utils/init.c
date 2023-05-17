/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 01:08:12 by albaud            #+#    #+#             */
/*   Updated: 2023/05/17 14:05:48 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	init_intersects(t_scene *scene)
{
	scene->obj_funcs[SPHERE - SHAPE_START] = (t_funcs){
		sphere_function, sphere_normal, no_condition, sphere_uv,};
	scene->obj_funcs[PLAN - SHAPE_START] = (t_funcs){
		plan_function, plan_normal, no_condition, plan_uv,};
	scene->obj_funcs[CYLINDRE - SHAPE_START] = (t_funcs){
		cylindre_function, cylindre_normal, cylindre_condition, cylindre_uv,};
	scene->obj_funcs[TORUS - SHAPE_START] = (t_funcs){
		torus_function, torus_normal, no_condition, torus_uv,};
	scene->obj_funcs[CONE - SHAPE_START] = (t_funcs){
		cone_function, cone_normal, cone_condition, cylindre_uv,};
	scene->obj_funcs[HYPERBOILD - SHAPE_START] = (t_funcs){hyperboloid_function,
		cylindre_normal, hyperboloid_condition, cylindre_uv,};
	scene->obj_funcs[HYPERBOILD2 - SHAPE_START] = (t_funcs){
		hyperboloid2_function, cylindre_normal, hyperboloid2_condition,
		cylindre_uv,};
	scene->obj_funcs[PARABOLOID2 - SHAPE_START] = (t_funcs){
		paraboloid2_function,
		cylindre_normal, paraboloid2_condition, cylindre_uv,};
	scene->obj_funcs[PARABOLOID - SHAPE_START] = (t_funcs){paraboloid_function,
		cylindre_normal, paraboloid_condition, cylindre_uv,};
	scene->obj_funcs[CUBE - SHAPE_START] = (t_funcs){
		cube_function, cube_normal, no_condition, cube_uv,};
	scene->obj_funcs[CAPSULE - SHAPE_START] = (t_funcs){
		capsule_function, capsule_normal, capsule_condition, capsule_uv,};
}

void	init_scene(t_scene *scene)
{
	int	i;

	i = 0;
	scene->hook = &simple;
	scene->w.cvs = ft_init_canvas(scene->w.mlx, X, Y);
	scene->input_mode = -1;
	gradient_background(&scene->w.cvs, &(t_v3){100, 228, 228},
		&(t_v3){228, 119, 119});
	apply_matrices(scene->objects, scene);
	i = -1;
	while (++i < 128)
		scene->inputs[i] = 0;
	iterate_objects(scene);
	ft_putimg(scene->w, scene->w.cvs.img, (t_vector){0, 0, 0, 0});
}
