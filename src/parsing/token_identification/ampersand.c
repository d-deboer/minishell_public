/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ampersand.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 15:02:14 by mmosk         #+#    #+#                 */
/*   Updated: 2024/07/10 22:09:23 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	tid_ampersand(t_lex **token_start)
{
	t_lex	*token_end;

	if ((*token_start)->is_joined == false)
		return ;
	token_end = (*token_start)->next;
	if (token_end->quotation != NONE)
		return ;
	if (token_end->content[0] != '&')
		return ;
	behead_sentence(token_start);
	(*token_start)->token = AND;
	(*token_start)->is_joined = false;
}
