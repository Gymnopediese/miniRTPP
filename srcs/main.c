/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:43:32 by albaud            #+#    #+#             */
/*   Updated: 2023/05/16 11:31:40 by albaud           ###   ########.fr       */
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
	while (++i < scene->process_amount)
		pthread_kill(scene->processes[i].thread, SIGUSR1);
	while (scene->process_count < scene->process_amount)
		usleep(1);
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
	else if (inputs(scene))
		update_screen(scene);
	return (0);
}

void	vo(int d)
{
	(void)d;
}

int	main(int argc, char **argv)
{
	t_scene		scene;

	ft_bzero(&scene, sizeof(t_scene));
	if (argc != 2)
		error("miniRT: usage: ./miniRT <file.rt>");
	ft_mlx_init(&scene.w, 800, 800, "miniRT");
	init_intersects(&scene);
	get_mlx(scene.w.mlx);
	parse_rt_file(&scene, argv[1]);
	init_scene(&scene);
	signal(SIGUSR1, vo);
	init_threads(&scene, 10);
	mlx_hook(scene.w.win, 2, 0, keydown, scene.inputs);
	mlx_hook(scene.w.win, 3, 0, keyup, scene.inputs);
	mlx_loop_hook(scene.w.mlx, simple, &scene);
	mlx_loop(scene.w.mlx);
}
