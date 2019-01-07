#ifndef _PROJ_
#define _PROJ_
#include <pthread.h>
#define NODE struct node
extern pthread_mutex_t mutex;

extern void insert();
extern int checkDuplicate();
extern void list();
extern void delRow();
extern void showDepartment();
extern void showInfo();
extern void readFile();
extern int saveFile();
extern void collectData();
extern void deleteAll();
extern void changeDepartment();
extern void recursion();
extern void *autoSave();
extern void displaySave();

union extra
{
    float fever;
    char pain[30];
    int daySick;
};


struct node
{
    char name[20];
    int department;
    union extra additionalInfo;
    struct node *next;
};

struct things
{
    NODE *head;
    NODE *tail;
};

extern struct things departments[4];

#endif

