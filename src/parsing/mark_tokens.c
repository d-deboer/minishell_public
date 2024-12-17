/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mark_tokens.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/04 22:31:25 by mmosk         #+#    #+#                 */
/*   Updated: 2024/10/09 15:19:19 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static const t_token_identifier	g_token_table[256]
	= {
['&'] = &tid_ampersand,
['$'] = &tid_dollarsign,
['<'] = &tid_left_arrow,
['('] = &tid_left_brace,
['|'] = &tid_pipe_line,
['>'] = &tid_right_arrow,
[')'] = &tid_right_brace,
['*'] = &tid_star
};

//Watch the pointers closely, here.
void	mark_tokens(t_lex **sentence)
{
	t_lex	**current;

	current = sentence;
	while (*current != NULL)
	{
		if ((*current)->quotation == NONE
			&& is_special_token((*current)->content[0]))
			g_token_table[(unsigned char)(*current)->content[0]](current);
		if ((*current)->quotation == DOUBLE
			&& (*current)->content[0] == '$')
			tid_dollarsign(current);
		current = &(*current)->next;
	}
}
