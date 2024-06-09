
#include<stdio.h>
#include<string.h>
#include<windows.h>

#define path "C:\\Login & Signup system\\database.txt"

// Global variables for user email and password
char useremail[50];
char userpass[8];

// Function prototypes
void signup();
void login();
int emailcheck();
int passcheck();

int main()
{
    int choice;

    // Main menu loop
    do
    {
        printf("**********MENU********\n");
        printf("Press 1 : Signup\n");
        printf("Press 2 : Login\n");
        printf("Press 3 : Exit\n");
        printf("**********MENU********\n");
        printf("Enter your choice\n");

        // Get user choice
        scanf("%d", &choice);

        // Switch based on user choice
        switch(choice)
        {
            case 1: signup();
             break;
            case 2: login();
             break;
            case 3: printf("exit\n");
             break;
            default: printf("Invalid choice\n"); break;
        }
    } while(choice != 3);

    return 0;
}

// Function to handle user login
void login()
{
    while(getchar() != '\n'); // Clear input buffer

    // Get user email and password
    printf("Enter your email\n");
    gets(useremail);
    printf("Enter your password\n");
    gets(userpass);

    FILE *fptr = NULL;
    fptr = fopen(path, "r");

    // Check if file opened successfully
    if(fptr == NULL)
    {
        system("cls");
        printf("Something went wrong. Please try again.\n");
    }
    else
    {
        char tempstr[50];
        char temppass[8];

        // Read data from the file
        while(fscanf(fptr, "%s", tempstr) == 1)
        {
            if(strcmp(useremail, tempstr) == 0)
            {
                fscanf(fptr, "%s", temppass);

                if(strcmp(userpass, temppass) == 0)
                {
                    system("cls");
                    printf("Login Successful\n");
                    exit(0);
                }
            }
        }

        system("cls");
        printf("Invalid email and password. Please try again or signup.\n");
    }
}

// Function to handle user signup
void signup()
{
    while(getchar() != '\n'); // Clear input buffer

    // Label for goto statement
    check1:

    // Get user email
    printf("Enter an email\n");
    gets(useremail);

    // Check if email is valid
    if(emailcheck() == 0)
    {
        goto check1;
    }
    else
    {
        check2:

        // Get user password
        printf("Enter password\n");
        gets(userpass);

        // Check if password is valid
        if(passcheck() == 0)
        {
            goto check2;
        }
        else
        {
            FILE *fptr = NULL;
            fptr = fopen(path, "a");

            // Check if file opened successfully
            if(fptr == NULL)
            {
                system("cls");
                printf("Something went wrong. Please try again.\n");
            }
            else
            {
                // Write user credentials to the file
                fprintf(fptr, "%s %s\n", useremail, userpass);
                printf("Signup Successful\n");
                fclose(fptr);
                exit(0);
            }
        }
    }
}

// Function to check password validity
int passcheck()
{
    int len = strlen(userpass);

    // Check if password meets criteria
    if(len < 8)
    {
        system("cls");
        printf("Invalid password. Minimum length is 8.\n");
        return 0;
    }

    int i = 0;

    // Check for spaces in password
    while(userpass[i] != '\0')
    {
        if(userpass[i] == ' ')
        {
            system("cls");
            printf("Invalid password. Spaces not allowed.\n");
            return 0;
        }
        i++;
    }

    return 1;
}

// Function to check email validity
int emailcheck()
{
    int len = strlen(useremail);

    // Check if email length is valid
    if(len < 12)
    {
        system("cls");
        printf("Invalid email. Minimum length is 12.\n");
        return 0;
    }

    int i = 0;

    // Check for spaces in email
    while(useremail[i] != '\0')
    {
        if(useremail[i] == ' ')
        {
            system("cls");
            printf("Invalid Email. Spaces not allowed.\n");
            return 0;
        }
        i++;
    }

    char tempstr[] = "moc.liamg@";

    i = 0;

    // Check if email has correct domain format
    while(tempstr[i] != '\0')
    {
        if(tempstr[i] != useremail[len - i - 1])
        {
            system("cls");
            printf("Invalid email. Please use @gmail.com.\n");
            return 0;
        }
        i++;
    }

    FILE *fptr = NULL;
    fptr = fopen(path, "r");

    // Check if file opened successfully
    if(fptr == NULL)
    {
        system("cls");
        printf("Something went wrong. Please try again.\n");
    }
    else
    {
        char tempstr[50];

        // Check if email is already in use
        while(fscanf(fptr, "%s", tempstr) == 1)
        {
            if(strcmp(tempstr, useremail) == 0)
            {
                system("cls");
                printf("Email already in use. Please choose another.\n");
                return 0;
            }
        }
    }

    return 1;
}
