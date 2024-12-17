/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_char_type.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/02 20:23:15 by mmosk         #+#    #+#                 */
/*   Updated: 2024/08/05 15:54:30 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	is_word_end(char c)
{
	if (ft_isspace(c))
		return (true);
	if (c == '(' || c == ')'
		|| c == '\0')
		return (true);
	return (false);
}

bool	is_lex_end(char c)
{
	if (is_word_end(c))
		return (true);
	if (c == '"' || c == '\''
		|| c == '<' || c == '>'
		|| c == '|' || c == '&'
		|| c == '$' || c == '*')
		return (true);
	return (false);
}

bool	is_special_token(char c)
{
	if (c == '<' || c == '>'
		|| c == '(' || c == ')'
		|| c == '|' || c == '&'
		|| c == '$' || c == '*')
		return (true);
	return (false);
}

bool	is_variable(char c)
{
	if (ft_isalnum(c) || c == '_' || c == '?')
		return (true);
	return (false);
}
