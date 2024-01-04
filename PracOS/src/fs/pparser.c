#include "pparser.h"
#include "kernel.h"
#include "string/string.h"
#include "memory/heap/kheap.h"
#include "memory/memory.h"
#include "status.h"

static int path_valid_format(const char* fname) {
    int len = strnlen(fname, PRACOS_MAX_PATH); // digits for the drive number
    return (len >= 3 && isdigit(fname[0]) && memcmp((void*)&fname[1], ":/", 2) == 0);
}

static int pathparser_get_drive_by_path(const char** path) {
    if (!path_valid_format(*path)) {
        return -EBADPATH;
    }

    int drive_no = todigit(*path[0]);
    // skip drive num 0:/ 1:/
    *path += 3;
    return drive_no;
}

static struct path_root* pathparser_create_root(int drive) {
    struct path_root* path_r = kzalloc(sizeof(struct path_root));
    path_r->drive_no = drive;
    path_r -> first = 0;
    return path_r;
}

static const char* pathparser_get_path_part(const char** path) {
    char* result_path_part = kzalloc(PRACOS_MAX_PATH);
    int sec = 0;
    while(**path != '/' && **path != 0x00) {
        result_path_part[sec] = **path; //set the path char
        *path += 1;
        sec++;

    }

    if (**path == '/') {
        // skip the foreward slash
        *path += 1; //increment after /
    }

    if (sec == 0) {
        kfree(result_path_part);
        result_path_part = 0;
    }

    return result_path_part;
}

struct path_part* pathparser_parse_path_part(struct path_part* last_part, const char** path) {
    const char* path_part_str = pathparser_get_path_part(path);
    if (!path_part_str) {
        return 0;
    }
    struct path_part* part = kzalloc(sizeof(struct path_part));
    part-> part = path_part_str;
    part-> next = 0x00;

    if (!last_part) {
        last_part->next = part;
    }

    return part;
}

void pathparser_free(struct path_root* root) {
    struct path_part* part = root->first;
    while(part) {
        struct path_part* next_part = part->next;
        kfree((void*) part->part);
        kfree(part);
        part = part -> next;
        part = next_part;
    }
    kfree(root);
}

struct path_root* pathparser_parse(const char* path, const char* cur_dir_path) {
    int res = 0;
    const char* tmp_path = path;
    struct path_root* path_root = 0;

    if (strlen(path) > PRACOS_MAX_PATH) {
        goto out;
    }
    res = pathparser_get_drive_by_path(&tmp_path);
    if(res < 0) {
        goto out;
    }

    path_root = pathparser_create_root(res);
    if(!path_root) {
        goto out;
    }
    struct path_part* first_part = pathparser_parse_path_part(NULL, &tmp_path);
    if(!first_part) {
        goto out;
    }

    path_root -> first = first_part;
    struct path_part* part = pathparser_parse_path_part(first_part, &tmp_path);
    while(part) {
        part = pathparser_parse_path_part(part, &tmp_path);
    }
out:
    return  path_root;
}