#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define MAX 1024

int dirScan( char *location, int dirlvl);
int copyFile( char source_file[20], char dest_file[20]);

int copyFile( char *source_file, char *dest_file)
{
  //FILE *source, *dest;
  // char *ch;

  int source, dest, from_source, to_dest;
  char buff[MAX];

  source = open( source_file, O_RDONLY);
  dest = creat( dest_file, 0644);

  while( (from_source = read( source, &buff, MAX )) > 0)
  {
    to_dest = write( dest, &buff, from_source);
  }

  close( source);
  close( dest);
}

int dirScan( char *location, int dirlvl)
{
  DIR *dirptr = opendir( location);
  struct dirent *entry;
  char newpath[MAX];
  char level[10];

  for( int i = 0; i < dirlvl; i++)
  {
    strcat( level, "|-");
  }
  dirlvl++;
  
  if( dirptr == NULL)
  {
    printf( "Could not find directory in the given location.");
    return 0;
  }

  while( (entry = readdir( dirptr)) != NULL)
  {
   
    if( entry->d_type == DT_DIR && strcmp( entry->d_name, "..") && strcmp( entry->d_name, "."))
    {
      strcpy( newpath, location);
      strcat( newpath, "/");
      strcat( newpath, entry->d_name);
      // printf( "%s is a directory\n\n", newpath);
      dirScan( newpath, dirlvl);
    }
    else
    {
       printf( "%s%s\n", level, entry->d_name);
    }
  }

  closedir( dirptr);
  return 1;
}



int main( int argc, char *argv[])
{
  int opt;
  char inputDir[125];
  // ':' in the starting of stirng so that
  // the compiler can know '?' and ':'
  // command line options 
  while((opt = getopt(argc, argv, ":i:o:h")) != -1)
  {
    switch(opt)
    {
      case 'i':
	strcpy( inputDir, optarg);
	printf("i = %s", inputDir);
	dirScan( inputDir, 0);
	break;
      case 'o':
        printf("o = %s", optarg);
	break;
      case 'h':
        printf("help");
	break;
      case '?':
        printf("help");
	break;
    }
  }      
  return 1;
}
