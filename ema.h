#ifndef EMA_H_INCLUDED
#define EMA_H_INCLUDED

//searching if the client has made a previous reservation
struct NodeCLI* searchID(char ID[15], struct NodeCLI *head){
    if(head==NULL){
        return NULL;
    }
    struct NodeCLI *curr;
    curr=head;
    while(curr!=NULL){
        if(strcmp(ID,curr->c.clientID)==0){
            //it returns the address of the node containing the client info in the client linked list
            return curr;
        }
        curr=curr->next;
    }
    return NULL;

}
//if this is a first time client, add it to the list of clients and get info
void addNewClient(struct NodeCLI **head, struct NodeCLI **tail, char id[15]){

    struct NodeCLI *newClient=NULL;
    newClient=(struct NodeCLI*)malloc(sizeof(*newClient));

    printf("This is a new client. Enter their personal data:");
    printf("\nName: ");
    scanf("%s",newClient->c.name);
    printf("\nSurname: ");
    scanf("%s",newClient->c.surname);
    printf("\nState: ");
    scanf("%s",newClient->c.state);
    printf("\nPhone number: ");
    scanf("%d",&newClient->c.phoneNr);
    strcpy(newClient->c.clientID, id);

    newClient->c.nrResTot=1;
    newClient->next=NULL;

    if((*head)==NULL)
    {
        (*head)=newClient;
        (*tail)=newClient;
        return;
    }

    (*tail)->next=newClient;
    (*tail)=newClient;
    printf("Client added.\n");
    //incrementing total number of clients
    cntC++;

}

//checking if car is available, and getting the price
double FindPrice(char plate[10], struct NodeVEH *head){
    if(head==NULL){
        return 0;
    }
    double price;
    struct NodeVEH *curr;
    curr=head;
    while(curr!=NULL){
        if(strcmp(plate,curr->v.plate)==0){
            price=curr->v.price;
            //if a new reservation is made with this vehicle, add 1 to the number of reservations
            curr->v.nrRes++;
            return price;
        }
        curr=curr->next;
    }
    printf("No vehicle with this plate.");
    return 0;

}

int months[12]={31,28,31,30,31,30,31,31,30,31,30,31};
int isLeapYear(int year)
{
    if (year%400==0) return 1;
    if (year%100==0) return 0;
    return (year%4==0);
}

void newDate(int d1[3], int d2[3], int x){
    d2[0]=d1[0];
    d2[1]=d1[1];
    d2[2]=d1[2];
    for (int i=0;i<x;i++)
        {
            d2[0]++;
            if ((d2[0] > months[d2[1]-1]) || ( d2[1]==2 && d2[0]==29 && isLeapYear(d2[2])==0 ) )
            {
                d2[0] = 1;
                d2[1]++;
                if (d2[1]==13)
                {
                    d2[1] = 1;
                    d2[2]++;
                }
            }
        }


}

void createRes(struct NodeRES **tail,struct NodeRES **head, struct NodeCLI **head1, struct NodeCLI **tail1, struct NodeVEH **head2)
{
    struct NodeRES *newRes;
    newRes=(struct NodeRES *)malloc(sizeof(*newRes));

    printf("Enter data for the new Reservation:");
    printf("\nVehicle Plate: ");
    scanf("%s",newRes->r.plate);
    //finds the price of the vehicle if there is one with the specified plate
    double p=FindPrice(newRes->r.plate, *head2);
    if(p==0){
        printf("No vehicle with this plate. Failed reservation.");
        free(newRes);
        return;
    }

    //generating the reservation ID
    newRes->r.resID = (1000+ cntID + 1);
    printf("\nFirst date of reservation (dd mm yyyy format): ");
    scanf("%d %d %d",&newRes->r.firstDate[0], &newRes->r.firstDate[1], &newRes->r.firstDate[2]);
    printf("\nLength of reservation (days): ");
    scanf("%d",&newRes->r.days);
    //calculating price based on discount rules
    if( newRes->r.days >= 30){
        newRes->r.price=(p* newRes->r.days)*0.8;
    } else if( newRes->r.days >= 14){
        newRes->r.price=(p* newRes->r.days)*0.85;
    }else if( newRes->r.days >= 7){
        newRes->r.price=(p* newRes->r.days)*0.9;
    }else{
        newRes->r.price=(p* newRes->r.days);
    }

    //calling the function that finds the last date
    newDate(newRes->r.firstDate, newRes->r.lastDate, newRes->r.days);

    printf("\nClient ID: ");
    scanf("%s",newRes->r.clientID);
    //searching if this is a first time client
    struct NodeCLI *i=searchID(newRes->r.clientID,*head1);
    if(i==NULL){
        addNewClient(head1, tail1, newRes->r.clientID);
    }
    else{
    i->c.nrResTot++;}

    newRes->next=NULL;

    if(*head==NULL)
    {
        (*head)=newRes;
        (*tail)=newRes;
        cntR++;
        cntID++;
        return;
    }
    (*tail)->next=newRes;
    (*tail)=newRes;
    printf("Reservation entered \n");
    cntR++;
    cntID++;

}


