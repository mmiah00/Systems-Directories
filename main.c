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

void gothroughfiles (char * dir_name) {
	printf ("Directories: \n");
	DIR * stream = opendir (dir_name);
	struct dirent * f = readdir (stream);
 	while (f != NULL) {
		printf ("\t%s \n", f -> d_name);
		f = readdir (stream);
  }
	printf ("\n");
	closedir (stream);
}

int findsize (char * dir_name) {
	int ans = 0;
	DIR * stream = opendir (dir_name);
	struct dirent * f = readdir (stream);
	while (f != NULL){
		struct stat * f_stats;
		stat (f-> d_name, f_stats);
		ans += f_stats -> st_size;
		f = readdir (stream);
	}
	return ans;
}

int main () {
	printf ("Total Size: %d\n", findsize ("."));
	gothroughfiles (".");
  return 0;
}
