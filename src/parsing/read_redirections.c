/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_redirections.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/17 16:05:35 by mmosk         #+#    #+#                 */
/*   Updated: 2024/10/09 15:20:50 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

//Handles redirections.
int	read_redirections(t_lex **current, t_redirection **ob, t_redirection **ib)
{
	t_redirection_type	type;
	char				*target;
	t_redirection		*item;

	while (*current != NULL && is_command_end((*current)->token) == false)
	{
		if (is_redirection((*current)->token))
		{
			type = (t_redirection_type)(*current)->token;
			behead_sentence(current);
			target = extract_word(current);
			if (target == NULL)
				return (FATAL_ERROR);
			item = make_redirection(type, target);
			if (item == NULL)
				return (FATAL_ERROR);
			if (type == INBOUND || type == INBOUND_DELIMIT)
				append_redirection(ib, item);
			else
				append_redirection(ob, item);
		}
		else
			current = &(*current)->next;
	}
	return (0);
}
