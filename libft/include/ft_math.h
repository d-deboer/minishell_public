/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_math.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/19 12:29:42 by mmosk         #+#    #+#                 */
/*   Updated: 2024/05/22 11:32:01 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATH_H
# define FT_MATH_H

# include "libft.h"

unsigned long	factorial(unsigned long in);
unsigned long	ft_pow(unsigned long base, unsigned long exponent);
unsigned long	bit_not(unsigned long in);

unsigned int	wrap(unsigned int in, unsigned int size);
unsigned int	dif(unsigned int a, unsigned int b);

#endif
