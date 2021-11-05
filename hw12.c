#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>


// to get currernt directory, argument is .
// takes in command line args, specifically string array
int main(int argc, char *string[]) {

    // path 
    char route[1000];

    
    if (argc > 1) {
        strcpy(route,string[1]);
    } else {
        // to print prompt for terminal input
        printf("Enter directory please:\n");
        int error = read(STDIN_FILENO, route, sizeof(route));
        // if an error, print out whats rong
        if (error == -1) {
            printf("Error %d: %s", errno, strerror(errno));
        }
        route[strlen(route) - 1] = 0;
    }
    
    DIR *dir;

    // to make struct for the information
    struct dirent *e;
    struct stat s;
    long long filesize;

	// to open directory
    dir = opendir(route);
    if (!dir) {
		// if theres an error, print
        printf("Error found %d: %s", errno, strerror(errno));
        return 0;
    }
   
   
    while ((e=readdir(dir))!=NULL){
        if(e->d_type == 8) {
            stat(e->d_name, &s);
            filesize+=s.st_size;
        }
    }
	// print the terminal stuff
	printf("Statistics for directory: %s\n", route);
    printf("Total Directory Size: %lld Bytes\n", filesize);

   
   // TO START AT THE BEGINNING
    rewinddir(dir);
    printf("Directories: \n");
	// prints out directories
    while ((e=readdir(dir))!=NULL){
        if(e->d_type == 4) {
            printf("\t%s\n",e->d_name);
        }
    }

	// to print out the files
    rewinddir(dir); // goes to beginning
    printf("Regular Files: \n");
	// prints out the files
    while ((e=readdir(dir))!=NULL){
        if(e->d_type == 8) {
            stat(e->d_name, &s);
            filesize+=s.st_size;
            printf("\t%s\n",e->d_name);
        }
    }

	closedir(dir);
    return 0;
}