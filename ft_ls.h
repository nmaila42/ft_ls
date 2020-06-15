#ifndef FT_LS_H
# define FT_LS_H

# include "libft/libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <time.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdio.h>
# include <pwd.h>
# include <grp.h>
# include <errno.h>

void        ft_sort(char **filename, char *flags);
void        ft_print(char **filenames, char *flags);
void        recurse(char *directory, char *flags);

#endif