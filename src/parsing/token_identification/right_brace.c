/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   right_brace.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 15:02:14 by mmosk         #+#    #+#                 */
/*   Updated: 2024/07/11 20:01:12 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	tid_right_brace(t_lex **token_start)
{
	(*token_start)->token = CLOSE_BRACE;
	(*token_start)->is_joined = false;
}
