/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_tokens.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 15:14:13 by mmosk         #+#    #+#                 */
/*   Updated: 2024/07/11 22:19:08 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	split_tokens(t_lex *sentence)
{
	t_lex	*current;

	current = sentence;
	while (current != NULL)
	{
		if (current->next == NULL)
			current->is_joined = false;
		else if (is_token_split(current->next->token))
			current->is_joined = false;
		current = current->next;
	}
}
