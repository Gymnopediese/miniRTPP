/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:37:18 by albaud            #+#    #+#             */
/*   Updated: 2023/05/17 12:58:52 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

//-d damier
//-t <texture> texture
//-r <reflexion> reflexion
//-s <x,y,z> scale

int	more_options(char	**argv, t_obj *obj, int *start)
{
	if (ft_strcmp(argv[*start], "-d") == 0 && argv[++(*start)])
	{
		obj->mode = DAMIER;
		obj->color2 = ft_atovedo(argv[*start], 0, 255);
	}
	else if (ft_strcmp(argv[*start], "-b") == 0 && argv[++(*start)])
	{
		obj->bmap = 1;
		obj->bumpmap = ft_init_image(get_mlx(0), argv[*start]);
	}
	else if (ft_strcmp(argv[*start], "-t") == 0 && argv[++(*start)])
	{
		obj->mode = TEXTURE;
		obj->texture = ft_init_image(get_mlx(0), argv[*start]);
	}
	else
		return (0);
	return (1);
}

int	comment(char *str)
{
	int	i;

	i = -1;
	while (str[++i] && str[i] != '#')
		;
	str[i] = 0;
	return (1);
}

void	bonus_parser(char	**argv, t_obj *obj, int start)
{
	while (argv[start])
	{
		if (ft_strcmp(argv[start], "-s") == 0 && argv[++start])
			obj->scale = ft_atovedo(argv[start], 0, 0);
		else if (ft_strcmp(argv[start], "-o") == 0 && argv[++start])
			obj->orientation = ft_atovedo(argv[start], 0, 1);
		else if (ft_strcmp(argv[start], "-p") == 0 && argv[++start])
			obj->pos = ft_atovedo(argv[start], 0, 1);
		else if (ft_strcmp(argv[start], "-r") == 0 && argv[++start])
			obj->rotation = ft_atovedo(argv[start], 0, 1);
		else if (ft_strcmp(argv[start], "-dxy") == 0 && argv[++start])
			obj->damier = ft_atovei(argv[start], 0, 0);
		else if (ft_strcmp(argv[start], "-sa") == 0 && argv[++start])
			obj->scale_anim = ft_atovedo(argv[start], 0, 0);
		else if (ft_strcmp(argv[start], "-period") == 0 && argv[++start])
			obj->scale_period = ft_atodor(argv[start], 0, 0);
		else if (!more_options(argv, obj, &start))
			error("invalid bonus option");
		start++;
	}
}
