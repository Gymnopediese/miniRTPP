/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterate_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 19:08:13 by albaud            #+#    #+#             */
/*   Updated: 2023/05/17 13:03:13 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_v3	v_cam_direction(t_scene *scene, double x, double y)
{
	return ((t_v3){
		(x - scene->w.cvs.x / 2) * 2 / scene->w.cvs.x
		+ scene->camera->orientaion.x,
		(y - scene->w.cvs.y / 2) * 2 / scene->w.cvs.y
		+ scene->camera->orientaion.y,
		1,
	});
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
			if (scene->camera_mode)
				color = ray_trace_phong(scene, &r);
			else
				color = ray_trace_basic(scene, &r);
			if (-1 != color)
				ft_draw_fsquare(&scene->w.cvs, (t_vector){x,
					scene->w.cvs.y - y, 0, 0}, scene->resolution, color);
			x += scene->resolution;
		}
		y += scene->resolution;
	}
}

// void	progressive_iteration(t_scene *scene, t_v3 **buffer, int steps)
// {
// 	int		x;
// 	int		y;
// 	t_ray	r;
// 	t_v3	s_color;
// 	t_v3	l_color;

// 	y = -1;
// 	r.origin = scene->camera->pos;
// 	while (++y < scene->w.cvs.y)
// 	{
// 		x = -1;
// 		while (++x < scene->w.cvs.x)
// 		{
// 			if (y % steps != 0)
// 				buffer[y][x] = (t_v3){-1.0, -1.0, -1.0};
// 			else if (x % steps != 0)
// 				buffer[y][x] = (t_v3){-1.0, -1.0, -1.0};
// 			else
// 			{
// 				r.origin = scene->camera->pos;
// 				r.direction = v_relative_pos
// 					(scene->w.cvs.x, scene->w.cvs.y, x, y);
// 				s_color = (t_v3){1.0, 1.0, 1.0};
// 				l_color = (t_v3){0.0, 0.0, 0.0};
// 				ray_trace_phong(scene, &r);
// 				buffer[y][x] = l_color;
// 				if (l_color.x + l_color.y + l_color.z != 0)
// Point d'accroche pour les tests. A enlever
// 					continue ;
// 			}
// 		}
// 	}
// }

// double	find_big_value(t_v3 **buffer, int width, int height)
// {
// 	int		x;
// 	int		y;
// 	double	max_value;

// 	(void) width;
// 	y = -1;
// 	max_value = 0.000001;
// 	while (++y < height)
// 	{
// 		x = -1;
// 		while (++x < height)
// 		{
// 			if (buffer[y][x].x > max_value)
// 				max_value = buffer[y][x].x;
// 			if (buffer[y][x].y > max_value)
// 				max_value = buffer[y][x].y;
// 			if (buffer[y][x].z > max_value)
// 				max_value = buffer[y][x].z;
// 		}
// 	}
// 	return (max_value);
// }

// void	normalize_buffer(t_v3 **buffer, int width, int height)
// {
// 	int		x;
// 	int		y;
// 	double	max_value;

// 	y = -1;
// 	max_value = find_big_value(buffer, width, height);
// 	while (++y < height)
// 	{
// 		x = -1;
// 		while (++x < height)
// 		{
// 			if (buffer[y][x].x >= 0)
// 				v_cnmult(buffer[y] + x, 255.0 / max_value);
// 		}
// 	}
// }

// void	print_buffer(t_scene *scene, t_v3 **buffer)
// {
// 	int		x;
// 	int		y;
// 	int		skip_x;
// 	int		skip_y;
// 	int		tmp_x;
// 	int		tmp_y;
// 	int		color;

// 	normalize_buffer(buffer, scene->w.cvs.x, scene->w.cvs.y);
// 	y = 0;
// 	x = 0;
// 	while (y < scene->w.cvs.y)
// 	{
// 		skip_y = 1;
// 		while (y + skip_y < scene->w.cvs.y && buffer[y + skip_y][x].x == -1)
// 			++skip_y;
// 		while (x < scene->w.cvs.x)
// 		{
// 			skip_x = 1;
// 			color = v_tocol(buffer[y] + x);
// 			while (x + skip_x < scene->w.cvs.x && buffer[y][x + skip_x].x == -1)
// 				++skip_x;
// 			x += skip_x;
// 			tmp_y = skip_y;

// 			while (tmp_y > 0)
// 			{
// 				tmp_x = skip_x;
// 				while (tmp_x > 0)
// 				{
// 					ft_put_pixel(&scene->w.cvs, x - tmp_x, y - tmp_y, color);
// 					tmp_x -= 1;
// 				}
// 				tmp_y -= 1;
// 			}
// 		}
// 		x = 0;
// 		y += skip_y;
// 	}
// }
