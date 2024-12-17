/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   did_step.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/03 18:12:12 by mmosk         #+#    #+#                 */
/*   Updated: 2024/08/08 17:59:02 by dode-boe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "bottleneck.h"

//Love this.

bool	did_step(void *ptr)
{
	static void	*last = NULL;
	bool		out;

	out = false;
	if (ptr != last)
		out = true;
	last = ptr;
	return (out);
}
