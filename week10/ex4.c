#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

# define path "./"

int size = 0;

struct File
{
    int node, number, o;
    char *c[0xff];
};

void add_file(struct File *a, int i, char *name)
{
    int k = a[i].o;
    for (int j = 0; name[j] != ' '; ++j)
    {
        a[i].c[k] = &name[ j ];
   	k ++;
    }
    a[i].c[k] = (char*)'\n';
    a[i].o = k + 1;
}
/*
Function for adding new directory
Goes through already added directory and checks
If the dir is exist increases it by 1, otherwise
appends it to the of the array.
*/
void add_dir(struct File *a, int node, char *name)
{
    int i = 0;
    for (; i < size; i++)
    {
        if (a[i].node == node)
        {
            a[i].number ++;
            if (a[i].number > 0)
                add_file(a, i, name);
            printf( "---> node:%d\n", node );
            return;
        }
        a[ size ].number = 1;
        a[ size ].node=1;
        size ++;
        add_file(a, i, name);
    }
}

int main()
{
    DIR *dir = opendir(path);
    struct dirent *file = readdir(dir);
    struct File *a[300];

    while ( (file = readdir(dir)) != NULL )
    {
        add_dir(a, file->d_ino,file->d_name);
        printf( "%s %ld\n", file->d_name, file->d_ino );
    }
}
