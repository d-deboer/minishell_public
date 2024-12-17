/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   t_redirection.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/17 22:36:41 by mmosk         #+#    #+#                 */
/*   Updated: 2024/10/29 15:19:48 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "bottleneck.h"

//target does not get duplicated. I may change that later.
t_redirection	*make_redirection(t_redirection_type type, char *target)
{
	t_redirection	*out;

	out = malloc(sizeof(t_redirection));
	if (out == NULL)
		return (NULL);
	out->next = NULL;
	out->type = type;
	out->target = target;
	out->fd = -1;
	return (out);
}

void	free_redirection(t_redirection *redirection)
{
	if (redirection == NULL)
		return ;
	free_redirection(redirection->next);
	free(redirection->target);
	free(redirection);
}

void	append_redirection(t_redirection **head, t_redirection *item)
{
	if (*head == NULL)
	{
		*head = item;
	}
	else
	{
		append_redirection(&(*head)->next, item);
	}
}
