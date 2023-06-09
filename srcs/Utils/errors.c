/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 14:28:46 by albaud            #+#    #+#             */
/*   Updated: 2023/05/17 14:01:13 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	error(char *message)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(message, 2);
	ft_garbage_colector(0, 1, 1);
}
