/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   left_brace.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 15:02:14 by mmosk         #+#    #+#                 */
/*   Updated: 2024/07/11 20:00:55 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	tid_left_brace(t_lex **token_start)
{
	(*token_start)->token = OPEN_BRACE;
	(*token_start)->is_joined = false;
}
