#include <stdio.h>
#include <cs50.h>

struct group{
    char groupname[25];
    char groupletter;
};


int main(void){
    struct group Group;
    Group.groupname = get_string("Group Name:");
    Group.groupletter = get_char("Group Letter: ");
    printf("%s\n", Group.groupname);
    printf("%c\n", Group.groupletter);
}