/*
list all the files in te direcotry
specify which files are direcotires
show the total size of all the regular files in the directory
  note that you do not have to recursively go through any subdirectories to find their size for this part (unless you want to)
have the program scan the current directory
possible enhancements:
  recursively list the files in any subdirectories, update the total to include the total size of subdirecotires
  print out the size in a more readable formate (like using KB, MS, GB for byte prefixes)
  make it look more like $ls -l
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

void gothroughfiles (DIR * d) {
	printf ("Directories: \n");
  	DIR * now = opendir (d);
 	while (now != NULL) {
		printf ("\t");
    		printf (now.d_name);
		printf ("\n");
    		now = readdir (now);
  }
	closedir (d);
}

int main () {
	gothroughfiles ('.');
  return 0;
}
