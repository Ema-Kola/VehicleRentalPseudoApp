#ifndef ALLSTRUCT_H_INCLUDED
#define ALLSTRUCT_H_INCLUDED
struct Vehicle{
    char plate[10];
    int yr;
    char model[20];
    char fuel[20];
    double consum;
    int seat;
    double price;
    int nrRes;
    int avail;
};

struct Client{
    char clientID[15];
    char name[20];
    char surname[20];
    char state[15];
    int nrResTot;
    int phoneNr;
};

struct Reservation{
    int resID;
    int firstDate[3];
    int days;
    int lastDate[3];
    double price;
    char plate[10];
    char clientID[15];
};

struct NodeCLI {
    struct Client c;
    struct NodeCLI * next;
};

struct NodeRES{
    struct Reservation r;
    struct NodeRES *next;
};

struct NodeVEH{
    struct Vehicle v;
    struct NodeVEH *next;
};

#endif // ALLSTRUCT_H_INCLUDED
