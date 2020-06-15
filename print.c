#include "ft_ls.h"

void print_2d_array(char **array)
{
    while (*array)
        ft_putendl(ft_strrchr(*array++, '/') + 1);
}

void    print_type(struct stat filestat)
{
    if (S_ISDIR(filestat.st_mode))
        ft_putchar('d');
    if (S_ISREG(filestat.st_mode))
        ft_putchar('-');
    if (S_ISCHR(filestat.st_mode))
        ft_putchar('c');
    if (S_ISBLK(filestat.st_mode))
        ft_putchar('b');
    if (S_ISFIFO(filestat.st_mode))
        ft_putchar('f');
    if (S_ISLNK(filestat.st_mode))
        ft_putchar('l');
    if (S_ISSOCK(filestat.st_mode))
        ft_putchar('s');

}
void    print_permissions(struct stat filestat)
{
    ft_putchar((filestat.st_mode & S_IRUSR)?'r':'-');
    ft_putchar((filestat.st_mode & S_IWUSR)?'w':'-');
    ft_putchar((filestat.st_mode & S_IXUSR)?'x':'-');
    ft_putchar((filestat.st_mode & S_IRGRP)?'r':'-');
    ft_putchar((filestat.st_mode & S_IWGRP)?'w':'-');
    ft_putchar((filestat.st_mode & S_IXGRP)?'x':'-');
    ft_putchar((filestat.st_mode & S_IROTH)?'r':'-');
    ft_putchar((filestat.st_mode & S_IWOTH)?'w':'-');
    ft_putchar((filestat.st_mode & S_IXOTH)?'x':'-');
}

void    print_hardlinks(struct stat filestat)
{
    ft_putchar('\t');
    ft_putnbr(filestat.st_nlink);
}

void    print_user(struct stat filestat)
{
    
    ft_putchar('\t');
    ft_putstr(getpwuid(filestat.st_uid)->pw_name);
}

void    printf_group(struct stat filestat)
{
    struct group *grp;

    grp = getgrgid(filestat.st_gid);
    ft_putchar('\t');
    ft_putstr(grp->gr_name);
    
}

void    printf_size(struct stat filestat)
{
    ft_putchar('\t');
    ft_putnbr(filestat.st_size);
}

void    printf_time(struct stat filestat)
{
    char date[14];
    ft_putchar('\t');
    ft_memcpy(date, &ctime(&filestat.st_mtime)[4], 12);
    ft_putstr(date);
}
void    print_bocks_size(char **files)
{
    struct stat filestat;
    int         total;

    total = 0;
    while (*files)
    {
        lstat(*files++, &filestat);
        total += filestat.st_blocks;
    }
    ft_putstr("Total: ");
    ft_putnbr(total / 2);
    ft_putchar('\n');
}

void    print_long_format(char **files)
{
    print_bocks_size(files);
    struct stat filestat;
    while (*files)
    {
        lstat(*files, &filestat);
        print_type(filestat);
        print_permissions(filestat);
        print_hardlinks(filestat);
        print_user(filestat);
        printf_group(filestat);
        printf_size(filestat);
        printf_time(filestat);
        ft_putstr("   ");
        ft_putendl(ft_strrchr(*files, '/') + 1);
        files++;
    }
}

void    ft_print(char **filenames, char *flags)
{
    if (ft_strchr(flags, 'l'))
        print_long_format(filenames);
    else
        print_2d_array(filenames);
}