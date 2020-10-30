#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

// stores list of reservation
int reserve_list[1000] = {0};

// stores train numbers, corresponding to train_details list
int train_number[20] = {1001,1002,1003,1004,1005,1006,1007,1008,1009,1010,1011,1012,1013,1014,1015,1016,1017,1018,1019,1020};

// price of fare, corresponding to the train_details list
int price_list[20] = {1200,1200,1300,1300, 600, 600,2500,2500,1800,1800,1600,1600,1500,1500,1200,1200,1300,1300,1400,1400};

// details of the train
char train_details[20][120] =
{
    "Rajdhani Express    DIBRUGARH        18:15   NEW DELHI        13:55",
    "Rajdhani Express    NEW DELHI        09:25   DIBRUGARH        06:15",
    "Rajdhani Express    HOWRAH JN        16:55   NEW DELHI        10:00",
    "Rajdhani Express    NEW DELHI        16:55   HOWRAH JN        09:50",
    "Rajdhani Express    NEW DELHI        20:40   JAMMU TAWI       05:45",
    "Rajdhani Express    JAMMU TAWI       19:40   NEW DELHI        05:00",
    "Rajdhani Express    TRIVANDRUM CNTL  19:15   H NIZAMUDDIN     12:40",
    "Rajdhani Express    H NIZAMUDDIN     10:55   TRIVANDRUM CNTL  04:55",
    "Rajdhani Express    CHENNAI CENTRAL  06:10   H NIZAMUDDIN     10:25",
    "Rajdhani Express    H NIZAMUDDIN     15:55   CHENNAI CENTRAL  20:15",
    "Rajdhani Express    SECUNDERABAD JN  12:45   H NIZAMUDDIN     10:25",
    "Rajdhani Express    H NIZAMUDDIN     15:55   SECUNDERABAD JN  14:00",
    "Rajdhani Express    RANCHI           17:55   NEW DELHI        10:50",
    "Rajdhani Express    NEW DELHI        16:00   RANCHI           09:00",
    "Rajdhani Express    NEW DELHI        16:25   MUMBAI CENTRAL   08:15",
    "Rajdhani Express    NEW DELHI        16:25   MUMBAI CENTRAL   08:15",
    "Rajdhani Express    AHMEDABAD JN     17:40   NEW DELHI        07:30",
    "Rajdhani Express    NEW DELHI        19:55   AHMEDABAD JN     09:40",
    "Rajdhani Express    BHUBANESWAR      07:10   NEW DELHI        10:40",
    "Rajdhani Express    NEW DELHI        17:05   BHUBANESWAR      20:35",
};

int pid = 1;

struct passengers
{
    int reservation_id;
    char name[80];
    int train_num;
    int num_of_seats;
    int charges;
};

struct trainset
{
    int train_num;
    char train_name[50];
    char source_stn[80];
    char dep_time[5];
    char destination_stn[80];
    char arrival_time[5];
    int price;
};

int getCharges(int tNum, int nSeats)
{
    int idx = tNum - 1001;
    return (price_list[idx]*nSeats);
}

// prints the ticket
void printTicket( int res_id, char name[], int num_of_seats, int t_num, int charges)
{
    system("cls");
    printf("-------------------\n");
    printf("\tTICKET\n");
    printf("-------------------\n\n");
    printf("\nReservation ID:\t\t%d\n",res_id);
    printf("Name:\t\t\t%s",name);
    printf("\nNumber Of Seats:\t%d",num_of_seats);
    printf("\nTrain Number:\t\t%d",t_num);
    printf("\nTotal Charges:\t\t%d\n\n",charges);
    printf("Train No.  Train Name          Src Stn   Src Dep. Time  Dest. Stn   Dest. Arr. Time\n");
    printf("    %d   %s\n", train_number[t_num - 1001], train_details[t_num - 1001]);
}

// function to view details
void viewdetails()
{
    int i;
    printf("Train No.  Train Name          Src Stn   Src Dep. Time  Dest. Stn   Dest. Arr. Time  Price\n");
    for(i = 0; i<20; i++)
    {
        printf("%d       %s   %d\n", train_number[i], train_details[i], price_list[i]);
    }

    return;
}

