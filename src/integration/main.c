/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmosk <mmosk@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/03 16:04:30 by mmosk         #+#    #+#                 */
/*   Updated: 2024/12/03 21:52:04 by mmosk         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sigval;

//Error printing at location where error is generated

int	mainloop(char ***env)
{
	char		*line;
	int			out;

	while (true)
	{
		interactive_signals();
		line = readline("Bring forth thy sorrows: ");
		g_sigval = 0;
		execution_signals();
		if (line == NULL)
			break ;
		add_history(line);
		out = parse(line, env);
		free(line);
		if (out == FATAL_ERROR)
			break ;
	}
	return (out);
}

int	main(int argc, char **argv, char **env)
{
	int		out;
	char	*status;

	(void)argv;
	if (argc != 1)
		return (1);
	if (isatty(1) != true)
		return (perror("Minishell"), 1);
	if (move_to_heap(&env))
		return (1);
	if (ft_dummy_export(&env, 0))
		return (free_ptr_arr((void **)env), 1);
	mainloop(&env);
	status = (char *)find_entry(env, "?");
	if (status != NULL)
		out = ft_atoi(status);
	else
		out = 0;
	free_ptr_arr((void **)env);
	rl_clear_history();
	printf("exit\n");
	return (out);
}
