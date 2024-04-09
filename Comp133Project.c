#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <strings.h>
#define MAXSIZE 100

/*
Name: Hazar Michael
ID: 1201838
Section: 1
*/

int size = 0;

void displayMainMenu();
void uploadStudentsFile(char names [][100], int stdID [], double phones [], int registrationYear []);
void createNewAccount(char names [][100], int stdID [], double phones [], int registrationYear []);
void removeAccount(char names [][100], int stdID [], double phones [], int registrationYear []);
void viewList(char names [][100], int stdID [], double phones [], int registrationYear []);
void editStudentInfo(char names [][100], int stdID [], double phones [], int registrationYear []);
void viewStudentInfo(char names [][100], int stdID [], double phones [], int registrationYear []);


int main()
{

    char names[MAXSIZE][100] ;
    int stdID[MAXSIZE];
    double phones[MAXSIZE];
    int registrationYear[MAXSIZE];

    char pass[10];
    char password[10] = "hazarC";
    int counter = 0;


    while (counter < 3 )
    {

        printf("Please enter the password : \n");
        gets(pass);
        counter++;

        if ( strcmp(pass, password) != 0)
        {
            char pass = NULL;
            printf("Incorrect Password \n");

        }

        else
        {
            uploadStudentsFile ( names, stdID, phones, registrationYear );

            int h;
            printf("\t\t\t\t\tSTUDENT ACCOUNT MANAGEMENT SYSTEM\n\n");
            printf ("\n");

            displayMainMenu();
            scanf("%d",&h );

            while ( h != 6 )
            {
                switch ( h )
                {
                case 1:

                    createNewAccount(names, stdID, phones, registrationYear);
                    break;

                case 2:
                    removeAccount (names, stdID, phones, registrationYear );
                    break;

                case 3:
                    viewList(names, stdID, phones, registrationYear);
                    break;

                case 4:
                    editStudentInfo(names, stdID, phones, registrationYear );
                    break;

                case 5:
                    viewStudentInfo(names, stdID, phones, registrationYear );
                    break;

                default:
                    printf("INVALID OPERATOR, please enter a correct option between 1 and 6 ");
                }

                printf("\n\n");
                displayMainMenu();
                scanf("%d",&h);
            }

            if (h == 6 )
                printf ("Your program exited, Thank you!");
            break;
        }

    }

    if (counter == 3)
    {
        printf("Sorry, you have reached the limit of trying. try again later.\n");
    }

    return 0;
}




void displayMainMenu()
{
    printf("<< Welcome to the Main Menu >>\n");
    printf ("\n");
    printf("Please Select an Operation from 1 to 6:\n1- Create a new account. \n2- Remove account.\n");
    printf("3- Show student\'s list.\n4- Edit student info.\n5- View specific student info.\n6- Exit System.\n");
}


void uploadStudentsFile(char names [][100], int stdID [], double phones [], int registrationYear [])
{

    FILE *hazarfile = fopen ("students.txt", "r");


    char x[100]= {NULL};

    rewind(hazarfile);

    for (int i = 0; i < MAXSIZE ; i++)
    {

        fscanf(hazarfile,"%s", x);
        fscanf(hazarfile,"%d", &stdID[i]);
        fscanf(hazarfile,"%lf", &phones[i]);
        fscanf(hazarfile,"%d", &registrationYear[i]);
        size++;

        for(int j = 0 ; j< 100 ; j++)
        {
            names[i][j] = x[j];
        }


        if (fgetc(hazarfile)== EOF)
            break;

    }


    fclose( hazarfile );
}


void createNewAccount(char names [][100], int stdID [], double phones [], int registrationYear [])
{

    int tempID;
    double tempPhone;
    int tempYear;
    int exist=0 ;
    char x[100];
    char write;
    if ( size < MAXSIZE )
    {

        printf("Enter the Name of the new student: \n");
        scanf(" %s", &x);


        printf("Enter the ID of the new student: \n");
        scanf(" %d", &tempID);


        printf("Enter the phone number of the new student: \n");
        scanf(" %lf", &tempPhone);

        printf("Enter the registration year of the new student: \n");
        scanf(" %d", &tempYear);

        for (int i = 0; i < size; i++)
        {
            if (stdID[i] == tempID )
            {
                exist = 1;
                break;
            }
        }



        if (exist == 0 )
        {

            for (int j= 0; j < 100; j++)
            {
                names[size][j]= x[j];
            }

            stdID[size]= tempID;
            phones[size]= tempPhone;
            registrationYear[size]= tempYear;
            size++;
            printf("Write new data to the file?\t y = yes, anything else = no\n");
            write = getch();
            if(write == 'y' || write == 'Y' )
            {
                editStudentInfo(names, stdID, phones, registrationYear );
            }
            else
            {
                printf("Data NOT saved to file, you still can save them to the file by using Edit student function from the main menu!\n");
            }

        }
        else
        {
            printf("\n\nERROR. The student is already exist!  Press any key to continue");
            getch();
        }

    }


    else printf("The list is full, sorry we can't add any students\n ");

}


