#ifndef KEIT_H_INCLUDED
#define KEIT_H_INCLUDED

void displayReservations(struct NodeRES *head)
 {
    if(head==NULL)
    {
        printf("\nNo reservations!\n");
        return;
    }
     struct NodeRES *current;
     current=head;
     printf("\nReservations made:\n");
     if (cntR==0)
     {
        printf("No res.");
        return;
     }
     while(current!=NULL)
     {
         printf("%d %d/%d/%d %d %d/%d/%d %lf %s %s\n", current->r.resID, current->r.firstDate[0], current->r.firstDate[1], current->r.firstDate[2], current->r.days, current->r.lastDate[0], current->r.lastDate[1], current->r.lastDate[2], current->r.price, current->r.plate, current->r.clientID);
         current=current->next;
     }

 }


void modifyInformation(struct NodeVEH **head)
{
    struct NodeVEH *current=*head;
    char plateNumber[10];
    char modifyFuel[10];
    double modifyPrice;
    if(current==NULL){
        printf("No vehicles. \n");
        return;
    }
    int option;
    int checkExists=0;

    printf("Enter plate number:\n");
    scanf("%s",plateNumber);
    while(current!=NULL)
    {
        if(strcmp(current->v.plate,plateNumber)==0)
        {
            checkExists=1;
            printf("What information do you want to change(press 1 to change fuel, press 2 to change the price)\n");
            scanf("%d",&option);
            printf("Enter new information:\n");
            if(option==1)
            {
                scanf("%s",modifyFuel);
            }
            else
            {
                scanf("%lf",&modifyPrice);
            }
            switch(option)
            {
            case 1:
                strcpy(current->v.fuel,modifyFuel);
                printf("Successfully modified the information of the fuel to %s.\n",current->v.fuel);
                break;

             case 2:
                current->v.price= modifyPrice;
                printf("Successfully modified the information of the price to %lf.\n",current->v.price);
                break;

             default:
                printf("Invalid option entered!\n");
                break;
            }
            break;
        }
        current=current->next;
    }

    if(checkExists==0){
        printf("Vehicle with plate number %s not found!\n",plateNumber);
        return;
    }
}


void swapInfo(struct NodeVEH **a, struct NodeVEH **b) {
    struct Vehicle temp = (*a)->v;
    (*a)->v = (*b)->v;
    (*b)->v = temp;
}

void sortAndDisplay(struct NodeVEH *head) {
    if (head == NULL) {
        printf("No vehicles in the list.\n");
        return;
    }

    struct NodeVEH* current;
    struct NodeVEH* index = NULL;

    for (current = head; current->next != NULL; current = current->next) {
        for (index = current->next; index != NULL; index = index->next) {
            if (current->v.price > index->v.price)
            {
                swapInfo(&current, &index);
            }
        }
    }

    printf("Sorted Vehicle List:\n");
    current = head;

    while (current != NULL) {
        printf("Plate: %s\nYear: %d\nModel: %s\nFuel: %s\nConsumption: %.2f\nSeats: %d\nPrice: %.2f\n\n",
            current->v.plate, current->v.yr, current->v.model, current->v.fuel, current->v.consum, current->v.seat, current->v.price);
        current = current->next;
    }
}



#endif // KEIT_H_INCLUDED
