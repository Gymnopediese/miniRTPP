/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:45:50 by albaud            #+#    #+#             */
/*   Updated: 2023/05/17 08:34:36 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ft_strcmp_word(char *line, char *cmp)
{
	int	i;

	while (*line && *line == ' ')
		*line += 1;
	i = 0;
	while (line[i] == cmp[i] && cmp[i] && line[i] && line[i] != ' ')
		i++;
	return (line[i] - cmp[i]);
}

int	valid_file(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len > 3 && ft_strcmp(&filename[len - 3], ".rt") == 0)
		return (0);
	if (len > 4 && ft_strcmp(&filename[len - 4], ".rta") == 0)
		return (1);
	error("wrong file type");
	return (0);
}
