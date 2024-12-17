/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   star.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 15:02:14 by mmosk         #+#    #+#                 */
/*   Updated: 2024/07/10 22:09:23 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	tid_star(t_lex **token_start)
{
	(*token_start)->token = WILDCARD;
}
