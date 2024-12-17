/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   t_command.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/17 22:36:36 by mmosk         #+#    #+#                 */
/*   Updated: 2024/07/29 21:19:43 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "bottleneck.h"

//argc can be larger than necessary.
t_command	*make_command(int argc)
{
	t_command	*out;

	out = malloc(sizeof(t_command));
	if (out == NULL)
		return (NULL);
	out->next_pipe = NULL;
	out->inbound = NULL;
	out->outbound = NULL;
	out->argv = malloc(sizeof(char *) * (argc + 1));
	if (out->argv == NULL)
		return (free(out), NULL);
	ft_memset(out->argv, 0, sizeof(char *) * (argc + 1));
	return (out);
}

void	free_command(t_command *command)
{
	if (command == NULL)
		return ;
	free_command(command->next_pipe);
	free_redirection(command->inbound);
	free_redirection(command->outbound);
	free_ptr_arr((void **)command->argv);
	free(command);
}
