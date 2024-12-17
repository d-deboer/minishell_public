/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe_line.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 15:02:14 by mmosk         #+#    #+#                 */
/*   Updated: 2024/07/10 22:09:23 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	set_pipe(t_lex **token_start)
{
	(*token_start)->token = PIPE;
	(*token_start)->is_joined = false;
}

void	tid_pipe_line(t_lex **token_start)
{
	t_lex	*token_end;

	if ((*token_start)->is_joined == false)
		return (set_pipe(token_start));
	token_end = (*token_start)->next;
	if (token_end->quotation != NONE)
		return (set_pipe(token_start));
	if (token_end->content[0] != '|')
		return (set_pipe(token_start));
	behead_sentence(token_start);
	(*token_start)->token = OR;
	(*token_start)->is_joined = false;
}
