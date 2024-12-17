/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   justify_string.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/30 13:51:34 by mmosk         #+#    #+#                 */
/*   Updated: 2024/01/15 13:12:22 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "ft_printf_flags.h"

void	justify_str(char *dst, void *in, t_decode *f, t_flags flags)
{
	dst[flags.width] = '\0';
	dst[flags.width + 1] = '\0';
	if (flags.flags & LEFT_JUST)
	{
		(*f)(dst, in, flags.prsc);
		ft_memset(dst + flags.prsc, ' ', flags.width - flags.prsc);
	}
	else
	{
		(*f)(dst + (flags.width - flags.prsc), in, flags.prsc);
		ft_memset(dst, ' ', flags.width - flags.prsc);
	}
}
