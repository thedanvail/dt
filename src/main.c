#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "skill.h"

typedef struct {
    char* p_chars;
    int len;
} str;

typedef struct {
    str cmd_name; 
} command_str;

typedef enum command {
    skill,
    invalid
} command;

command get_command(const command_str* str) {
    if(strncmp(str->cmd_name.p_chars, "skill", str->cmd_name.len) == 0) { return skill; }
    return invalid;
}

void print_help() {
    printf("--- dt (Dan's Tool) ---\n");
    printf("Usage:\n");
    printf("dt skill create <skill name> - creates a new skill file, opens it in Neovim, and symlinks it\n");
    printf("\n\nThat's all I've got so far.\n");
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s <file>\n", argv[0]);
        return 1;
    }

    const char *path = argv[1];

    FILE *fp = fopen(path, "a"); /* create if missing, don't truncate */
    if (!fp) {
        perror("fopen");
        return 1;
    }
    fclose(fp);

    const char* editor = "nvim";

    execlp(editor, editor, path, (char *)NULL);

    /* Only reached if exec failed */
    fprintf(stderr, "exec %s: %s\n", editor, strerror(errno));
    return 1;
}

