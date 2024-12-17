/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   word.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 22:10:40 by mmosk         #+#    #+#                 */
/*   Updated: 2024/10/09 15:21:37 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	tiq_word(t_lex *token)
{
	t_token	next;

	if (find_next_unjoined(token) == NULL)
		return (0);
	next = find_next_unjoined(token)->token;
	if (is_redirection(next) || next == CLOSE_BRACE
		|| next == PIPE || next == AND || next == OR
		|| is_word(next))
		return (0);
	return (1);
}
