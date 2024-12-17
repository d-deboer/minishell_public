/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_sentence.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/03 16:09:08 by mmosk         #+#    #+#                 */
/*   Updated: 2024/10/09 15:19:41 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//Move this back to parsing folder.

static const char	*g_token_strings[MAX_TOKEN]
	= {
	"WORD",
	"INPUT",
	"DOUBLE_INPUT",
	"OUTPUT",
	"DOUBLE_OUTPUT",
	"PIPE",
	"LEFT_BRACE",
	"RIGHT_BRACE",
	"AND",
	"OR",
	"VARIABLE",
	"WILDCARD"
};

int	print_sentence(t_lex *sentence)
{
	t_lex	*current;

	current = sentence;
	while (current != NULL)
	{
		if (current->token != WORD)
		{
			if (printf("%s-\n", g_token_strings[current->token]) == -1)
				return (1);
		}
		else if (printf("%s-\n", current->content) == -1)
			return (1);
		if (current->is_joined)
			if (printf("+") == -1)
				return (1);
		current = current->next;
	}
	return (0);
}
