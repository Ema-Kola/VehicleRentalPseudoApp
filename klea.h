#ifndef KLEA_H_INCLUDED
#define KLEA_H_INCLUDED
#include <stdbool.h>
#include <time.h>

void isVehicleAvailable(struct NodeRES *headR, int date[3], struct NodeVEH *headV) {
    printf("\nHow long do you want to rent the vehicle: ");
    int l;
    scanf("%d", &l);
    int lastDate[3];
    newDate(currentDate,lastDate,l);
    struct NodeRES *curr=NULL;
    curr=headR;

    if (curr == NULL){
        //if there are no reservations, all vehicles are available
       displayAllVehicles(headV);

       }

     while(curr!=NULL){
        isReserved(curr, headV, currentDate, lastDate);
        curr=curr->next;
    }

    int countingAvail=0;
    struct NodeVEH *curr1;
    curr1=headV;
    printf("\nAvailable vehicles: \n ");
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





void AddNewVehicle(struct NodeVEH **head, struct NodeVEH **tail){
    struct NodeVEH *newNode;
    newNode=(struct NodeVEH*)malloc(sizeof(struct NodeVEH));
    printf("Add plate:");
    scanf(" %s",newNode->v.plate);
    printf("Add year:");
    scanf(" %d",&newNode->v.yr);
    printf("Add model: ");
    scanf(" %s",newNode->v.model);
    printf("Add fuel: ");
    scanf(" %s",newNode->v.fuel);
    printf("Add consumption: ");
    scanf(" %lf",&newNode->v.consum);
    printf("Add the number of seats: ");
    scanf(" %d",&newNode->v.seat);
    printf("Add the price: ");
    scanf(" %lf",&newNode->v.price);
    newNode->v.avail=1;
    newNode->v.nrRes=0;
    newNode->next=NULL;
    cntV++;
    if(*head==NULL){
        printf("\nThis is the first vehicle.\n");
        *head=newNode;
        *tail=newNode;

        return;
    }
    else{

        (*tail)->next=newNode;
        *tail=newNode;
        printf("You just added a vehicle. \n");
    }
}



void saveExcessP(struct NodeRES *head) {
    double x;
    printf("Enter price: ");
    scanf("%lf", &x);
    FILE* file = fopen("exceedingprice.txt", "w");
    if (file == NULL) {
        printf("Error opening reservation file!");
        return;
    }

    struct NodeRES* current = head;
    while (current != NULL) {
        if (current->r.price >x) {
            fprintf(file, "%d ", current->r.resID);
            fprintf(file, "%d %d %d ", current->r.firstDate[0], current->r.firstDate[1], current->r.firstDate[2]);
            fprintf(file, "%d ", current->r.days);
            fprintf(file, "d %d %d ", current->r.lastDate[0], current->r.lastDate[1], current->r.lastDate[2] );
            fprintf(file, "%.2f ", current->r.price);
            fprintf(file, "\n");
        }
        current = current->next;
    }

    fclose(file);
    printf("Reservations saved to file: exceedingprice.");
}


void displayTop3ReservedVehicles(struct NodeVEH *head, struct NodeRES *reservations) {

    if (head == NULL) {
        printf("No vehicles in the list.\n");
        return;
    }

    struct NodeVEH* current;
    struct NodeVEH* index = NULL;

    for (current = head; current->next != NULL; current = current->next) {
        for (index = current->next; index != NULL; index = index->next) {
            if (current->v.nrRes < index->v.nrRes)
            {
                swapInfo(&current, &index);
            }
        }
    }

    current = head;
    if(cntV<3){
        printf("There are less than 3 vehicles:\n");
        while(current!=NULL){
            printf("Plate: %s\nYear: %d\nModel: %s\nFuel: %s\nConsumption: %.2f\nSeats: %d\nPrice: %.2f\n\n",
                current->v.plate, current->v.yr, current->v.model, current->v.fuel, current->v.consum, current->v.seat, current->v.price);
            current = current->next;
        }
    }else{
        printf("Top 3 Most Reserved Vehicles:\n");
        for(int i=0;i<3;i++){
            printf("Plate: %s\nYear: %d\nModel: %s\nFuel: %s\nConsumption: %.2f\nSeats: %d\nPrice: %.2f\n\n",
                   current->v.plate, current->v.yr, current->v.model, current->v.fuel, current->v.consum, current->v.seat, current->v.price);
            current = current->next;
        }

    }


}


#endif // KLEA_H_INCLUDED
