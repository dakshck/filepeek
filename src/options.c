#include <filepeek.h>

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
