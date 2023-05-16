/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 17:58:30 by albaud            #+#    #+#             */
/*   Updated: 2023/05/16 14:54:07 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#define ADD 0.5

int	inputs2(t_scene *scene)
{
	int	f;

	f = 0;
	// if (scene->inputs[KEYCODE_H] && ++f)
	// 	scene->lights->data->pos.x += ADD;
	// if (scene->inputs[KEYCODE_T] && ++f)
	// 	scene->lights->data->pos.y -= ADD;
	// if (scene->inputs[KEYCODE_4] && ++f)
	// 	scene->lights->data->pos.z += ADD;
	// if (scene->inputs[KEYCODE_5] && ++f)
	// 	scene->lights->data->pos.z -= ADD;
	if (scene->inputs[KEYCODE_K] && ++f)
		scene->camera_mode = (scene->camera_mode + 1) % 2;
	if (scene->inputs[KEYCODE_UP_ARROW] && ++f)
		scene->camera->pos.z += ADD;
	if (scene->inputs[KEYCODE_DOWN_ARROW] && ++f)
		scene->camera->pos.z -= ADD;
	return (f);
}

int	inputs(t_scene *scene)
{
	int	f;

	f = 0;
	if (scene->inputs[KEYCODE_A] && ++f)
		scene->camera->pos.x -= ADD;
	if (scene->inputs[KEYCODE_S] && ++f)
		scene->camera->pos.y += ADD;
	if (scene->inputs[KEYCODE_D] && ++f)
		scene->camera->pos.x += ADD;
	if (scene->inputs[KEYCODE_W] && ++f)
		scene->camera->pos.y -= ADD;
	if (scene->inputs[KEYCODE_F] && ++f)
		((t_light*)scene->lights->data)->pos.x -= ADD;
	// if (scene->inputs[KEYCODE_G] && ++f)
	// 	scene->lights-->pos.y += ADD;
	return (f + inputs2(scene));
}

int	keyup(int key, char *keys)
{
	keys[key] = 0;
	return (0);
}

int	keydown(int key, char *keys)
{
	keys[key] = 1;
	return (0);
}
