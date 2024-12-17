/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   left_arrow.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 15:02:14 by mmosk         #+#    #+#                 */
/*   Updated: 2024/07/10 22:09:23 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	set_input(t_lex **token_start)
{
	(*token_start)->token = INPUT;
	(*token_start)->is_joined = false;
}

void	tid_left_arrow(t_lex **token_start)
{
	t_lex	*token_end;

	if ((*token_start)->is_joined == false)
		return (set_input(token_start));
	token_end = (*token_start)->next;
	if (token_end->quotation != NONE)
		return (set_input(token_start));
	if (token_end->content[0] != '<')
		return (set_input(token_start));
	behead_sentence(token_start);
	(*token_start)->token = DOUBLE_INPUT;
	(*token_start)->is_joined = false;
}
