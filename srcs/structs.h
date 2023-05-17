/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bphilago <bphilago@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 12:42:18 by albaud            #+#    #+#             */
/*   Updated: 2023/05/17 10:48:57 by bphilago         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "../libs/vector3d/t_v3.h"
# include "../libs/koflibc/struct.h"
# include <pthread.h>

# define SHAPE_START 3

typedef struct s_funcs
{
	void	(*function)();
	void	(*normal)();
	int		(*condition)();
	t_v3	(*uv)();
}	t_funcs;

enum
{
	NORMAL,
	DAMIER,
	TEXTURE,
	BUMPMAP,
};

typedef struct s_eqt2
{
	double	a;
	double	b;
	double	c;
	double	delta;
	double	x1;
	double	x2;
}	t_eqt2;

enum e_id
{
	AMBIANCE,
	CAMERA,
	LUMIERE,
	SPHERE,
	PLAN,
	CYLINDRE,
	HYPERBOILD,
	CONE,
	HYPERBOILD2,
	PARABOLOID,
	PARABOLOID2,
	TORUS,
	CUBE,
	CAPSULE,
	OBJECT
};

typedef struct s_ray
{
	t_v3	origin;
	t_v3	direction;
}	t_ray;

typedef struct s_light
{
	double	ratio;
	t_v3	pos;
	t_v3	color;
}	t_light;

typedef struct s_ambiance
{
	double	ratio;
	t_v3	color;
}	t_ambiance;

typedef struct s_camera
{
	double	fov;
	t_v3	orientation;
	t_v3	pos;
}	t_camera;

typedef struct s_triangle
{
	t_v3	a;
	t_v3	b;
	t_v3	c;
	t_v3	n;
	t_v3	*t;
}	t_triangle;

typedef struct s_obj_file
{
	t_v3		*vertices;
	t_v3		*normales;
	t_v3		*vt;
	t_triangle	*triangle;
	int			triangle_length;

	int			vertices_length;
	int			normales_length;
	int			vt_length;
}	t_obj_file;

typedef struct s_obj
{
	enum e_id	id;
	t_v3		pos;
	t_v3		orientation;
	t_v3		scale;
	t_v3		color;
	t_v3		rotation;
	t_v3		scale_anim;
	int			scale_period;
	int			scale_index;
	int			mode;
	int			bmap;
	int			alpha;
	t_v3		color2;
	t_v3		damier;
	t_canvas	texture;
	t_canvas	bumpmap;
	t_obj_file	*obj;
	t_funcs		*funcs;
	double		transform[4][4];
	double		inverse_transform[4][4];
	double		normalizer[4][4];
}	t_obj;

typedef struct s_hit
{
	t_ray		ray;
	t_v3		normal;
	t_v3		reflect;
	t_v3		color;
	const t_obj	*obj;
}	t_hit;

typedef struct s_scene	t_scene;

typedef struct s_process
{
	pthread_t	thread;
	t_v3		start;
	int			iteration;
	t_scene		*scene;
}	t_process;

// int		(*function)();
// void	(*data)();
// int		(*condition)();
typedef struct s_scene
{
	t_window		w;
	t_ambiance		*ambiance;
	t_camera		*camera;
	t_list			*lights;
	t_list			*objects;
	int				input_mode;
	int				animation;
	int				camera_mode;
	int				(*hook)();
	t_funcs			obj_funcs[12];
	char			inputs[128];
	t_process		*processes;
	int				process_count;
	int				process_amount;
	int				resolution;
	pthread_mutex_t	lock;
}	t_scene;

#endif
