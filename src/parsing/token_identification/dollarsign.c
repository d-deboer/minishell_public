/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   dollarsign.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 15:02:14 by mmosk         #+#    #+#                 */
/*   Updated: 2024/08/06 13:03:02 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	tid_dollarsign(t_lex **token_start)
{
	if ((*token_start)->is_joined == false)
		return ;
	if ((*token_start)->next == NULL
		|| is_variable((*token_start)->next->content[0]) == false)
		return ;
	(*token_start)->token = VARIABLE;
}
