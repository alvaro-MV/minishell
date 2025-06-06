/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvez-dia <lvez-dia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:57:28 by lvez-dia          #+#    #+#             */
/*   Updated: 2025/05/14 19:39:14 by lvez-dia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	change_to_oldpwd(t_exec *exec, char *oldpwd, char *print_wd)
{
	t_dic_entry	*pwd_entry;
	t_dic_entry	*oldpwd_entry;

	ft_memcpy(print_wd, dict_get(exec->env, "OLDPWD"), 1024);
	oldpwd = ft_strdup(dict_get(exec->env, "PWD"));
	if (chdir(print_wd) != 0)
	{
		perror("Error: cannot change to old directory");
		return (1);
	}
	pwd_entry = dict_create_entry(ft_strdup("PWD"), ft_strdup(print_wd));
	oldpwd_entry = dict_create_entry(ft_strdup("OLDPWD"), ft_strdup(oldpwd));
	dict_insert(&exec->env, pwd_entry);
	dict_insert(&exec->env, oldpwd_entry);
	free(oldpwd);
	return (0);
}

int	change_directory(t_exec *exec, char *path)
{
	t_dic_entry	*pwd_entry;
	t_dic_entry	*oldpwd_entry;
	char		old_cwd[1024];

	ft_memcpy(old_cwd, dict_get(exec->env, "PWD"), 1024);
	ft_printf("old_cwd en change_directory: %s\n", old_cwd);
	if (chdir(path) != 0)
	{
		perror("Error: path does not exist or cannot be accessed");
		return (1);
	}
	pwd_entry = dict_create_entry(ft_strdup("PWD"), ft_strdup(path));
	oldpwd_entry = dict_create_entry(ft_strdup("OLDPWD"), ft_strdup(old_cwd));
	dict_insert(&exec->env, pwd_entry);
	dict_insert(&exec->env, oldpwd_entry);
	return (0);
}

char	*cd_continue(t_exec *exec, char **arg)
{
	char	*path;
	char	*tmp_path;

	if (arg[1] && arg[1][0] != '~')
	{
		path = ft_strjoin(dict_get(exec->env, "PWD"), "/");
		tmp_path = path;
		path = ft_strjoin(path, arg[1]);
		free(tmp_path);
	}
	else
		path = dict_get(exec->env, "HOME");
	return (path);
}

int	cd(t_exec *exec, char **arg)
{
	char	current_wd[1024];
	char	*oldpwd;
	char	*path;

	if (arg[1] && arg[1][0] == '-' && arg[1][1] == '\0')
	{
		oldpwd = dict_get(exec->env, "OLDPWD");
		if (!oldpwd)
		{
			perror("Error: OLDPWD not set");
			return (1);
		}
		return (change_to_oldpwd(exec, oldpwd, current_wd));
	}
	path = cd_continue(exec, arg);
	if (!path)
	{
		ft_printf("cd: HOME not set\n");
		return (1);
	}
	return (change_directory(exec, path));
}
