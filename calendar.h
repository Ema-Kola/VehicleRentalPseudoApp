#ifndef CALENDAR_H_INCLUDED
#define CALENDAR_H_INCLUDED

// Function to check if a year is a leap year
int isItLeapYear(int year)
{
    return ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0);
}

// Function to calculate the day number for a given date
int dayNumber(int day, int month, int year)
{
    int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    year -= month < 3;
    return (year + year / 4 - year / 100 + year / 400 + t[month - 1] + day) % 7;
}

// Function to get the name of the month
char* getMonthName(int monthNumber)
{
    char* month;

    switch (monthNumber) {
    case 0:
        month = "January";
        break;
    case 1:
        month = "February";
        break;
    case 2:
        month = "March";
        break;
    case 3:
        month = "April";
        break;
    case 4:
        month = "May";
        break;
    case 5:
        month = "June";
        break;
    case 6:
        month = "July";
        break;
    case 7:
        month = "August";
        break;
    case 8:
        month = "September";
        break;
    case 9:
        month = "October";
        break;
    case 10:
        month = "November";
        break;
    case 11:
        month = "December";
        break;
    }
    return month;
}

void printCalendar(int year)
{
    printf("Calendar - %d\n", year);

    // number of days in each month
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // February if it's a leap year
    if (isItLeapYear(year))
        daysInMonth[1] = 29;

    //  each month
    for (int month = 0; month < 12; month++) {
        printf("\n ------------%s-------------\n", getMonthName(month));
        printf(" Mon Tue Wed Thu Fri Sat Sun\n");

        // Calculate the starting day of the week for the current month
        int startDay = dayNumber(1, month + 1, year);


        startDay = (startDay + 6) % 7;


        for (int i = 0; i < startDay; i++)
            printf("    ");


        for (int day = 1; day <= daysInMonth[month]; day++) {
            printf("%4d", day);


            if ((startDay + day) % 7 == 0)
                printf("\n");
        }

        printf("\n");
    }
}


#endif // CALENDAR_H_INCLUDED
