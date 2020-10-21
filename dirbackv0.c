#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <dirent.h>

int dirScan( char directory_location[1024], int level);
int copyFile( char *source, char* dest);

int dirScan( char directory_location[1024], int level)
{
    DIR *dirptr = opendir( directory_location);
    struct dirent *entry;
    char newPath[1024];
    char level_index[10];

    for(int i = 0; i < level; i++)
    {
	strcat( level_index, "|-");
    }

    level++;

    if( dirptr == NULL)
    {
	printf("no directory found");
	return 0;
    }

    while( (entry = readdir( dirptr)) != NULL)
    {
	if(! ( strcmp( entry->d_name, "..") && strcmp( entry->d_name, ".")))
	{
	    // do nothing
	}
	else if( entry->d_type == DT_DIR) // && strcmp( entry->d_name, "..") && strcmp( entry->d_name, "."))
	{
	    strcpy( newPath, directory_location);
	    strcat( newPath, "/");
	    strcat( newPath, entry->d_name);
	    printf( "%s%s is directory\n", level_index, entry->d_name);
	    dirScan( newPath, level);
	}
	else
        {
	    printf( "%s%s is not directory\n", level_index, entry->d_name);
	}
    }

    closedir( dirptr);
    return 1; 
}
    

int main( int argc, char *argv[])
{
    int initial_level = 0;
    
    if( argc < 2)
    {
	printf(" no input\n");
    }

    dirScan( argv[1], initial_level);
   
}
