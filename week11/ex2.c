# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>

int main()
{
	DIR *dir = opendir("/");
	struct dirent *item;
	while( 1 ){
		item = readdir(dir);
		if( item ){
			if( (*item).d_type == DT_REG || (*item).d_type == DT_DIR ){
				printf("%s\n", (*item).d_name);
			}
		}
		else{
			break;
		}
	}
	closedir(dir);
	return 0;
}
