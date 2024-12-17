/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quotation.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/03 13:59:48 by mmosk         #+#    #+#                 */
/*   Updated: 2024/10/09 15:19:58 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_quotation	update_quotation(t_quotation in, char **delimiter)
{
	if (in == SINGLE && **delimiter == '\'')
		return ((*delimiter)++, NONE);
	if (in == DOUBLE && **delimiter == '"')
		return ((*delimiter)++, NONE);
	if (in == NONE && **delimiter == '\'')
		return ((*delimiter)++, SINGLE);
	if (in == NONE && **delimiter == '"')
		return ((*delimiter)++, DOUBLE);
	return (in);
}

size_t	no_quotation(char *word_start)
{
	size_t	out;

	out = 0;
	while (is_lex_end(word_start[out]) == false)
	{
		out++;
	}
	if (out == 0)
		out = 1;
	return (out);
}

size_t	single_quotation(char *word_start)
{
	size_t	out;

	out = 0;
	while (word_start[out] != '\'' && word_start[out] != '\0')
	{
		out++;
	}
	if (out == 0)
		out = 1;
	return (out);
}

size_t	double_quotation(char *word_start)
{
	size_t	out;

	out = 0;
	while (word_start[out] != '"' && word_start[out] != '$'
		&& word_start[out] != '\0')
	{
		out++;
	}
	if (out == 0)
		out = 1;
	return (out);
}

size_t	expanded_quotation(char *word_start)
{
	size_t	out;

	out = 0;
	while (word_start[out] != ' ' && word_start[out] != '\0')
	{
		out++;
	}
	if (out == 0)
		out = 1;
	return (out);
}
