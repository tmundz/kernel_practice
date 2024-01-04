#ifndef PATHPARSER_H
#define PATHPARSER_H

struct path_root {
    int drive_no;
    struct path_part* first;
};


// linked list to allow easy iteration through paths
struct path_part {
    const char*  part;
    struct path_part* next;
};

/*
function to parse the path for the filesystem
*/
struct path_root* pathparser_parse(const char* path, const char* cur_dir_path);

/*
frees memory the the pathparser was using
*/
void pathparser_free(struct path_root* root);

#endif