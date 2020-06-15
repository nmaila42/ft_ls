#include "ft_ls.h"


void read_filesystem(char *direct, char **files, char **directories, char *flags)
{
    DIR             *dir;
    struct dirent   *entry;
    char            temp[1024];
    int             f;
    int             d;

    f = 0;
    d = 0;
    ft_bzero(temp, 1024);
    if (!(dir = opendir(direct)))
        exit(1);
    while ((entry = readdir(dir)) != NULL)
    {
        if ( entry->d_name[0] != '.' || ft_strchr(flags, 'a'))
        {
            ft_strcpy(temp, direct);
            ft_strcat(temp, "/");
            ft_strcat(temp, entry->d_name);
            files[f++] = ft_strdup(temp);
            if (entry->d_type == DT_DIR)
                directories[d++] = ft_strdup(temp);
        }
    }
    files[f] = NULL;
    directories[d]= NULL;
    closedir(dir);
}

void    free_array(char **array)
{
    while(*array)
        free(*array++);
}

void    recurse(char *direct, char *flags)
{
    char *files[1024];
    char *directories[1024];
    char subdir[1024];
    int d;

    
    ft_bzero(subdir, 1024);
    read_filesystem(direct, files, directories, flags);
    ft_sort(files, flags);
    ft_sort(directories, flags);
    ft_print(files, flags);
    if (ft_strchr(flags, 'R'))
    {
        d = 0;
        while (directories[d])
        { 
            if (!ft_strequ(ft_strrchr(directories[d], '/'),"/.") && !ft_strequ(ft_strrchr(directories[d], '/'), "/.."))
            {

                ft_putendl("");
                ft_putendl(directories[d]);
                recurse(directories[d], flags);
            }
            d++;
        }
    }
    free_array(files);
    free_array(directories);
}