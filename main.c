#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "allstruct.h"
#include "fileextract.h"
#include "ema.h"
#include "aurora.h"
#include "keit.h"
#include "klea.h"
#include "calendar.h"



int main()
{

    koha();
    printf("\t\t\t\t\tCurrent date: %02d/%02d/%04d\n\n", currentDate[0], currentDate[1], currentDate[2]);

    printf("\t\t\t*   *                      ****                        *   \n");
    printf("\t\t\t*   *                      *   *                      * *  \n");
    printf("\t\t\t*   *                      *   *                     *   * \n");
    printf("\t\t\t*   *                      ****                     *******\n");
    printf("\t\t\t * *                       *  *                     *     *\n");
    printf("\t\t\t  *   Vehicle              *   *  Rental            *     *     Application\n\n");

    struct NodeVEH *headV=NULL, *tailV=NULL;
    struct NodeRES *headR=NULL, *tailR=NULL;
    struct NodeCLI *headC=NULL, *tailC=NULL;

    addResFromFile(&headR, &tailR);
    readClientInfoFromFile(&headC, &tailC);
    getVehicleDataFile(&headV, &tailV);
    int year;

    printf("\n\nMenu: \n");
    printf("\n\
1-Display all vehicle information.\n\
2-Display available vehicles currently.\n\
3-Display vehicles that will be available after x days.\n\
4-Create a new reservation.\n\
5-Add a new vehicle.\n\
6-Search for a vehicle using the license plate number.\n\
7-Sort and display all vehicles according to their daily rental price.\n\
8-Display the top 3 most reserved vehicles. \n\
9-Display all reservations.\n\
10-Remove a vehicle. (delete)\n\
11-Cancel a reservation. (delete)\n\
12-Display the name, surname and Client ID of all clients who have rented a vehicle more than 3 times.\n\
13-Save all reservations with a total cost exceeding x to a new file.\n\
14-Modify information for a vehicle using its plate number. \n\
Press 15 for a little surprise ;)         \n " );


    while(1){
    printf("\nChoose an option or press 0 to stop: ");
    int option;
    scanf("%d", &option);
    switch(option)
    {
    case 1:{
        displayAllVehicles(headV);
        break;
    }
    case 2:{
        isVehicleAvailable(headR, currentDate, headV);
        break;
    }
    case 3:{
        vehiclesAvailableXdays(&tailR, &headR, &headC, &tailC, &headV);
        break;
    }
    case 4:{
        createRes(&tailR, &headR, &headC, &tailC, &headV);
        break;
    }
    case 5:{
        AddNewVehicle(&headV, &tailV);
        break;
    }
    case 6:{
           searchVehPlate(headV);
        break;
    }
    case 7:{
        sortAndDisplay(headV);
        break;
    }
    case 8:{
        displayTop3ReservedVehicles(headV, headR);
        break;
    }
    case 9:{
        displayReservations(headR);
        break;
    }
    case 10:{
        removeVehicle(&headV);
        break;
    }
    case 11:{
        cancelReservation(&headR, headV, headC);
        break;
    }
    case 12:{
        printClients3Times(headC);
        break;
    }
    case 13:{
        saveExcessP(headR);
        break;
    }
    case 14:{
        modifyInformation(&headV);
        break;
    }

    case 0:{
        saveReservationstofile(headR);
        printToVehicleFile(headV);
        saveClientInfo(headC);
        return 0;
    }

    default:{
        printf("The option is not valid!");
        break;
    }
    case 15:
        {
            printf("Enter the year: ");
            scanf("%d", &year);
            printCalendar(year);
            break;
        }

    }

    }

    return 0;
}



