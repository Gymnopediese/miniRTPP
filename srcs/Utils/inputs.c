/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 17:58:30 by albaud            #+#    #+#             */
/*   Updated: 2023/05/17 13:14:23 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#define ADD 0.5
#define ADDCAM 0.01

int	inputs2(t_scene *scene)
{
	int	f;

	f = 0;
	if (scene->inputs[KEYCODE_K] && ++f)
	{
		scene->inputs[KEYCODE_K] = 0;
		scene->camera_mode = (scene->camera_mode + 1) % 2;
	}
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
		scene->camera->pos.x -= ADD;
	if (scene->inputs[KEYCODE_S] && ++f)
		scene->camera->pos.y -= ADD;
	if (scene->inputs[KEYCODE_D] && ++f)
		scene->camera->pos.x += ADD;
	if (scene->inputs[KEYCODE_W] && ++f)
		scene->camera->pos.y += ADD;
	if (scene->inputs[KEYCODE_UP_ARROW] && ++f)
		scene->camera->pos.z += ADD;
	if (scene->inputs[KEYCODE_DOWN_ARROW] && ++f)
		scene->camera->pos.z -= ADD;
	if (scene->inputs[KEYCODE_F] && ++f)
		scene->camera->orientaion.x -= ADDCAM;
	if (scene->inputs[KEYCODE_G] && ++f)
		scene->camera->orientaion.y -= ADDCAM;
	if (scene->inputs[KEYCODE_H] && ++f)
		scene->camera->orientaion.x += ADDCAM;
	if (scene->inputs[KEYCODE_T] && ++f)
		scene->camera->orientaion.y += ADDCAM;
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
		ft_garbage_colector(0, 1, 1);
	keys[key] = 1;
	return (0);
}
