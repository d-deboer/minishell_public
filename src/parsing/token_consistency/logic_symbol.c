/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   logic_symbol.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 22:10:40 by mmosk         #+#    #+#                 */
/*   Updated: 2024/10/09 15:21:37 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	tiq_logic_symbol(t_lex *token)
{
	t_token	next;

	if (find_next_unjoined(token) == NULL)
		return (1);
	next = find_next_unjoined(token)->token;
	if (is_redirection(next) || next == OPEN_BRACE
		|| is_word(next))
		return (0);
	return (1);
}
