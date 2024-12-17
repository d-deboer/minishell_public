/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: dode-boe <dode-boe@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/16 17:41:00 by dode-boe      #+#    #+#                 */
/*   Updated: 2024/12/17 15:01:58 by dode-boe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "bottleneck.h"
#include "pipex.h"
#include "dirent.h"

int	ft_cd_is_valid(char **argv, char ***env);
int	ft_path_is_valid(char **argv, char ***env);
int	check_path_validity(char *str);

int	ft_cd(char ***env, t_command *curr)
{
	t_ugly_helper	help;
	char			*str;

	if (ft_cd_is_valid(curr->argv, env) == -1)
		return ((ENOENT << 1) + CONT);
	if (ft_path_is_valid(curr->argv, env) == -1)
		return ((ENOENT << 1) + CONT);
	if (curr->argv[1])
		help.ret = chdir(curr->argv[1]);
	else
		help.ret = chdir(find_entry(*env, "HOME"));
	if (help.ret == -1)
		return ((errno << 1) + CONT);
	str = ft_strjoin("OLDPWD=", find_entry(*env, "PWD"));
	if (!str)
		return ((ENOMEM << 1) + EXIT);
	ft_export(env, &(t_command){NULL, NULL, NULL, (char *[]){"export", str, NULL}});
	free(str);
	str = ft_strjoin("PWD=", getcwd(help.buf, 2000));
	if (!str)
		return ((ENOMEM << 1) + EXIT);
	ft_export(env, &(t_command){NULL, NULL, NULL, (char *[]){"export", str, NULL}});
	return (free(str), 0);
}

int	ft_cd_is_valid(char **argv, char ***env)
{
	if (!argv[1] && find_entry(*env, "HOME"))
		return (1);
	else if (!argv[1])
		return (-1);
	if (argv[1][0] == '-' || argv[2])
		return (-1);
	return (1);
}

int	ft_path_is_valid(char **argv, char ***env)
{
	char	*str;
	char	*cmd;
	int		i;

	if (argv[1])
		cmd = argv[1];
	else
		cmd = (char *)find_entry(*env, "HOME");
	if (!cmd)
		return (-1);
	if (ft_strncmp(cmd, "/", 2) == 0)
		return (1);
	str = ft_calloc(ft_strlen(cmd) + 1, sizeof (char));
	if (!str)
		return (-1);
	i = 0;
	while (cmd[i])
	{
		str[i] = cmd[i];
		i++;
		if ((cmd[i] == '/' || !cmd[i]) && check_path_validity(str) == -1)
			return (free(str), -1);
	}
	free(str);
	return (1);
}

int	check_path_validity(char *str)
{
	DIR	*dir;

	dir = opendir(str);
	if (!dir)
		return (-1);
	if (closedir(dir) == -1)
		return (-1);
	return (1);
}

int	ft_cd_child(char ***env, t_command *curr)
{
	int	ret;

	if (ft_cd_is_valid(curr->argv, env) == -1)
		exit(ENOENT);
	if (ft_path_is_valid(curr->argv, env) == -1)
		exit(ENOENT);
	if (curr->argv[1])
		ret = chdir(curr->argv[1]);
	else
		ret = chdir(find_entry(*env, "HOME"));
	if (ret == -1)
		return ((errno << 1) + CONT);
	exit(0);
}
