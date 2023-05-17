/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_randint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 15:22:42 by albaud            #+#    #+#             */
/*   Updated: 2023/05/17 13:44:31 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources.h"

int	ft_randint(int min, int max)
{
	time_t		t;
	static int	innit = 1;

	if (innit)
	{
		innit = 0;
		srand((unsigned) time(&t));
	}
	return (rand() % (max - min) + min);
}
