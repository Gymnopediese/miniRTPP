/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:37:18 by albaud            #+#    #+#             */
/*   Updated: 2023/05/11 11:32:16 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

//-d damier
//-t <texture> texture
//-r <reflexion> reflexion
//-s <x,y,z> scale

void	bonus_parser(char	**argv, t_obj *obj, int start)
{
	while (argv[start])
	{
		if (ft_strcmp(argv[start], "-s") == 0)
		{
			start++;
			obj->scale = ft_atovedo(argv[start], -20, 20);
		}
		else
		{
			error("invalid bonus option");
		}
		start++;
	}
}
