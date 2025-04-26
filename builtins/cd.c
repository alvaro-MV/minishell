#include "builtins.h"

//OBJETIVO = cd /home/usuario


//chdir()


/*int ft_cd(char **args)
{
    if (!args[1])
    {
        printf("Error: faltan argumentos\n");
        return 1;
    }
    if (chdir(args[1]) != 0)
    {
        perror("Error al cambiar el directorio");
        return 1;
    }
    return 0;
}*/

int change_to_oldpwd(t_exec *exec, char *oldpwd, char *print_wd)
{
    t_dic_entry *pwd_entry;
    t_dic_entry *oldpwd_entry;

    // if (getcwd(print_wd, 1024) == NULL)
    // {
    //     perror("Error: cannot retrieve current directory");
    //     return (1);
    // }
    ft_printf("que es print_wd: %s\n", print_wd);
    ft_printf("que es oldpwd: %s\n", oldpwd);
    if (chdir(oldpwd) != 0)
    {
        perror("Error: cannot change to old directory");
        return (1);
    }
    pwd_entry = dict_create_entry(ft_strdup("PWD"), ft_strdup(print_wd));
    oldpwd_entry = dict_create_entry(ft_strdup("OLDPWD"), ft_strdup(oldpwd));
    dict_insert(&exec->env, pwd_entry);
    dict_insert(&exec->env, oldpwd_entry);
    ft_printf("Es aqui donde no saca nadaaa %s\n", oldpwd);
    return (0);
}

int change_directory(t_exec *exec, char *path)
{
    t_dic_entry *pwd_entry;
    t_dic_entry *oldpwd_entry;

    char old_cwd[1024];

    // if (getcwd(old_cwd, sizeof(old_cwd)) == NULL)
    // {
    //     perror("Error: cannot retrieve current directory");
    //     return (1);
    // }
    memcpy(old_cwd, dict_get(exec->env, "PWD"), 1024);
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

int cd(t_exec *exec, char **arg)
{
    char current_wd[1024];
	char *oldpwd;
	char *path;

    if (arg[1] && arg[1][0] == '-' && arg[1][1] == '\0')
    {
        oldpwd = dict_get(exec->env, "OLDPWD");
        if (!oldpwd)
        {
            perror("Error: OLDPWD not set");
            return (1);
        }
        return(change_to_oldpwd(exec, oldpwd, current_wd));
    }
    if (arg[1])
		path = arg[1];
	else
		path = dict_get(exec->env, "HOME");	
	if (!path)
	{
		ft_printf("cd: HOME not set\n");
		return (1);
	}
	return (change_directory(exec, path));
}