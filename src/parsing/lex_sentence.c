/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lex_sentence.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/02 21:02:11 by mmosk         #+#    #+#                 */
/*   Updated: 2024/10/09 15:18:30 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static const t_quotation_handler	g_quotation_table[4]
	= {
	&no_quotation,
	&single_quotation,
	&double_quotation,
	&expanded_quotation
};

//Returns true if whitespace is found.
static bool	clear_whitespace(t_quotation *quotation, char **input)
{
	bool	out;

	did_step((void *) NULL);
	out = false;
	while (did_step((void *)*input))
	{
		while (ft_isspace(**input) && *quotation == NONE)
		{
			(*input)++;
			out = true;
		}
		*quotation = update_quotation(*quotation, input);
	}
	return (out);
}

//Can leave lex_start pointing to a null character.
t_lex	*read_lex(char **input, t_quotation *quotation)
{
	size_t	len;
	bool	is_joined;
	t_lex	*lex;
	char	*lex_start;

	lex_start = *input;
	len = g_quotation_table[*quotation](*input);
	*input += len;
	is_joined = true;
	if (clear_whitespace(quotation, input)
		|| (is_word_end(**input) && *quotation == NONE))
		is_joined = false;
	lex = make_lex(lex_start, len, is_joined, *quotation);
	return (lex);
}

int	lex_sentence(t_lex **output, char *input)
{
	t_quotation	quotation;
	t_lex		*current;

	quotation = NONE;
	clear_whitespace(&quotation, &input);
	while (*input != '\0')
	{
		current = read_lex(&input, &quotation);
		if (current == NULL)
			return (FATAL_ERROR);
		sentence_append_back(output, current);
	}
	if (quotation != NONE)
		return (printf("Lex error!\n"));
	return (0);
}
//Lexes either command line input or variables?
//Best make a similar function for variables.
