# include "ft_ls.h"

//parsing and storing flags
int    parse_flags(int ac, char **av, char *flags)
{
    int     i;
    int     j;

    i = 1;
    ft_bzero(flags, 6);
    while (i < ac && av[i][0] == '-')
    {
        j = 1;
        if (av[i][1] == '-')
            break ;
        while (av[i][j])
        {
            if (!(ft_strchr("larRt", av[i][j])))
            {
                ft_putstr_fd("ft_ls: invalid option -- '", 1);
                ft_putchar_fd(av[i][j], 1);
                ft_putendl_fd("'", 1);
                exit(1);
            }
            else
            {
                if(!ft_strchr(flags, av[i][j]))
                    ft_strncat(flags, &av[i][j], 1);
            }
            j++;
        }
        i++;        
    }
    return (i);
}

//parsing and storing files and directories 
int    parse_paths(char **av, char **files, char **directory, int i)
{
    struct stat filestat;
    int f;
    int d;
    int  err;

    f = 0;
    d = 0;
    err = 1;
    while (av[i])
    {
        if (lstat(av[i], &filestat) == -1)
        {
            ft_putstr_fd("ft_ls: cannot access '", 1);
            ft_putstr_fd(av[i], 1);
            ft_putendl_fd("': No such file or directory ", 1);
            err = 0;
        }
        else
        {
            if (S_ISDIR(filestat.st_mode))
            {
                directory[d] = av[i];
                d++;
            }
            else
                files[f++] = av[i];
            
        }
        i++;
    }
    files[f] = NULL;
    directory[d] = NULL;
    return(err);
}
void    parse(int ac, char **av, char *flags, char **files, char **direct)
{  
    int i;
    int err;

    i = 0;
    i = parse_flags(ac, av, flags);
    err = parse_paths(av, files, direct, i);
    if (!files[0] && !direct[0])
        if (err == 1)
        {
            direct[0] = ".";
            direct[1] = NULL;
        }
}

int     main(int ac, char **av)
{
    char    flags[6];
    char    *files[1024];
    char    *direct[1024];
    int    i;

    parse(ac, av, flags, files, direct);
    
    ft_sort(files, flags);
    if (files[0])
        ft_print(files, flags);

    while (direct[i])
    {
        recurse(direct[i++], flags);
    }

    return (0);
}