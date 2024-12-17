/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   condense_command.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/11 21:48:15 by mmosk         #+#    #+#                 */
/*   Updated: 2024/10/09 15:14:31 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//Takes the first word of the sentence and condenses it into a single lex.
//!!Removes token and quotation information!!!
t_lex	*condense_word(t_lex **sentence)
{
	t_lex	*out;

	out = malloc(sizeof(t_lex));
	if (out == NULL)
		return (NULL);
	out->content = extract_word(sentence);
	if (out->content == NULL)
		return (free(out), NULL);
	out->token = WORD;
	out->is_joined = false;
	out->quotation = NONE;
	out->next = *sentence;
	*sentence = out;
	return (out);
}

//Can use this only after expanding variables and wildcards.
int	condense_command(t_lex **sentence)
{
	t_lex	**current;

	current = sentence;
	while (*current != NULL && is_pipeline_end((*current)->token) == false)
	{
		if ((*current)->is_joined == true)
			if (condense_word(current) == NULL)
				return (1);
		current = &(*current)->next;
	}
	return (0);
}
