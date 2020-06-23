# include "ft_ls.h"

void        ft_swap(char **a, char **b)
{
    char *temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

void        sort_r(char **filename)
{
    int     i;
    int     j;

    i = 0;
    j = 0;
    while (filename[i])
        i++;
    i--;
    while (j < i)
        ft_swap(&filename[i--], &filename[j++]);

}
// had issues with mtime, mtim, mtimespec, i hate windows.
void        sort_t(char **filename)
{
    int i;
    int j;
    int k;
    struct stat temp;
    struct stat files[4096];

    i = 0;
    k = 0;
    while (filename[i])
    {
        lstat(filename[i], &files[i]);
        i++;
    }
    while (k < i)
    {
       j = 0;
        while (j+1 < i)
        {
            if (files[j].st_mtim.tv_sec <files[j+1].st_mtim.tv_sec)
            {
                ft_swap(&filename[j], &filename[j+1]);
                temp = files[j];
                files[j] = files[j+1];
                files[j+1] = temp; 
            }
            // if they are created at the same time
            if (files[j].st_mtim.tv_sec == files[j+1].st_mtim.tv_sec)
                if (files[j].st_mtim.tv_nsec < files[j+1].st_mtim.tv_nsec)
                {
                    ft_swap(&filename[j], &filename[j+1]);
                    temp = files[j];
                    files[j] = files[j+1];
                    files[j+1] = temp; 
                }
            j++;
        }
        k++;
    }
    // an alternitive sort by time, takes time needs to be optimized.
    // while (k < i)
    //  {
    //      j = 0;
    //      while (j+1 < i)
    //      {
    //          lstat(filename[j], &file_a);
    //          lstat(filename[j+1], &file_b);
    //          if (file_a.st_mtim.tv_sec < file_b.st_mtim.tv_sec)
    //              ft_swap(&filename[j], &filename[j+1]);
    //          if (file_a.st_mtim.tv_sec == file_b.st_mtim.tv_sec)
    //              if (file_a.st_mtim.tv_nsec < file_b.st_mtim.tv_nsec)
    //                  ft_swap(&filename[j], &filename[j+1]);
    //          j++;
    //      }
    //      k++;
    //  }
}

void        sort_asc(char **filename)
{
    int i;
    int j;
    int k;

    i = 0;
    k = 0;
    while (filename[i])
        i++;
    while (k < i)
    {
        j = 0;
        while (j+1 < i)
        {
            if (ft_strcmp(filename[j], filename[j+1]) > 0)
                ft_swap(&filename[j], &filename[j+1]);
            j++;
        }
        k++;
    }
}

void       ft_sort(char **filename, char *flags)
{
    sort_asc(filename);

    if (ft_strchr(flags, 't'))
    {
        sort_t(filename);
    }
    if (ft_strchr(flags, 'r'))
    {
        sort_r(filename);
    }

}