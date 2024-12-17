/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/29 18:13:36 by mmosk         #+#    #+#                 */
/*   Updated: 2024/08/08 14:33:54 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	parse(char *line, char ***env)
{
	t_lex	*sentence;
	int		out;

	sentence = NULL;
	out = lex_sentence(&sentence, line);
	if (out != 0)
		return (free_sentence(&sentence), out);
	mark_tokens(&sentence);
	split_tokens(sentence);
	out = check_consistency(sentence);
	if (out != 0)
		return (free_sentence(&sentence), out);
	out = process(&sentence, env);
	free_sentence(&sentence);
	if (out != 0)
		return (out);
	return (0);
}
