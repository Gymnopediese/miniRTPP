/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 17:58:30 by albaud            #+#    #+#             */
/*   Updated: 2023/05/17 13:38:43 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#define ADD 1
#define ADDCAM 0.1

// intmove_z(t_scene *scene, int step)
// {
	
// }

int	inputs2(t_scene *scene)
{
	int	f;

	f = 0;
	if (scene->inputs[KEYCODE_K] && ++f)
	{
		scene->inputs[KEYCODE_K] = 0;
		scene->camera_mode = (scene->camera_mode + 1) % 2;
	}
	if (scene->inputs[KEYCODE_UP_ARROW] && ++f)
		scene->motion.z += ADD;
	if (scene->inputs[KEYCODE_DOWN_ARROW] && ++f)
		scene->motion.z -= ADD;
	if (scene->inputs[KEYCODE_O] && scene->resolution > 1 && ++f)
		scene->resolution -= 1;
	if (scene->inputs[KEYCODE_I] && scene->resolution < 20 && ++f)
		scene->resolution += 1;
	return (f);
}

int	inputs(t_scene *scene)
{
	int	f;

	f = 0;
	if (scene->inputs[KEYCODE_A] && ++f)
		scene->motion.x -= ADD;
	if (scene->inputs[KEYCODE_S] && ++f)
		scene->motion.y -= ADD;
	if (scene->inputs[KEYCODE_D] && ++f)
		scene->motion.x += ADD;
	if (scene->inputs[KEYCODE_W] && ++f)
		scene->motion.y += ADD;
	if (scene->inputs[KEYCODE_LEFT_ARROW] && ++f)
		scene->camera->orientation.y += ADDCAM;
	if (scene->inputs[KEYCODE_SPACE] && ++f)
		scene->camera->orientation.x -= ADDCAM;
	if (scene->inputs[KEYCODE_RIGHT_ARROW] && ++f)
		scene->camera->orientation.y -= ADDCAM;
	if (scene->inputs[KEYCODE_C] && ++f)
		scene->camera->orientation.x += ADDCAM;
	return (f + inputs2(scene));
}

int	keyup(int key, char *keys)
{
	keys[key] = 0;
	return (0);
}

int	keydown(int key, char *keys)
{
	if (key == 53)
		exit(0);
	keys[key] = 1;
	return (0);
}
