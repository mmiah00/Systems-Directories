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
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

void gothroughfiles (char * dir_name) {
	printf ("Directories: \n");
	DIR * stream = opendir (dir_name);
	if (!stream || stream == NULL) {
		printf ("Directory %s not found. Error: %s", dir_name, strerror (errno));
	}
	struct dirent * f = readdir (stream);
 	while (f != NULL) {
		printf ("\t%s", f -> d_name);
		if (f -> d_type == DT_DIR) {
			printf ("[DIRECTORY]\n");
		}
		else {
			printf ("[REG FILE]\n");
		}
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
	if (ans < 0) {
		return ans * -1;
	}
	return ans;
}

void printsize (char * dir_name) {
	printf ("Total size: ");
	int size = findsize (dir_name);
	if (size < 1000){
		printf ("%d Bytes", size);
	}
	if (size > 1000) {
		printf ("%d.%f KB\n", size/1000, size % 1000);
	}
	if (size > 1000000) {
		printf ("%d.%f MB\n", size/1000000, size % 1000000);
	}
	if (size > 1000000000) {
		printf ("%d.%f GB\n", size/1000000000, size % 1000000000);
	}
}

int main (int argc, char *argv []) {
	char * name = malloc (100);
	/*
	if (argc <= 1) {
		fgets (name, 100, stdin);
	}
	else {
		name = argv[1];
	}*/
 	 if (argc <= 1){
   		printf("Directory: ");
    	fgets(name, 100, stdin);
    	name[strlen(name)-1] = 0;
 	 }
 	 else {
   		 name = argv[1];
 	 }
	printf ("Total Size: %d Bytes\n", findsize (name));
	gothroughfiles (name);
	return 0;
}
