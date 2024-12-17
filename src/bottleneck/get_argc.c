/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_argc.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/12 22:19:40 by mmosk         #+#    #+#                 */
/*   Updated: 2024/08/12 22:21:49 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "bottleneck.h"

int	get_argc(char **argv)
{
	int	out;

	out = 0;
	while (argv[out] != NULL)
		out++;
	return (out);
}
