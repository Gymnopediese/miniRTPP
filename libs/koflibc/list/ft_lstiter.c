/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albaud <albaud@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 16:55:13 by albaud            #+#    #+#             */
/*   Updated: 2022/10/31 11:35:28 by albaud           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sources.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{	
		f(lst->data);
		lst = lst->next;
	}
}