void removeAccount(char names [][100], int stdID [], double phones [], int registrationYear [])
{

    int reqID;
    int foundIDindex;
    int found = 0 ;
    char confirmation;
    char remove;

    if (size > 0)
    {

        printf("Please enter the ID that you want to remove: \n");
        scanf("%d",  &reqID );

        for (int i = 0; i < MAXSIZE ; i++)
        {
            if (reqID == stdID[i])
            {
                foundIDindex = i;
                found = 1;
                break;
            }
            else
            {
                found = 0;

            }
        }
        if ( found )
        {

            printf("Are you sure you want to delete this record? (y = yes, anything else = no) \n\n");


            for (int k = 0; k < 10; k++)
            {
                if(names[foundIDindex][k] != NULL)
                {
                    putchar(names[foundIDindex][k]);
                }
            }

            printf("\t");
            printf("%.0f\t", phones[foundIDindex]);
            printf("%d\n", registrationYear[foundIDindex]);

            confirmation = getch();

            if (confirmation == 'Y'|| confirmation == 'y')
            {
                for(int i = foundIDindex; i < size; i++)
                {
                    for (int l = 0; l < 100; l++)
                    {
                        names[i][l] = names [i+1][l];
                    }
                    stdID[i]= stdID[i+1];
                    phones[i]= phones[i+1];
                    registrationYear[i]= registrationYear[i+1];
                }
                size--;
                printf("The account has been removed from the array , do you want to remove the data from the file?\n");
                printf("y = yes, anything else = no\n\n");
                remove = getch();
                if(remove == 'y' || remove == 'Y' )
                {
                    editStudentInfo(names, stdID, phones, registrationYear );
                }
                else
                {
                    printf("Acount NOT removed from the file, you still can save them to the file by using Edit student function from the main menu!\n");
                }
            }
            else
            {
                printf("Operation has been canceled.");
            }
        }
        else
        {
            printf("<<The requested ID is NOT found>>\n");
        }
    }
    else   printf("The list is empty!\n");

}




void viewList(char names [][100], int stdID [], double phones [], int registrationYear [])
{

    if (size > 0 )
    {
        printf("Here is the list of student info:\n");

        for (int i = 0; i < size; i++ )
        {
            for(int j = 0 ; j < 100 ; j++)
            {
                if(names[i][j] != NULL)

                {
                    printf("%c",names[i][j]);
                }

                else
                {
                    break;
                }


            }
            printf("\t");
            printf("%d \t", stdID[i]);
            printf("%.0f \t", phones[i]);
            printf("%d \n", registrationYear[i]);
        }
    }
    else printf("The list is empty!\n");

}


void editStudentInfo (char names [][100], int stdID [], double phones [], int registrationYear [])
{


    printf("Info has been updated successfully.\n");
    FILE *hazarfile = fopen ("students.txt", "w");
    rewind(hazarfile);
    for (int i = 0; i < size-1 ; i++)
    {
        for (int h = 0; h < 10 ; h++)
        {
            if(names[i][h] != NULL)
            {

                fputc(names[i][h], hazarfile );
            }
            else
            {
                break;
            }
        }
        fputc(' ', hazarfile);
        fprintf(hazarfile, "%d", stdID[i]);
        fputc(' ', hazarfile);
        fprintf(hazarfile, "%f", phones[i]);
        fputc(' ', hazarfile);
        fprintf(hazarfile, "%d", registrationYear[i]);
        fputc('\n', hazarfile);
    }
    for (int h = 0; h < 100 ; h++)
    {
        if(names[size-1][h] != NULL)
        {

            fputc(names[size-1][h], hazarfile );
        }
        else
        {
            break;
        }
    }
    fputc(' ', hazarfile);
    fprintf(hazarfile, "%d", stdID[size-1]);
    fputc(' ', hazarfile);
    fprintf(hazarfile, "%f", phones[size-1]);
    fputc(' ', hazarfile);
    fprintf(hazarfile, "%d", registrationYear[size-1]);
    fclose(hazarfile);
}




void viewStudentInfo(char names [][100], int stdID [], double phones [], int registrationYear [])
{

    int reqID;
    int foundID;
    int found = 0 ;


    if (size > 0)
    {

        printf("Please enter the ID that you want to view: \n");
        scanf("%d",  &reqID );

        for (int i = 0; i < size; i++)
        {
            if (reqID == stdID[i])
            {
                foundID = i;
                found = 1;
                break;
            }

            else
            {
                found = 0;

            }
        }

        if ( found )
        {

            printf("The stored information for the ID %d is: \n\n", stdID[foundID]);
            printf("Name: ");
            for ( int k = 0; k <100 ; k++ )

            {
                if(names[foundID][k] != NULL)
                {

                    printf("%c", names[foundID][k]);
                }
            }

            printf("\n");
            printf("Phone number:  %.0f\n", phones[foundID]);
            printf("Registration Year:  %d\n", registrationYear[foundID]);
        }

        else
        {
            printf("<<The requested ID is NOT found>>\n");
        }

    }
    else   printf("The list is empty!\n");
}
