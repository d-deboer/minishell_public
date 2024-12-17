/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sentence.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/27 14:28:09 by mmosk         #+#    #+#                 */
/*   Updated: 2024/08/16 16:58:15 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	free_sentence(t_lex **sentence)
{
	if (*sentence == NULL)
		return ;
	free_sentence(&(*sentence)->next);
	free_lex(*sentence);
	*sentence = NULL;
}

void	sentence_append_front(t_lex **sentence, t_lex *item)
{
	item->next = *sentence;
	*sentence = item;
}

void	sentence_append_back(t_lex **sentence, t_lex *item)
{
	if (*sentence == NULL)
		*sentence = item;
	else
		sentence_append_back(&(*sentence)->next, item);
}
