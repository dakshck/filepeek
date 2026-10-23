#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

void help(void);
void version(void);

int main(int argc, char*argv[]) {

	struct stat metadata;

	if(argc > 2) {	//check the number of args
		printf("filepeek: too many arguments\n");
		printf("Usage: ./filepeek <filename>\n");
		return 1;
	} else if(argc == 2) {
		if(strcmp(argv[1], "--help") == 0) {
			help();
			return 0;
		} else if(strcmp(argv[1], "--version") == 0) {
			version();
			return 0;
		} else {
			int checksuccess = stat(argv[1], &metadata);  //writes metadata to the struct and evalurates to 0 if successful (-1)
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
					printf("Name: %s\n", argv[1]);
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
	} else {
		fprintf(stderr, "Usage: ./filepeek <filename>\n");  //defines an error and returns 2 instead
		return 2;
	}

}

void help(void) {
	printf("Usage: filepeek <filename>\n"
       "\n"
       "Inspect metadata of a regular file.\n"
       "\n"
       "Options:\n"
       "  --help       Display this help message\n"
       "  --version    Display version information\n"
       "\n"
       "Examples:\n"
       "  filepeek main.c\n"
       "  filepeek --help\n"
       "  filepeek --version\n");
}

void version(void) {
	printf("filepeek 0.1.0\n");
}