void removeVehicle(struct NodeVEH **head)
{

    if(*head==NULL){
        printf("There are no vehicles. ");
        return;
    }

    printf("Enter the plate number of the vehicle you want to remove: ");
    char plateNum[10];
    scanf("%s", plateNum);

    struct NodeVEH *curr, *prev;
    curr=*head;

    if(strcmp(curr->v.plate,plateNum)==0){
        *head=curr->next;
        free(curr);
        cntV--;
        return;
    }

    while(curr!=NULL){
        if(strcmp(curr->v.plate,plateNum)==0){
            prev->next=curr->next;
            free(curr);
            printf("Vehicle successfully removed.");
            cntV--;
            return;
        }
        prev=curr;
        curr=curr->next;
    }
    printf("No vehicle with that plate number was found.");

}


int isBetweenDates(int first[3], int d[3], int last[3]){
    //out of bounded years
    if(d[2]<first[2] || d[2]>last[2]){
        return 0;
    }
    //same year, out of bound months
    if((first[2]==last[2])&&(first[2]==d[2]) && (d[1]<first[1] || d[1]>last[1])){
        return 0;
    }
    //same year and month, out of bound days
    if(((first[2]==last[2])&&(first[2]==d[2])) && ((first[1]==last[1])&&(first[1]==d[1])) && ((d[0]<first[0] || d[0]>last[0]))){
        return 0;
    }
    //same year as lower bound year, out of bound month
    if(d[2]==first[2] && d[1]<first[1]){
        return 0;
    }
    //same year as upper bound year, out of bound month
    if(d[2]==last[2] && d[1]>last[1]){
        return 0;
    }

    return 1;

}


void isReserved(struct NodeRES* x, struct NodeVEH* head2, int d1[3], int d2[3]) {
    /*
     If the time we want to make the new reservation overlaps with the dates in a stored reservation,
     it means that the vehicle in that reservation is not available during that time.
    */
    struct NodeVEH* curr = head2;
    while (curr != NULL) {
        if (strcmp(x->r.plate, curr->v.plate) == 0) {
            // Check if there is an overlapping reservation
            if (isBetweenDates(x->r.firstDate, d1, x->r.lastDate) || isBetweenDates(d1, x->r.firstDate, d2) ||
                isBetweenDates(x->r.firstDate, d2, x->r.lastDate) || isBetweenDates(d1, x->r.lastDate, d2)) {
                curr->v.avail = 0;
            }
            return;
        }
        curr = curr->next;
    }
}





void vehiclesAvailableXdays(struct NodeRES **tail,struct NodeRES **head, struct NodeCLI **head1, struct NodeCLI **tail1, struct NodeVEH **head2){
    printf("Enter after how many days you want to make the reservation:");
    int x;
    scanf("%d", &x);
    printf("\nFor how many days you want the reservation: ");
    int l;
    scanf("%d", &l);
    int d1[3];
    int d2[3];
    newDate(currentDate, d1, x);
    newDate(d1, d2, l);
    printf("%d %d %d\n%d %d %d\n", d1[0],d1[1],d1[2], d2[0], d2[1], d2[2]);

    if(*head==NULL){
        printf("No available vehicles.");
        return;
    }
    struct NodeRES *curr;
    curr=*head;
    while(curr!=NULL){
        isReserved(curr, *head2, d1, d2);
        curr=curr->next;
    }

    int countingAvail=0;
    struct NodeVEH *curr1;
    curr1=*head2;
    printf("\nAvailable vehicles: \n");
    while(curr1!=NULL){
        if(curr1->v.avail==1){
            countingAvail++;
            printf("%s %d %s %s %.2lf %d %.2lf \n", curr1->v.plate, curr1->v.yr, curr1->v.model, curr1->v.fuel, curr1->v.consum, curr1->v.seat, curr1->v.price);

        }
        //changing back every avail status to 1, we will be reusing this attribute
        curr1->v.avail=1;
        curr1=curr1->next;
    }
    if(countingAvail==0){
        printf("\nNo available vehicles for the specified time frame.\n ");
    }

}


#endif // EMA_H_INCLUDED
