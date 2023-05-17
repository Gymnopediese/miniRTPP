/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 12:42:18 by albaud            #+#    #+#             */
/*   Updated: 2023/05/17 13:32:00 by bphilago         ###   ########.fr       */
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

int			hit_any_obj(const t_scene *scene, t_ray *r, double d);
int			inputs(t_scene *scene);
void		*iterate_thread(void *p);
void		init_threads(t_scene *scene, int amount);
int			ray_trace_basic(t_scene *scene, t_ray *r);
int			ray_trace_phong(t_scene *scene, t_ray *r);
void		print_scene(t_scene *i);
void		parse_rt_file(t_scene *scene, char *file_name);
void		error(char *message);
void		input(int key, t_scene *scene);
// void		iterate_objects(t_scene *scene);
t_v3		v_relative_pos(double height, double width, double x, double y);
void		brightness(t_v3 *final_color, const t_hit *hit, const t_scene *scene);

void		print_vector(t_v3 a, char *name);
// int			damier(t_obj *obj, t_v3 *hit, t_scene *scene);
// int			uvmapping(t_obj *obj, t_v3 *hit, t_scene *scene);
// Dispersion
t_v3		disperse(t_hit *hit, t_obj *obj);
int			coloring2(t_obj	*obj, t_v3 *hit, t_scene *scene);
// test
void		print_buffer(t_scene *scene, t_v3 **buffer);
void		progressive_iteration(t_scene *scene, t_v3 **buffer, int steps);

int			keyup(int key, char *keys);
int			keydown(int key, char *keys);

int			hit_obj(t_scene *scene, t_ray *r, t_hit *hit);

void		apply_matrices(t_list *o, t_scene *scene);

long int	ft_get_color(const t_canvas *cvs, int x, int y);

void		*get_mlx(void *p);
t_obj_file	*obj_parser(char *filename);
void		init_intersects(t_scene *scene);
void		init_scene(t_scene *scene);
int			simple(t_scene *scene);
void		ft_pitch(t_v3 *vector, float angle);
void		ft_yaw(t_v3 *vector, float angle);
#endif
