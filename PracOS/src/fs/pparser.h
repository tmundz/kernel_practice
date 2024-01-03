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



#endif