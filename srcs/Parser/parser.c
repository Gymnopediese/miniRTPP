/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:21:18 by albaud            #+#    #+#             */
/*   Updated: 2023/05/17 14:02:26 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

enum e_id	get_id(char *line)
{
	const char	*p[] = {
		"A", "C", "L", "sp", "pl", "cy", "hb", "cn",
		"hb2", "pb", "pb2", "to", "cb", "cp", "obj", 0
	};
	int			i;

	if (!line)
		return (-1);
	i = -1;
	while (p[++i])
		if (ft_strcmp(line, (char *)p[i]) == 0)
			return (i);
	error("invalid object type in .rt file");
	return (0);
}

t_obj	*new_obj(int id)
{
	t_obj	*obj;

	obj = allok(sizeof(*obj), 1, 1);
	obj->scale = (t_v3){1, 1, 1};
	obj->rotation = (t_v3){0, 0, 0};
	obj->damier = (t_v3){10, 10, 0};
	obj->scale_anim = (t_v3){0, 0, 0};
	obj->scale_period = 5;
	obj->id = id;
	return (obj);
}

void	ligne_to_shape(char **argv, t_scene *scene, enum e_id id)
{
	t_obj	*obj;

	obj = new_obj(id);
	if (id == SPHERE)
		init_sphere(argv, obj);
	else if (id == PLAN || id == CUBE)
		init_plan(argv, obj);
	else if (id == CYLINDRE || id == CONE || id == HYPERBOILD
		|| id == HYPERBOILD2 || id == PARABOLOID || id == PARABOLOID2
		|| id == CAPSULE)
		init_cylindre(argv, obj);
	else if (id == TORUS)
		init_torus(argv, obj);
	else if (id == OBJECT)
		init_object(argv, obj);
	v_cndiv(&obj->color, 255.0);
	v_cndiv(&obj->color2, 255.0);
	v_cnmult(&obj->orientation, PI);
	obj->funcs = &scene->obj_funcs[id - 3];
	ft_lstadd_back(&scene->objects, ft_lstnew(obj));
}

void	ligne_to_obj(char *line, t_scene *scene)
{
	enum e_id	id;
	char		**argv;

	argv = ft_split(line, ' ');
	if (argv == 0)
		error("split malloc error");
	id = get_id(argv[0]);
	if (id == AMBIANCE)
		init_ambiance(argv, scene);
	else if (id == LUMIERE)
		init_light(argv, scene);
	else if (id == CAMERA)
		init_camera(argv, scene);
	else if (id > 0)
		ligne_to_shape(argv, scene, id);
	ft_free_pp((void **)argv);
}

void	parse_rt_file(t_scene *scene, char *file_name)
{
	char	**lines;
	int		i;

	scene->animation = valid_file(file_name);
	lines = ft_read_lignes(file_name);
	if (lines == 0)
		error("the file does not exist");
	i = -1;
	scene->ambiance = 0;
	scene->camera = 0;
	scene->lights = 0;
	scene->objects = 0;
	while (lines[++i] && comment(lines[i]))
	{
		if (lines[i][0])
			ligne_to_obj(lines[i], scene);
	}
	if (!scene->camera)
		error("Rt file invalide : no camera");
	if (!scene->ambiance)
		error("Rt file invalide : no ambiant light");
	if (!scene->lights)
		error("Rt file invalide : no light");
}
