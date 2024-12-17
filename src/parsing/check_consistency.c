/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_consistency.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 21:36:52 by mmosk         #+#    #+#                 */
/*   Updated: 2024/10/09 15:16:56 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static const char				*g_token_strings[MAX_TOKEN]
	= {
	"WORD",
	"INPUT",
	"DOUBLE_INPUT",
	"OUTPUT",
	"DOUBLE_OUTPUT",
	"PIPE",
	"OPEN_BRACE",
	"CLOSE_BRACE",
	"AND",
	"OR",
	"VARIABLE",
	"WILDCARD"
};

static const char				*g_token_msg[MAX_TOKEN]
	= {
	"Next token is opening brace.",
	"Next token is not a word.",
	"Next token is not a word.",
	"Next token is not a word.",
	"Next token is not a word.",
	"Next token is not a word or redirection.",
	"Next token is not opening brace, redirection, or word.",
	"Next token is not end of line, closing brace, or logic symbol.",
	"Next token is not a word, redirection, or opening brace.",
	"Next token is not a word, redirection, or opening brace.",
	"Next token is opening brace.",
	"Next token is opening brace."
};

static const t_token_inquisitor	g_inquisition_table[MAX_TOKEN]
	= {
	&tiq_word,
	&tiq_redirection,
	&tiq_redirection,
	&tiq_redirection,
	&tiq_redirection,
	&tiq_pipe,
	&tiq_open_brace,
	&tiq_close_brace,
	&tiq_logic_symbol,
	&tiq_logic_symbol,
	&tiq_word,
	&tiq_word
};

static inline void	update_brace_level(int *brace_level, t_token token)
{
	if (token == OPEN_BRACE)
		(*brace_level)++;
	if (token == CLOSE_BRACE)
		(*brace_level)--;
}

//Not actually necessary.
// static inline int	check_argc(t_token token)
// {
// 	static int	argc_count = 0;

// 	if (token == WORD)
// 		argc_count++;
// 	if (is_redirection(token))
// 		argc_count--;
// 	if (token == PIPE || token == AND || token == OR)
// 	{
// 		if (argc_count <= 0)
// 			return (1);
// 		argc_count = 0;
// 	}
// 	return (0);
// }

// if (check_argc(token))
// 	return (printf("Friend, you've lost the forest for the trees.\n"));
//In loop, if we want it to be.

int	check_consistency(t_lex *sentence)
{
	t_lex	*current;
	t_token	token;
	int		brace_level;

	if (sentence == NULL)
		return (0);
	token = sentence->token;
	if (is_logic_symbol(token) || token == PIPE)
		return (printf("First token is either pipe or logic symbol.\n"));
	brace_level = 0;
	current = sentence;
	while (current != NULL)
	{
		token = current->token;
		if (g_inquisition_table[token](current))
			return (printf("At token %s: %s\n",
					g_token_strings[token], g_token_msg[token]));
		update_brace_level(&brace_level, token);
		if (brace_level < 0)
			return (printf("Too many closing braces, punk.\n"));
		current = current->next;
	}
	if (brace_level != 0)
		return (printf("Too few closing braces, lass.\n"));
	return (0);
}
