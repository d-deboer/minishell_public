/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   reduce_sentence.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/16 16:57:19 by mmosk         #+#    #+#                 */
/*   Updated: 2024/08/28 21:39:17 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//returns true if the lex beheaded was joined to the next.
bool	behead_sentence(t_lex **sentence)
{
	t_lex	*next;
	bool	out;

	next = (*sentence)->next;
	out = (*sentence)->is_joined;
	free_lex(*sentence);
	*sentence = next;
	return (out);
}

void	gut_word(t_lex **word)
{
	while (*word != NULL && behead_sentence(word))
		;
}

static inline int	scroll_brace_level(t_lex **current, int brace_level)
{
	while (*current != NULL && is_brace((*current)->token))
	{
		if ((*current)->token == OPEN_BRACE)
			brace_level++;
		if ((*current)->token == CLOSE_BRACE)
			brace_level--;
		behead_sentence(current);
	}
	return (brace_level);
}

void	devour_command(t_lex **sentence)
{
	int		brace_level;

	brace_level = 0;
	while (*sentence != NULL
		&& (is_logic_symbol((*sentence)->token) == false || brace_level != 0))
	{
		did_step((void *)*sentence);
		brace_level = scroll_brace_level(sentence, brace_level);
		if (did_step((void *)*sentence) == false)
			behead_sentence(sentence);
	}
}
