#ifndef FILEEXTRACT_H_INCLUDED
#define FILEEXTRACT_H_INCLUDED

int cntC=0;
int cntV=0;
int cntR=0;
int cntID;
int currentDate[3];

void koha(){
    time_t now = time(NULL);
    struct tm* timeinfo = localtime(&now);
    int currentDay = timeinfo->tm_mday;
    int currentMonth = timeinfo->tm_mon + 1;
    int currentYear = timeinfo->tm_year + 1900;
    currentDate[0]=currentDay;
    currentDate[1]=currentMonth;
    currentDate[2]=currentYear;
}



void getVehicleDataFile(struct NodeVEH **head, struct NodeVEH **tail){

    FILE *veh=NULL;
    veh=fopen("vehicle.txt","r");
    if (veh==NULL)
    {
        printf("Cannot open Vehicle file.\n");
        return ;
    }

    struct NodeVEH *prev=NULL, *newNode=NULL;
    fscanf(veh,"%d ", &cntV);
    if(cntV==0)
        return ;
    for(int i=1;i<=cntV;i++)
    {
        newNode=(struct NodeVEH *)malloc(sizeof(struct NodeVEH));
        newNode->next=NULL;
        fscanf(veh," %s%d%s%s%lf%d%lf%d%d",newNode->v.plate, &newNode->v.yr, newNode->v.model, newNode->v.fuel, &newNode->v.consum, &newNode->v.seat, &newNode->v.price, &newNode->v.avail, &newNode->v.nrRes);

        if(*head==NULL){
            *head=newNode;
        }
        else{
        prev->next=newNode;}

        prev=newNode;
    }
    *tail=prev;
    fclose(veh);

}

void addResFromFile(struct NodeRES **head, struct NodeRES **tail)
{
     FILE *fp=NULL;
    fp=fopen("reservations.txt","r");
    if (fp==NULL)
    {
        printf("Cannot open Reservation file.\n");
        return ;
    }

    struct NodeRES *prev=NULL, *newRes=NULL;
    fscanf(fp,"%d ", &cntR);
    if(cntR==0)
        return ;
    for(int i=1;i<=cntR;i++)
    {
        newRes=(struct NodeRES *)malloc(sizeof(*newRes));
        newRes->next=NULL;
        fscanf(fp,"%d%d%d%d%d%d%d%d%lf%s%s" ,&newRes->r.resID, &newRes->r.firstDate[0],&newRes->r.firstDate[1],&newRes->r.firstDate[2],&newRes->r.days, &newRes->r.lastDate[0],&newRes->r.lastDate[1],&newRes->r.lastDate[2], &newRes->r.price, newRes->r.plate, newRes->r.clientID );
        if(*head==NULL){
            *head=newRes;
        }
        else{
        prev->next=newRes;
        }

        prev=newRes;
    }

    *tail=prev;
    //printf("\nAll reservations from the file are in the list!\n");
    fscanf(fp,"%d", &cntID);
    fclose(fp);
}



void readClientInfoFromFile(struct NodeCLI** head, struct NodeCLI** tail) {
    FILE* fp = fopen("clients.txt", "r");
    if (fp == NULL) {
        printf("Cannot open Client file!\n");
        return;
    }

    fscanf(fp, "%d", &cntC);

    if (cntC == 0) {
        printf("No clients in the file!\n");
        fclose(fp);
        return;
    }
    struct NodeCLI* prev = NULL;

    for (int i = 1; i <= cntC; i++) {
        struct NodeCLI* newClient = (struct NodeCLI*)malloc(sizeof(struct NodeCLI));
        fscanf(fp, "%s%s%s%s%d%d", newClient->c.name, newClient->c.surname, newClient->c.clientID, newClient->c.state, &newClient->c.phoneNr, &newClient->c.nrResTot);
        newClient->next = NULL;
        //newClient->c.nrResTot=0;
        if (*head==NULL) {
            *head = newClient;
        } else {
            prev->next = newClient;
        }

        prev = newClient;
    }

    *tail = prev;
    //printf("All clients from file are in the list!\n");
    fclose(fp);
}


void printToVehicleFile(struct NodeVEH *head ){
    FILE *veh=NULL;
    veh=fopen("vehicle.txt","w");
    if (veh==NULL)
    {
        printf("Cannot open Vehicle file.\n");
        return ;
    }
    fprintf(veh,"%d\n", cntV);
    while(head!=NULL){
        fprintf(veh, "%s %d %s %s %.2lf %d %.2lf %d %d\n", head->v.plate, head->v.yr, head->v.model, head->v.fuel, head->v.consum, head->v.seat, head->v.price, head->v.avail, head->v.nrRes);
        head=head->next;
    }
    fclose(veh);

}

void saveReservationstofile(struct NodeRES *head){
FILE *fptr=fopen("reservations.txt", "w");
if (fptr==NULL)
    {
        printf("Cannot open Reservation file.\n");
        return ;
    }
fprintf(fptr, "%d\n", cntR);
while(head!=NULL){
    fprintf(fptr,"%d %d %d %d %d %d %d %d %.2lf %s %s" ,head->r.resID,head->r.firstDate[0],head->r.firstDate[1],head->r.firstDate[2],head->r.days, head->r.lastDate[0],head->r.lastDate[1],head->r.lastDate[2], head->r.price, head->r.plate, head->r.clientID );
    fprintf(fptr,"\n");
    head=head->next;

}
fprintf(fptr, "%d\n", cntID);

fclose(fptr);
}

void saveClientInfo(struct NodeCLI *head)
{
    FILE *file = fopen("clients.txt", "w ");
    if(file==NULL)
    {
        printf("Error.Could not open file!");
        return;
    }
    fprintf(file,"%d\n", cntC);
    while(head!=NULL)
    {
       fprintf(file ,"%s %s %s %s %d %d",head->c.name,head->c.surname,head->c.clientID, head->c.state, head->c.phoneNr, head->c.nrResTot);
       fprintf(file ,"\n");
       head=head->next;
    }
     fclose(file);
}



#endif // FILEEXTRACT_H_INCLUDED
