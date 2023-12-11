#ifndef AURORA_H_INCLUDED
#define AURORA_H_INCLUDED
#include <string.h>

void displayAllVehicles(struct NodeVEH *head)
{
    if (head==NULL){
        printf("No vehicles.\n");
        return;
    }
    printf("**************************************\n");
    while(head!=NULL){
        printf("%s %d %s %s %.2lf %d %.2lf %d\n", head->v.plate, head->v.yr, head->v.model, head->v.fuel, head->v.consum, head->v.seat, head->v.price, head->v.avail);
        head=head->next;
    }
    printf("**************************************\n");

    return;
}

int vehicleInfo(struct NodeVEH *headV, char plate []){
     while(headV!=NULL){

            if (strcmp(plate, headV->v.plate)==0){
                printf("This is the information for the vehicle with the selected license plate.\n");
                printf("Plate: ");
                printf("%s\n",headV->v.plate);
                printf("Year: ");
                printf("%d\n",headV->v.yr);
                printf("Model: ");
                printf("%s\n",headV->v.model);
                printf("Fuel: ");
                printf("%s\n",headV->v.fuel);
                printf("Consumption: ");
                printf("%.2lf\n",headV->v.consum);
                printf("Nr. of seats: ");
                printf("%d\n",headV->v.seat);
                printf("Price: ");
                printf("%.2lf\n",headV->v.price);
                return 1;
                }
            headV=headV->next;
        }
    return 0;
}

void searchVehPlate(struct NodeVEH *headV)
{
    char plate[10];
    int foundV=0;
    printf("\nEnter the license plate of the vehicle: \n");
    scanf("%s", plate);

    foundV=vehicleInfo(headV, plate);
    if (foundV==0){
        printf("Vehicle not found!\n");
    }
}



void cancelReservation(struct NodeRES **headR, struct NodeVEH *headV, struct NodeCLI *headC) {
    if (*headR == NULL) {
        printf("There are no reservations. ");
        return;
    }

    printf("Enter the Reservation ID you'd like to prematurely cancel: \n");
    int found = 0;
    int reserID;
    char plate[10];
    char cID[15];
    scanf("%d", &reserID);

    struct NodeRES *current = NULL, *temp;
    current = *headR;
    temp = *headR;

    if (current->r.resID == reserID) {
        *headR = current->next;
        strcpy(plate, current->r.plate);
        strcpy(cID, current->r.clientID);
        free(current);
        found = 1;
        printf("Reservation cancelled!\n");
    } else {
        while (current != NULL) {
            if (reserID == current->r.resID) {
                found = 1;
                printf("Reservation cancelled!\n");
                temp->next = current->next;
                strcpy(plate, current->r.plate);
                strcpy(cID, current->r.clientID);
                free(current);
                break;
            }
            temp = current;
            current = current->next;
        }
    }

    while (headV != NULL) {
        if (strcmp(headV->v.plate, plate) == 0) {
            headV->v.nrRes--;
            break;
        }
        headV = headV->next;
    }

    while (headC != NULL) {
        if (strcmp(headC->c.clientID, cID) == 0) {
            headC->c.nrResTot--;
            break;
        }
        headC = headC->next;  // Add this line to move to the next node
    }
    if (found == 0){
        printf("No such reservation ID found. \n");
        return;
        }
    cntR--;

}


//Display the name, surname and Client ID of all clients who have rented a vehicle (not
//necessarily the same) more than 3 times.
void printClients3Times(struct NodeCLI *head){
    int found=0;
    printf("Clients who have rented a vehicle more than 3 times are: \n");
    while(head!=NULL){
        if(head->c.nrResTot>3){
            printf("Name: %s\nSurname: %s\nClient: %s\n", head->c.name, head->c.surname, head->c.clientID);
            found=1;
        }
        head=head->next;
    }
    if (found==0)
        printf("No clients have more rented a vehicle more than 3 times.\n");
}

#endif // AURORA_H_INCLUDED
