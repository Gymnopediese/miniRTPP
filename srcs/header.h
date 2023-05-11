/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 12:42:18 by albaud            #+#    #+#             */
/*   Updated: 2023/05/11 11:57:01 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# define STEPS 3

# include "../libs/koflibc/sources.h"
# include "structs.h"
# include "Parser/parser.h"
# include "Background/background.h"
# include "Shapes/shapes.h"
# include <pthread.h>
# include <signal.h>

int			hit_any_obj(const t_scene *scene, t_ray *r);
int			inputs(t_scene *scene);
void		*iterate_thread(void *p);
void		init_threads(t_scene *scene, int amount);
int			ray_trace_basic(t_scene *scene, t_ray *r);
void		print_scene(t_scene *i);
void		parse_rt_file(t_scene *scene, char *file_name);
void		error(char *message);
void		input(int key, t_scene *scene);
// void		iterate_objects(t_scene *scene);
t_v3		v_relative_pos(double height, double width, double x, double y);
void		ray_trace(t_scene *scene, t_ray *r, t_v3 *l_color,
				t_v3 *s_color);
void		brightness(t_v3 *tmp_color, const t_v3 *origine_pos,
				const t_hit *hit, const t_scene *scene);

void		print_vector(t_v3 a, char *name);
int			damier(t_obj *obj, t_v3 *hit, t_scene *scene);
int			uvmapping(t_obj *obj, t_v3 *hit, t_scene *scene);
// Dispersion
t_v3		disperse(t_hit *hit, t_obj *obj);
int			coloring2(t_obj	*obj, t_v3 *hit, t_scene *scene);
// test
void		print_buffer(t_scene *scene, t_v3 **buffer);
void		progressive_iteration(t_scene *scene, t_v3 **buffer, int steps);

int			keyup(int key, char *keys);
int			keydown(int key, char *keys);

int			hit_obj(t_scene *scene, t_ray *r, t_hit *hit);

void		brightness(t_v3 *tmp_color, const t_v3 *origine_pos,
				const t_hit *hit, const t_scene *scene);

void		apply_matrices(t_list *o, t_scene *scene);
#endif
