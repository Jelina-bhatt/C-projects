// Student Data Management System in C
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#define max 100
int totalStudent = 0;
// Structure to represent a student
struct Student
{
  int rno;
  char name[30];
  float per;
};

// Array to store student records
struct Student st[max];

// Function to add student details to a file
void AddtoFile()
{
    FILE *fptr = NULL;

    // Open the file for writing
    fptr = fopen("C:\\Test\\Student_database.txt", "w");

    if (fptr == NULL)
    {
        printf("File related issue\n");
    }
    else
    {
        // Write student details to the file
        for (int i = 0; i < totalStudent; i++)
        {
            fprintf(fptr, "%d %s %f\n", st[i].rno, st[i].name, st[i].per);
        }
        printf("Data Added to file");
        fclose(fptr);
    }
}

// Function to load student records from a file
void loadFile()
{
    FILE *fptr = NULL;

    // Open the file for reading
    fptr = fopen("C:\\Test\\Student_database.txt", "r");

    if (fptr == NULL)
    {
        printf("File related issue\n");
    }
    else
    {
        // Read student details from the file
        while (fscanf(fptr, "%d %s %f", &st[totalStudent].rno, st[totalStudent].name, &st[totalStudent].per) == 3)
        {
            totalStudent++;
        }
        fclose(fptr);
    }
}

// Function to add a new student
void AddStudent()
{
    if (totalStudent > 100)
        printf("Seat full");
    else
    {
        char ch;
        while (1)
        {
            // Get student details from the user
            printf("Enter Student detail\n");
            printf("Enter Rollno \n");
            scanf("%d", &st[totalStudent].rno);
            printf("Enter name\n");
            scanf("%s", st[totalStudent].name);
            printf("Enter percentage\n");
            scanf("%f", &st[totalStudent].per);
            totalStudent++;
            printf("Enter [N]/[n] for main menu\n");
            ch = getche();
            if (ch == 'n' || ch == 'N')
                break;
        }
    }
}

// Function to display all student records
void display()
{
    if (totalStudent == 0)
        printf("No Data\n");
    else
    {
        // Display student records
        printf("RollNO \t Name \t Percentage\n\n");
        for (int i = 0; i < totalStudent; i++)
        {
            printf("%d \t %s \t %f\n", st[i].rno, st[i].name, st[i].per);
        }
    }
}

// Function to update student details
void update()
{
    if (totalStudent == 0)
        printf("No Data\n");
    else
    {
        int r;
        int flag = -1;
        // Get the roll number of the student to be updated
        printf("Enter Rollno of Student for updation\n");
        scanf("%d", &r);

        // Search for the student
        for (int i = 0; i < totalStudent; i++)
        {
            if (r == st[i].rno)
            {
                flag = i;
                break;
            }
        }
        if (flag == -1)
            printf("Student not available\n");
        else
        {
            // Update student details
            printf("Enter name\n");
            scanf("%s", st[flag].name);
            printf("Enter percentage\n");
            scanf("%f", &st[flag].per);
            printf("data updated\n");
        }
    }
}

int main()
{
    int choice;
    loadFile();
    do
    {
        // Display menu
        printf("\n******Menu*******\n");
        printf("Press 1 : Add Details\n");
        printf("Press 2 : Display\n");
        printf("Press 3 : Update Details\n");
        printf("Press 4 : Exit\n");
        printf("******Menu*******\n");
        printf("Enter your choice\n");
        scanf("%d", &choice);

        // Perform action based on user choice
        switch (choice)
        {
        case 1:
            AddStudent();
            break;
        case 2:
            display();
            break;
        case 3:
            update();
            break;
        case 4:
            AddtoFile();
            printf("Exit");
            break;
        default:
            printf("Invalid choice");
            break;
        }
    } while (choice != 4);

    return 0;
}
