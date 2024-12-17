/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   bit_not.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/19 13:12:00 by mmosk         #+#    #+#                 */
/*   Updated: 2024/03/20 11:43:18 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include "ft_printf.h"

unsigned long	bit_not(unsigned long in)
{
	return (in ^ 0xFFFFFFFFFFFFFFFF);
}
