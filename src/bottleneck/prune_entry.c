/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prune_entry.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/28 13:44:14 by mmosk         #+#    #+#                 */
/*   Updated: 2024/10/09 14:07:43 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "bottleneck.h"

void	prune_entry(void **ptr_arr, unsigned int entry)
{
	unsigned int	i;

	i = 0;
	while (ptr_arr[i] != NULL && i < entry)
		i++;
	if (i != entry)
		return ;
	free(ptr_arr[entry]);
	while (ptr_arr[i] != NULL)
	{
		ptr_arr[i] = ptr_arr[i + 1];
		i++;
	}
}
