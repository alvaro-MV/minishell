/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:57:28 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/16 16:15:44 by lvez-dia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char	*cd_build_path(t_exec *exec, char **arg)
{
	char	*cwd;
	char	*tmp;
	char	*path;

	if (!arg[1] || arg[1][0] == '~')
		return (ft_strdup(dict_get(exec->env, "HOME")));
	if (arg[1][0] == '/')
		return (ft_strdup(arg[1]));
	cwd = dict_get(exec->env, "PWD");
	tmp = ft_strjoin(cwd, "/");
	path = ft_strjoin(tmp, arg[1]);
	free(tmp);
	return (path);
}

static int	change_to_oldpwd(t_exec *exec)
{
	const char	*old_dir = dict_get(exec->env, "OLDPWD");
	char		current_wd[PATH_MAX];

	if (!old_dir)
		return (perror("cd: OLDPWD not set"), 1);
	if (chdir(old_dir) != 0)
		return (perror("cd"), 1);
	if (!getcwd(current_wd, PATH_MAX))
		return (perror("cd: getcwd"), 1);
	dict_insert(&exec->env, dict_create_entry(ft_strdup("OLDPWD"),
			ft_strdup(dict_get(exec->env, "PWD"))));
	dict_insert(&exec->env, dict_create_entry(ft_strdup("PWD"),
			ft_strdup(current_wd)));
	return (0);
}

static int	change_directory(t_exec *exec, const char *path)
{
	char	old_cwd[PATH_MAX];
	char	new_cwd[PATH_MAX];

	ft_strlcpy(old_cwd, dict_get(exec->env, "PWD"), PATH_MAX);
	if (chdir(path) != 0)
		return (perror("cd"), 1);
	if (!getcwd(new_cwd, PATH_MAX))
		return (perror("cd: getcwd"), 1);
	dict_insert(&exec->env, dict_create_entry(ft_strdup("OLDPWD"),
			ft_strdup(old_cwd)));
	dict_insert(&exec->env, dict_create_entry(ft_strdup("PWD"),
			ft_strdup(new_cwd)));
	return (0);
}

int	cd(t_exec *exec, char **arg)
{
	int		ret;
	char	*path;

	if (arg[1] && arg[2])
		return (ft_putendl_fd("cd: too many arguments", 2), 1);
	if (arg[1] && arg[1][0] == '-' && arg[1][1] == '\0')
		return (change_to_oldpwd(exec));
	path = cd_build_path(exec, arg);
	if (!path)
		return (ft_putendl_fd("cd: HOME not set", 2), 1);
	ret = change_directory(exec, path);
	free(path);
	return (ret);
}
