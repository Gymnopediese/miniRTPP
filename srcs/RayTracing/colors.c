/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:11:47 by albaud            #+#    #+#             */
/*   Updated: 2023/05/17 13:31:26 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"
#define MIN_SCOLOR 0.01

void	compute_reflexion(t_v3 *final_color, const t_light *light,
		const t_scene *scene, const t_hit *hit)
{
	t_v3	reflexion;
	double	tmp_double;
	t_v3	tmp_vector;

	tmp_vector = hit->normal;
	reflexion = v_nmult(&light->pos, -1);
	tmp_double = v_dotp(&reflexion, &tmp_vector);
	v_cnmult(&tmp_vector, tmp_double * 2.0);
	v_crm(&reflexion, &tmp_vector);
	v_cunit(&reflexion);
	tmp_vector = v_rm(&scene->camera->pos, &hit->ray.origin);
	v_cunit(&tmp_vector);
	tmp_double = fabs(pow(v_dotp(&reflexion, &tmp_vector), hit->obj->alpha));
	tmp_vector = v_nmult(&light->color, tmp_double);
	v_cadd(final_color, &tmp_vector);
}

int	compute_light(t_v3 *final_color, const t_hit *hit, const t_light *light)
{
	t_v3	tmp_color;
	t_v3	tmp_vector;
	double	tmp_double;

	tmp_color = hit->color;
	v_cmult(&tmp_color, &light->color);
	tmp_vector = v_rm(&light->pos, &hit->ray.origin);
	v_cunit(&tmp_vector);
	tmp_double = v_dotp(&tmp_vector, &hit->normal);
	if (tmp_double <= 0)
		return (0);
	v_cnmult(&tmp_color, tmp_double);
	v_cadd(final_color, &tmp_color);
	return (1);
}

void	brightness(t_v3 *final_color, const t_hit *hit, const t_scene *scene)
{
	t_list	*current_link;
	t_light	*current_light;
	t_v3	tmp_v3;
	t_ray	r;

	current_link = scene->lights;
	while (current_link)
	{
		current_light = current_link->data;
		r.direction = v_rm(&current_light->pos, &hit->ray.origin);
		r.origin = hit->ray.origin;
		tmp_v3 = v_nmult(&hit->normal, 0.01);
		v_cadd(&r.origin, &tmp_v3);
		if (current_light->ratio != 0
			&& !hit_any_obj(scene, &r,
				v_dist(&current_light->pos, &hit->ray.origin))
			&& compute_light(final_color, hit, current_light))
		{
			if (hit->obj->alpha >= 1)
				compute_reflexion(final_color, current_light, scene, hit);
		}
		current_link = current_link->next;
	}
}

long int	ft_get_color(const t_canvas *cvs, int x, int y)
{
	unsigned char		*pix;
	unsigned long int	col;

	pix = (unsigned char *)ft_get_pixel(cvs, x, y);
	col = 0;
	col = (col << 8) + (((int)pix[3]));
	col = (col << 8) + (((int)pix[2]));
	col = (col << 8) + (((int)pix[1]));
	col = (col << 8) + (((int)pix[0]));
	return (col);
}
