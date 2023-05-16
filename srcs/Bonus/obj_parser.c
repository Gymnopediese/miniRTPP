/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 15:18:13 by albaud            #+#    #+#             */
/*   Updated: 2023/05/16 01:14:09 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

t_v3	ligne_to_vec(char *line)
{
	t_v3	res;
	double	t[10];
	int		i;
	int		n;

	i = 0;
	n = -1;
	while (line[i])
	{
		while (!ft_strcontain("1234567890.-", line[i]))
			++i;
		t[++n] = ft_atodo(&line[i]);
		while (ft_strcontain("1234567890.-", line[i]))
			++i;
	}
	res.x = t[0];
	res.y = t[1];
	res.z = t[2];
	return (res);
}

void	count(char **lines, t_obj_file *res)
{
	int	i;

	i = -1;
	while (lines[++i])
	{
		if (ft_strcmpl(lines[i], "vt") == 0)
			res->vt_length++;
		else if (ft_strcmpl(lines[i], "vn") == 0)
			res->normales_length++;
		else if (ft_strcmpl(lines[i], "v") == 0)
			res->vertices_length++;
		else if (ft_strcmpl(lines[i], "f") == 0)
			res->triangle_length++;
	}
}

void	fill_obj(char **lines, t_obj_file *res)
{
	int		i[5];
	t_v3	temp[3];
	char	**split;

	ft_bzero(i, 20);
	while (lines[i[0]])
	{
		if (ft_strcmpl(lines[i[0]], "vt") == 0)
			res->vt[i[1]++] = ligne_to_vec(lines[i[0]++]);
		else if (ft_strcmpl(lines[i[0]], "vn") == 0)
			res->normales[i[2]++] = ligne_to_vec(lines[i[0]++]);
		else if (ft_strcmpl(lines[i[0]], "v") == 0)
			res->vertices[i[3]] = ligne_to_vec(lines[i[0]++]);
		else if (ft_strcmpl(lines[i[0]], "f") == 0)
		{
			split = ft_split(lines[i[0]++], ' ');
			temp[0] = ligne_to_vec(split[1]);
			temp[1] = ligne_to_vec(split[2]);
			temp[2] = ligne_to_vec(split[3]);
			ft_free_pp((void **)split);
			res->triangle[i[4]++] = (t_triangle){\
res->vertices[(int)temp[0].x - 1], res->vertices[(int)temp[1].x - 1], \
res->vertices[(int)temp[2].x - 1], res->normales[(int)temp[0].z - 1], 0,};
		}
	}
}

t_obj_file	*obj_parser(char *filename)
{
	char		**lines;
	t_obj_file	*res;

	res = allok(1, sizeof(t_obj_file), 1);
	lines = ft_read_lignes(filename);
	if (lines == 0)
		error("couldn't read file");
	count(lines, res);
	res->vertices = allok(res->vertices_length, sizeof(t_v3), 1);
	res->normales = allok(res->normales_length, sizeof(t_v3), 1);
	res->vt = allok(res->vt_length, sizeof(t_v3), 1);
	res->triangle = allok(res->triangle_length, sizeof(t_v3), 1);
	fill_obj(lines, res);
	ft_free_pp((void **)lines);
	return (res);
}
