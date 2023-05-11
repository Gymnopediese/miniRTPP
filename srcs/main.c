/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:43:32 by albaud            #+#    #+#             */
/*   Updated: 2023/05/11 01:33:32 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <pthread.h>

int	update_screen(t_scene *scene)
{
	int	i;

	gradient_background(&scene->w.cvs, &(t_v3){100, 228, 228},
		&(t_v3){228, 119, 119});
	i = -1;
	scene->process_count = 0;
	while (++i < scene->process_amount)
		pthread_kill(scene->processes[i].thread, SIGUSR1);
	while (scene->process_count < scene->process_amount)
		usleep(1);
	ft_putimg(scene->w, scene->w.cvs.img, (t_vector){0, 0, 0, 0});
	return (0);
}

int	gui_update(t_scene *scene)
{
	apply_matrices(scene->objects, scene);
	update_screen(scene);
	return (0);
}

int	simple(t_scene *scene)
{
	static int	tick = 0;

	if (++tick < 1)
		return (0);
	tick = 0;
	if (inputs(scene) == 0)
		return (0);
	update_screen(scene);
	return (0);
}

void	init_intersects(t_scene *scene)
{
	scene->get_hit_point[SPHERE - SHAPE_START] = get_sphere_hit_point;
	scene->is_intersections[SPHERE - SHAPE_START] = is_sphere_hit;
	
	scene->get_hit_point[CYLINDRE - SHAPE_START] = get_cylindre_hit_point;
	scene->is_intersections[CYLINDRE - SHAPE_START] = is_cylindre_hit;

	scene->get_hit_point[PLAN - SHAPE_START] = get_plan_hit_point;
	scene->is_intersections[PLAN - SHAPE_START] = is_cylindre_hit;
}

void	init_scene(t_scene *scene)
{
	int	i;

	i = 0;
	scene->hook = &simple;
	ft_mlx_init(&scene->w, 800, 800, "miniRT");
	scene->w.cvs = ft_init_canvas(scene->w.mlx, 800, 800);
	scene->input_mode = -1;
	gradient_background(&scene->w.cvs, &(t_v3){100, 228, 228},
		&(t_v3){228, 119, 119});
	apply_matrices(scene->objects, scene);
	init_intersects(scene);
	i = -1;
	while (++i < 128)
		scene->inputs[i] = 0;
	print_scene(scene);
	iterate_objects(scene);
	ft_putimg(scene->w, scene->w.cvs.img, (t_vector){0, 0, 0, 0});
}

void	vo(int d)
{
	(void)d;
}

int	main(int argc, char **argv)
{
	t_scene		scene;

	if (argc != 2)
		error("miniRT: usage: ./miniRT <file.rt>");
	parse_rt_file(&scene, argv[1]);
	init_scene(&scene);
	signal(SIGUSR1, vo);
	init_threads(&scene, 10);
	mlx_hook(scene.w.win, 2, 0, keydown, scene.inputs);
	mlx_hook(scene.w.win, 3, 0, keyup, scene.inputs);
	mlx_loop_hook(scene.w.mlx, simple, &scene);
	mlx_loop(scene.w.mlx);
}
