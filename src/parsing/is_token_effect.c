/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_token_effect.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/02 20:23:15 by mmosk         #+#    #+#                 */
/*   Updated: 2024/08/06 13:24:55 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	is_token_split(t_token token)
{
	if (token != WORD && token != VARIABLE
		&& token != WILDCARD)
		return (true);
	return (false);
}

bool	is_pipeline_end(t_token token)
{
	if (is_logic_symbol(token) || token == CLOSE_BRACE)
		return (true);
	return (false);
}

bool	is_command_end(t_token token)
{
	if (is_pipeline_end(token) || token == PIPE)
		return (true);
	return (false);
}
