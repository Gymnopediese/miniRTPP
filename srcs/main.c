/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:43:32 by albaud            #+#    #+#             */
/*   Updated: 2023/05/17 14:07:33 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <pthread.h>
#define ANIMATION MAXINT

int	update_screen(t_scene *scene)
{
	int	i;

	gradient_background(&scene->w.cvs, &(t_v3){100, 228, 228},
		&(t_v3){228, 119, 119});
	i = -1;
	scene->process_count = 0;
	iterate_objects(scene);
	ft_putimg(scene->w, scene->w.cvs.img, (t_vector){0, 0, 0, 0});
	return (0);
}

int	simple(t_scene *scene)
{
	static int	tick = 0;

	if (++tick < 1)
		return (0);
	tick = 0;
	if (scene->animation)
	{
		apply_matrices(scene->objects, scene);
		update_screen(scene);
	}
	scene->motion = (t_v3){0, 0, 0};
	if (inputs(scene))
	{
		ft_pitch(&scene->motion, scene->camera->orientation.x);
		ft_yaw(&scene->motion, scene->camera->orientation.y);
		v_cadd(&scene->camera->pos, &scene->motion);
		update_screen(scene);
	}
	return (0);
}

int	finish(t_scene *scene)
{
	(void) scene;
	ft_garbage_colector(0, 1, 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_scene		scene;

	ft_bzero(&scene, sizeof(t_scene));
	if (argc < 2 || argc > 3)
		error("miniRT: usage: ./miniRT <file.rt> [resolution]");
	scene.resolution = 1;
	if (argc == 3)
		scene.resolution = ft_atoi(argv[2]);
	if (scene.resolution <= 0 || scene.resolution > 10)
	{
		ft_putendl("invalid resolution -> resolution set to 1 by default");
		scene.resolution = 1;
	}
	ft_mlx_init(&scene.w, X, Y, "miniRT");
	init_intersects(&scene);
	get_mlx(scene.w.mlx);
	parse_rt_file(&scene, argv[1]);
	init_scene(&scene);
	mlx_hook(scene.w.win, 2, 0, keydown, scene.inputs);
	mlx_hook(scene.w.win, 3, 0, keyup, scene.inputs);
	mlx_hook(scene.w.win, 17, 0, finish, &scene);
	mlx_loop_hook(scene.w.mlx, simple, &scene);
	mlx_loop(scene.w.mlx);
}
