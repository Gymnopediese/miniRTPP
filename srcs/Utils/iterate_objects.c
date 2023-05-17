/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterate_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 19:08:13 by albaud            #+#    #+#             */
/*   Updated: 2023/05/17 13:27:56 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	ft_pitch(t_v3 *vector, float angle)
{
	float	temp;

	temp = vector->y * cos(angle) + vector->z * sin(angle);
	vector->z = vector->y * (-sin(angle)) + vector->z * cos(angle);
	vector->y = temp;
}

void	ft_yaw(t_v3 *vector, float angle)
{
	float	temp;

	temp = vector->x * cos(angle) + vector->z * (-sin(angle));
	vector->z = vector->x * sin(angle) + vector->z * cos(angle);
	vector->x = temp;
}

t_v3	v_cam_direction(t_scene *scene, double x, double y)
{
	t_v3	ray;

	ray = (t_v3){
		(x - scene->w.cvs.x / 2) * 2 / scene->w.cvs.x,
		(y - scene->w.cvs.y / 2) * 2 / scene->w.cvs.y,
		1};
	ft_pitch(&ray, scene->camera->orientation.x);
	ft_yaw(&ray, scene->camera->orientation.y);
	return (ray);
}

void	draw_fsquare(t_canvas *cvs, t_vector pos, int size, int color)
{
	int	x;
	int	y;

	x = 0;
	while (x < size)
	{
		y = 0;
		while (y < size)
		{
			if (pos.x + x < cvs->x && pos.y + y < cvs->y)
				ft_put_pixel(cvs, pos.x + x, pos.y + y, color);
			y++;
		}
		x++;
	}
}

void	iterate_objects(t_scene *scene)
{
	int		x;
	int		y;
	t_ray	r;
	int		color;

	y = 0;
	r.origin = scene->camera->pos;
	while (y < scene->w.cvs.y)
	{
		x = 0;
		while (x < scene->w.cvs.x)
		{
			r.origin = scene->camera->pos;
			r.direction = v_cam_direction(scene, x, y);
			if (!scene->camera_mode)
				color = ray_trace_phong(scene, &r);
			else
				color = ray_trace_basic(scene, &r);
			if (-1 != color)
				draw_fsquare(&scene->w.cvs, (t_vector){x,
					scene->w.cvs.y - y, 0, 0}, scene->resolution, color);
			x += scene->resolution;
		}
		y += scene->resolution;
	}
}