// writes reservation to a file, by getting input from user
void reservation(void)
{
    char confirm;
    int i=0;

    // structure to store details to write to a file
    struct passengers ticket;
    FILE *fp;
    fp = fopen("seats_reserved.txt","a");
    system("cls");

    // taking in the details
    printf("Enter the details below.");
    printf("\nEnter Your Name: ");
    fflush(stdin);
    gets(ticket.name);

    printf("\n\nPress \'Enter\' To View Available Trains ");
    getch();
    system("cls");
    viewdetails();

    printf("\n\nEnter train number: ");
    while(1)
    {
        scanf("%d",&(ticket.train_num));
        if(ticket.train_num<1001 || ticket.train_num>1020)
        {
            printf("\nInvalid train Number! Enter again. ");
            continue;
        }
        printf("\nEnter Number of seats: ");
        scanf("%d",&ticket.num_of_seats);
        ticket.charges = getCharges(ticket.train_num,ticket.num_of_seats);
        break;
    }
    ticket.reservation_id = pid;
    printTicket(ticket.reservation_id, ticket.name, ticket.num_of_seats, ticket.train_num, ticket.charges);

    while(1)
    {
        scanf("%c",&confirm);
        printf("\n\nConfirm Ticket (y/n):>");
        scanf("%c",&confirm);
        if(confirm == 'y' || confirm == 'Y')
        {
            fwrite(&ticket, sizeof(struct passengers), 1, fp);
            reserve_list[pid] = 1;
            pid++;
            printf("\n Reservation Done\n");
            printf("\nPress any key to go back to Main menu");
            break;
        }
        else
        {
            if(confirm=='n' || confirm == 'N')
            {
                printf("\nReservation Not Done!\nPress any key to go back to  Main menu!");
                break;
            }
            else
            {
                printf("\nInvalid choice entered! Enter again");
            }
        }
    }
    fclose(fp);
    getch();
}

int checkRno(int cn)
{
    if(reserve_list[cn] == 1)
        return 0;
    return 1;
}

void cancel(void)
{
    // take in reservation number
    int cNum;
    char buff;
    printf("Enter Reservation number: ");
    scanf("%d", &cNum);
    if(checkRno(cNum))
    {
        printf("Reservation does not exist\n\n");
        printf("\nPress any key to go back to Main menu\n");
        buff = getchar();
        buff = getchar();
        return;
    }
    FILE *f,*t;

    struct passengers tempTicket;
    f = fopen ("seats_reserved.txt", "r");
    t = fopen ("seats_reserved_temp.txt", "w");

    if ((f == NULL) || (t == NULL))
    {
        printf("\nError opening file\n");
        exit (1);
    }
    int wCheck = 0;

    // read file contents till end of file
    while(fread(&tempTicket, sizeof(struct passengers), 1, f))
    {
        if(tempTicket.reservation_id == cNum)
        {
            continue;
        }
        wCheck = fwrite(&tempTicket, sizeof(struct passengers), 1, t);
    }

    if(wCheck != 0)
    {
        printf("Contents to file written successfully !\n");
    }
    else
    {
        printf("error writing file !\n");
    }

    // close file
    fclose(f);
    fclose(t);

    if(rename("seats_reserved.txt", "seats_reserved_temp2.txt") < 0 )
        printf("renaming error\n");
    if(rename("seats_reserved_temp.txt", "seats_reserved.txt") < 0 )
        printf("renaming error\n");
    if(rename("seats_reserved_temp2.txt", "seats_reserved.txt") < 0 )
        printf("renaming error\n");

    system("cls");
    fflush(stdin);
    printf("\n\nCancelled");
    printf("\nPress any key to go back to Main menu");
    getch();
}

void print_banner_line(int top)
{
    if(top) printf("\t\t===================================================\n");
    printf("\t\t|        ---------------------------------        |\n");
    if(!top) printf("\t\t===================================================\n");
}

void print_banner(void)
{
    print_banner_line(1);
    printf("\t\t|         TRAIN TICKET RESERVATION SYSTEM         |\n");
    print_banner_line(0);
}

// helper function to display options menu
void display_menu()
{
    print_banner();
    printf("\n");
    printf("\n\n1. Reserve A Ticket");
    printf("\n\n2. View All Available Trains");
    printf("\n\n3. Cancel Reservation");
    printf("\n\n4. Exit");
    printf("\n\n------------------------");
    printf("\n\nEnter option:  ");
}

int main()
{
    system("cls");
    print_banner();
    printf(" \n Press any key to continue:");
    getch();
    system("cls");

    int choice;
    while(1)
    {
        system("cls");
        display_menu();
        scanf("%d",&choice);

        switch(choice)
        {
        case 1:
            reservation();
            break;
        case 2:
            viewdetails();
            printf("\n\nPress any key to go to Main Menu...");
            getch();
            break;
        case 3:
            cancel();
            break;
        case 4:
            return 0;
        default:
            printf("\nInvalid choice. Try again.");
        }
    }
    return 0;
}
