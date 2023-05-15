/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 17:58:30 by albaud            #+#    #+#             */
/*   Updated: 2023/05/15 15:26:33 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#define ADD 0.5

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
	if (scene->inputs[KEYCODE_G] && ++f)
		((t_light*)scene->lights->data)->pos.y += ADD;
	if (scene->inputs[KEYCODE_H] && ++f)
		((t_light*)scene->lights->data)->pos.x += ADD;
	if (scene->inputs[KEYCODE_T] && ++f)
		((t_light*)scene->lights->data)->pos.y -= ADD;
	if (scene->inputs[KEYCODE_4] && ++f)
		((t_light*)scene->lights->data)->pos.z += ADD;
	if (scene->inputs[KEYCODE_5] && ++f)
		((t_light*)scene->lights->data)->pos.z -= ADD;
	if (scene->inputs[KEYCODE_UP_ARROW] && ++f)
		scene->camera->pos.z += ADD;
	if (scene->inputs[KEYCODE_DOWN_ARROW] && ++f)
		scene->camera->pos.z -= ADD;
	return (f);
}

void	input_light(int key, t_scene *scene)
{
	if (key == KEYCODE_A)
		((t_light*)scene->lights->data)->pos.x -= ADD;
	if (key == KEYCODE_S)
		((t_light*)scene->lights->data)->pos.y += ADD;
	if (key == KEYCODE_D)
		((t_light*)scene->lights->data)->pos.x += ADD;
	if (key == KEYCODE_W)
		((t_light*)scene->lights->data)->pos.y -= ADD;
	if (key == KEYCODE_UP_ARROW)
		((t_light*)scene->lights->data)->pos.z += ADD;
	if (key == KEYCODE_DOWN_ARROW)
		((t_light*)scene->lights->data)->pos.z -= ADD;
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
