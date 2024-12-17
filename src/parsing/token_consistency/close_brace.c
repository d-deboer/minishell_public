/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   close_brace.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 22:10:40 by mmosk         #+#    #+#                 */
/*   Updated: 2024/08/06 13:15:20 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	tiq_close_brace(t_lex *token)
{
	t_token	next;

	if (find_next_unjoined(token) == NULL)
		return (0);
	next = find_next_unjoined(token)->token;
	if (next == CLOSE_BRACE || next == AND || next == OR)
		return (0);
	return (1);
}
