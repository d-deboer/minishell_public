/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   factorial.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/19 12:30:48 by mmosk         #+#    #+#                 */
/*   Updated: 2024/03/19 12:32:59 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

unsigned long	factorial(unsigned long in)
{
	unsigned long	out;

	out = 1;
	while (in > 0)
	{
		out *= in;
		in--;
	}
	return (out);
}
