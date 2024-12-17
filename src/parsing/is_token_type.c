/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_token_type.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/02 20:23:15 by mmosk         #+#    #+#                 */
/*   Updated: 2024/08/06 12:46:01 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	is_redirection(t_token token)
{
	if (token == INPUT || token == DOUBLE_INPUT
		|| token == OUTPUT || token == DOUBLE_OUTPUT)
		return (true);
	return (false);
}

bool	is_logic_symbol(t_token token)
{
	if (token == AND || token == OR)
		return (true);
	return (false);
}

bool	is_brace(t_token token)
{
	if (token == OPEN_BRACE || token == CLOSE_BRACE)
		return (true);
	return (false);
}

bool	is_word(t_token token)
{
	if (token == WORD || token == VARIABLE || token == WILDCARD)
		return (true);
	return (false);
}
