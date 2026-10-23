#include "filepeek.h"

int fetchmetadata(char *argv[], int argfile);

int main(int argc, char*argv[]) {

	struct stat metadata;

	if(argc > 3) {	//check the number of args
		printf("filepeek: too many arguments\n");
		printf("Usage: ./filepeek <filename>\n");
		return 1;
	} else if(argc == 2 || argc == 3) {
		if(strcmp(argv[1], "--help") == 0) {
			help();
			return 0;
		} else if(strcmp(argv[1], "--version") == 0) {
			version();
			return 0;
		} else if(strcmp(argv[1], "--") == 0){
    			if (argc < 3) {
        			fprintf(stderr, "Usage: filepeek -- <filename>\n");
        			return 2;
    			}
    			int argfile = 2;
    			return fetchmetadata(argv, argfile);
		} else {
			int argfile = 1;
			return fetchmetadata(argv, argfile);
		}
	} else {
		fprintf(stderr, "Usage: ./filepeek <filename>\n");  //defines an error and returns 2 instead
		return 2;
	}

}

int fetchmetadata( char *argv[], int argfile){
			struct stat metadata;
			int checksuccess = stat(argv[argfile], &metadata);  //writes metadata to the struct and evalurates to 0 if successful (-1)
			if(checksuccess == 0) {
				if(S_ISREG(metadata.st_mode)) {
					char timebuf[80];
					struct tm *timedata = localtime(&metadata.st_mtime); 
					if(timedata == NULL) {
						fprintf(stderr, "filepeek: could not convert timestamp\n");
						return 2;
					}
					size_t check = strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", timedata);
					if(check == 0) {
						fprintf(stderr, "filepeek: could not format timestamp data\n");
						return 2;
					}
					printf("Name: %s\n", argv[argfile]);
					printf("Size: %ld\n", metadata.st_size);
					printf("Perms: %o\n", metadata.st_mode & 0777);
					printf("Last modified: %s\n", timebuf);
					return 0;
				} else {
					fprintf(stderr, "filepeek: not a regular file\n");
					return 2;
				}
			} else {
				perror("filepeek");
				return 1;
			}

}

