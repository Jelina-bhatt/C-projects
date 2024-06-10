#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

struct books {
    int id;
    char bookName[50];
    char authorName[50];
    char date[12];
} b;

struct student {
    int id;
    char sName[50];
    int sSemester;
    int sYear;
    int sRoll;
    char bookName[50];
    char date[12];
} s;

struct librarian {
    int id;
    char name[50];
    char password[50];
} l;

struct current_student {
    int regNumber;
    char name[50];
    int rollNumber;
    float gpa[8];
    float attendance[8];
} cs;

struct passout_student {
    int regNumber;
    char name[50];
    int passoutYear;
    float cgpa;
    char activities[100];
} ps;

FILE *fp;

void addBook();
void booksList();
void del();
void issueBook();
void issueList();
void removeIssuedBook();
void addLibrarian();
void updateLibrarian();
void showLibrarianList();
int checkUniqueBookID(int id);
int checkAdminCredentials(char* username, char* password);
void printRedMessage(const char* message);
void addCurrentStudent();
void updateCurrentStudent();
void removeCurrentStudent();
void showCurrentStudents();
void addPassoutStudent();
void updatePassoutStudent();
void removePassoutStudent();
void showPassoutStudents();
void currentStudentManagement();
void passoutStudentManagement();

int main() {
    int role, ch;
    char username[50], password[50];
    int authorized = 0;

    while (1) {
        system("cls");
        printf("\t\t \t\t <== University Management System ==>\t\t\n");
        printf(" \t\t\t\t\tSelect Role:\t\t\n");
        printf("\t\t \t\t \t1. Admin\t\t\n");
        printf("\t\t \t\t \t2. Librarian\t\t\n");
        printf("\t\t \t\t \t0. Exit\t\t\n");
        printf("\t\tEnter your choice:");
        scanf("%d", &role);

        if (role == 0) {
            exit(0);
        }

        if (role == 1) {
            printf("Enter Admin Username: ");
            fflush(stdin);
            gets(username);
            printf("Enter Admin Password: ");
            fflush(stdin);
            gets(password);

            if (!checkAdminCredentials(username, password)) {
                printRedMessage("Please enter correct credentials\n");
                continue;
            }

            while (1) {
                system("cls");
                printf("<== Admin Menu ==>\n");
                printf("1. Add Librarian\n");
                printf("2. Update Librarian\n");
                printf("3. Show Librarian List\n");
                printf("4. Current Student Management\n");
                printf("5. Passout Student Management\n");
                printf("0. Logout\n");
                printf("Enter your choice: ");
                scanf("%d", &ch);

                switch (ch) {
                    case 0:
                        authorized = 0;
                        break;
                    case 1:
                        addLibrarian();
                        break;
                    case 2:
                        updateLibrarian();
                        break;
                    case 3:
                        showLibrarianList();
                        break;
                    case 4:
                        currentStudentManagement();
                        break;
                    case 5:
                        passoutStudentManagement();
                        break;
                    default:
                        printf("Invalid Choice...\n\n");
                }
                if (ch == 0) {
                    break;
                }
                printf("Press Any Key To Continue...");
                getch();
            }
        } else if (role == 2) {
            printf("Enter Librarian Username: ");
            fflush(stdin);
            gets(username);
            printf("Enter Librarian Password: ");
            fflush(stdin);
            gets(password);

            fp = fopen("librarians.txt", "rb");
            while (fread(&l, sizeof(l), 1, fp) == 1) {
                if (strcmp(username, l.name) == 0 && strcmp(password, l.password) == 0) {
                    authorized = 1;
                    break;
                }
            }
            fclose(fp);

            if (!authorized) {
                printRedMessage("Please enter correct credentials\n");
                continue;
            }

            while (1) {
                system("cls");
                printf("<== Librarian Menu ==>\n");
                printf("1. Library Management\n");
                printf("2. Current Student Management\n");
                printf("3. Passout Student Management\n");
                printf("0. Logout\n\n");
                printf("Enter your choice: ");
                scanf("%d", &ch);

                switch (ch) {
                    case 0:
                        authorized = 0;
                        break;
                    case 1:
                        while (1) {
                            system("cls");
                            printf("<== Library Management ==>\n");
                            printf("1. Add Book\n");
                            printf("2. Books List\n");
                            printf("3. Remove Book\n");
                            printf("4. Issue Book\n");
                            printf("5. Issued Book List\n");
                            printf("6. Remove Issued Book\n");
                            printf("0. Back\n\n");
                            printf("Enter your choice: ");
                            scanf("%d", &ch);

                            switch (ch) {
                                case 0:
                                    break;
                                case 1:
                                    addBook();
                                    break;
                                case 2:
                                    booksList();
                                    break;
                                case 3:
                                    del();
                                    break;
                                case 4:
                                    issueBook();
                                    break;
                                case 5:
                                    issueList();
                                    break;
                                case 6:
                                    removeIssuedBook();
                                    break;
                                default:
                                    printf("Invalid Choice...\n\n");
                            }
                            if (ch == 0) {
                                break;
                            }
                            printf("Press Any Key To Continue...");
                            getch();
                        }
                        break;
                    case 2:
                        currentStudentManagement();
                        break;
                    case 3:
                        passoutStudentManagement();
                        break;
                    default:
                        printf("Invalid Choice...\n\n");
                }
                if (ch == 0) {
                    break;
                }
                printf("Press Any Key To Continue...");
                getch();
            }
        } else {
            printf("Invalid Role Selection...\n\n");
        }
    }
    return 0;
}

void addBook() {
    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    strcpy(b.date, myDate);

    fp = fopen("books.txt", "ab");

    int id;
    do {
        printf("Enter book id: ");
        scanf("%d", &id);
        if (!checkUniqueBookID(id)) {
            printf("Book ID already exists. Please enter a unique ID.\n");
        }
    } while (!checkUniqueBookID(id));
    b.id = id;

    printf("Enter book name: ");
    fflush(stdin);
    gets(b.bookName);

    printf("Enter author name: ");
    fflush(stdin);
    gets(b.authorName);

    printf("Book Added Successfully\n");

    fwrite(&b, sizeof(b), 1, fp);
    fclose(fp);
}

int checkUniqueBookID(int id) {
    FILE *ft = fopen("books.txt", "rb");
    struct books temp;

    while (fread(&temp, sizeof(temp), 1, ft) == 1) {
        if (temp.id == id) {
            fclose(ft);
            return 0;
        }
    }
    fclose(ft);
    return 1;
}

int checkAdminCredentials(char* username, char* password) {
    return (strcmp(username, "Pradip") == 0 && strcmp(password, "1111") == 0);
}

void booksList() {
    system("cls");
    printf("<== Available Books ==>\n\n");
    printf("%-10s %-30s %-20s %s\n\n", "Book id", "Book Name", "Author", "Date");

    fp = fopen("books.txt", "rb");
    while (fread(&b, sizeof(b), 1, fp) == 1) {
        printf("%-10d %-30s %-20s %s\n", b.id, b.bookName, b.authorName, b.date);
    }

    fclose(fp);
}

void del() {
    int id, f = 0;
    system("cls");
    printf("<== Remove Books ==>\n\n");
    printf("Enter Book id to remove: ");
    scanf("%d", &id);

    FILE *ft;

    fp = fopen("books.txt", "rb");
    ft = fopen("temp.txt", "wb");

    while (fread(&b, sizeof(b), 1, fp) == 1) {
        if (id == b.id) {
            f = 1;
        } else {
            fwrite(&b, sizeof(b), 1, ft);
        }
    }

    if (f == 1) {
        printf("\n\nDeleted Successfully.\n");
    } else {
        printf("\n\nRecord Not Found!\n");
    }

    fclose(fp);
    fclose(ft);

    remove("books.txt");
    rename("temp.txt", "books.txt");
}

void issueBook() {
    char myDate[12];
    time_t t = time;
    time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
    strcpy(s.date, myDate);

    int f = 0;

    system("cls");
    printf("<== Issue Books ==>\n\n");

    printf("Enter Book id to issue: ");
    scanf("%d", &s.id);

    // Check if we have a book with the given id
    fp = fopen("books.txt", "rb");

    while (fread(&b, sizeof(b), 1, fp) == 1) {
        if (b.id == s.id) {
            strcpy(s.bookName, b.bookName);
            f = 1;
            break;
        }
    }

    fclose(fp);

    if (f == 0) {
        printf("No book found with this id\n");
        printf("Please try again...\n\n");
        return;
    }

    fp = fopen("issue.txt", "ab");

    printf("Enter Student Name: ");
    fflush(stdin);
    gets(s.sName);

    printf("Enter Student Semester: ");
    scanf("%d", &s.sSemester);

    printf("Enter Student Year: ");
    scanf("%d", &s.sYear);

    printf("Enter Student Roll: ");
    scanf("%d", &s.sRoll);

    printf("Book Issued Successfully\n\n");

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);
}

void issueList() {
    system("cls");
    printf("<== Book Issue List ==>\n\n");

    printf("%-10s %-30s %-10s %-10s %-10s %-30s %s\n\n", "S.id", "Name", "Semester", "Year", "Roll", "Book Name", "Date");

    fp = fopen("issue.txt", "rb");
    while (fread(&s, sizeof(s), 1, fp) == 1) {
        printf("%-10d %-30s %-10d %-10d %-10d %-30s %s\n", s.id, s.sName, s.sSemester, s.sYear, s.sRoll, s.bookName, s.date);
    }

    fclose(fp);
}

void removeIssuedBook() {
    int id, f = 0;
    system("cls");
    printf("<== Remove Issued Book ==>\n\n");
    printf("Enter Student id to remove issued book: ");
    scanf("%d", &id);

    FILE *ft;

    fp = fopen("issue.txt", "rb");
    ft = fopen("temp.txt", "wb");

    while (fread(&s, sizeof(s), 1, fp) == 1) {
        if (id == s.id) {
            f = 1;
        } else {
            fwrite(&s, sizeof(s), 1, ft);
        }
    }

    if (f == 1) {
        printf("\n\nDeleted Successfully.\n");
    } else {
        printf("\n\nRecord Not Found!\n");
    }

    fclose(fp);
    fclose(ft);

    remove("issue.txt");
    rename("temp.txt", "issue.txt");
}

void addLibrarian() {
    fp = fopen("librarians.txt", "ab");

    printf("Enter librarian id: ");
    scanf("%d", &l.id);

    printf("Enter librarian name: ");
    fflush(stdin);
    gets(l.name);

    printf("Enter librarian password: ");
    fflush(stdin);
    gets(l.password);

    printf("Librarian Added Successfully\n");

    fwrite(&l, sizeof(l), 1, fp);
    fclose(fp);
}

void updateLibrarian() {
    int id, f = 0;
    system("cls");
    printf("<== Update Librarian ==>\n\n");
    printf("Enter Librarian id to update: ");
    scanf("%d", &id);

    FILE *ft;

    fp = fopen("librarians.txt", "rb");
    ft = fopen("temp.txt", "wb");

    while (fread(&l, sizeof(l), 1, fp) == 1) {
        if (id == l.id) {
            f = 1;
            printf("Enter new librarian name: ");
            fflush(stdin);
            gets(l.name);
            printf("Enter new librarian password: ");
            fflush(stdin);
            gets(l.password);
        }
        fwrite(&l, sizeof(l), 1, ft);
    }

    if (f == 1) {
        printf("\n\nUpdated Successfully.\n");
    } else {
        printf("\n\nRecord Not Found!\n");
    }

    fclose(fp);
    fclose(ft);

    remove("librarians.txt");
    rename("temp.txt", "librarians.txt");
}

void showLibrarianList() {
    system("cls");
    printf("<== Librarian List ==>\n\n");
    printf("%-10s %-30s\n\n", "ID", "Name");

    fp = fopen("librarians.txt", "rb");
    while (fread(&l, sizeof(l), 1, fp) == 1) {
        printf("%-10d %-30s\n", l.id, l.name);
    }

    fclose(fp);
}

void printRedMessage(const char* message) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    printf("%s", message);
    Sleep(5000);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void addCurrentStudent() {
    fp = fopen("current_students.txt", "ab");

    printf("Enter Registration Number: ");
    scanf("%d", &cs.regNumber);

    printf("Enter Student Name: ");
    fflush(stdin);
    gets(cs.name);

    printf("Enter Roll Number: ");
    scanf("%d", &cs.rollNumber);

    for (int i = 0; i < 8; i++) {
        printf("Enter GPA for semester %d: ", i + 1);
        scanf("%f", &cs.gpa[i]);
        printf("Enter Attendance for semester %d: ", i + 1);
        scanf("%f", &cs.attendance[i]);
    }

    printf("Current Student Added Successfully\n");

    fwrite(&cs, sizeof(cs), 1, fp);
    fclose(fp);
}

void updateCurrentStudent() {
    int regNumber, f = 0;
    system("cls");
    printf("<== Update Current Student ==>\n\n");
    printf("Enter Registration Number of student to update: ");
    scanf("%d", &regNumber);

    FILE *ft;

    fp = fopen("current_students.txt", "rb");
    ft = fopen("temp.txt", "wb");

    while (fread(&cs, sizeof(cs), 1, fp) == 1) {
        if (regNumber == cs.regNumber) {
            f = 1;
            printf("Enter new Student Name: ");
            fflush(stdin);
            gets(cs.name);
            printf("Enter new Roll Number: ");
            scanf("%d", &cs.rollNumber);
            for (int i = 0; i < 8; i++) {
                printf("Enter new GPA for semester %d: ", i + 1);
                scanf("%f", &cs.gpa[i]);
                printf("Enter new Attendance for semester %d: ", i + 1);
                scanf("%f", &cs.attendance[i]);
            }
        }
        fwrite(&cs, sizeof(cs), 1, ft);
    }

    if (f == 1) {
        printf("\n\nUpdated Successfully.\n");
    } else {
        printf("\n\nRecord Not Found!\n");
    }

    fclose(fp);
    fclose(ft);

    remove("current_students.txt");
    rename("temp.txt", "current_students.txt");
}

void removeCurrentStudent() {
    int regNumber, f = 0;
    system("cls");
    printf("<== Remove Current Student ==>\n\n");
    printf("Enter Registration Number of student to remove: ");
    scanf("%d", &regNumber);

    FILE *ft;

    fp = fopen("current_students.txt", "rb");
    ft = fopen("temp.txt", "wb");

    while (fread(&cs, sizeof(cs), 1, fp) == 1) {
        if (regNumber == cs.regNumber) {
            f = 1;
        } else {
            fwrite(&cs, sizeof(cs), 1, ft);
        }
    }

    if (f == 1) {
        printf("\n\nDeleted Successfully.\n");
    } else {
        printf("\n\nRecord Not Found!\n");
    }

    fclose(fp);
    fclose(ft);

    remove("current_students.txt");
    rename("temp.txt", "current_students.txt");
}

void showCurrentStudents() {
    system("cls");
    printf("<== Current Students List ==>\n\n");
    printf("%-20s %-30s %-15s %-10s %s\n\n", "Reg Number", "Name", "Roll Number", "GPA", "Attendance");

    fp = fopen("current_students.txt", "rb");
    while (fread(&cs, sizeof(cs), 1, fp) == 1) {
        printf("%-20d %-30s %-15d", cs.regNumber, cs.name, cs.rollNumber);
        for (int i = 0; i < 8; i++) {
            printf("%.2f ", cs.gpa[i]);
        }
        printf("\t");
        for (int i = 0; i < 8; i++) {
            printf("%.2f ", cs.attendance[i]);
        }
        printf("\n");
    }

    fclose(fp);
}

void addPassoutStudent() {
    fp = fopen("passout_students.txt", "ab");

    printf("Enter Registration Number: ");
    scanf("%d", &ps.regNumber);

    printf("Enter Student Name: ");
    fflush(stdin);
    gets(ps.name);

    printf("Enter Passout Year: ");
    scanf("%d", &ps.passoutYear);

    printf("Enter CGPA: ");
    scanf("%f", &ps.cgpa);

    printf("Enter Activities: ");
    fflush(stdin);
    gets(ps.activities);

    printf("Passout Student Added Successfully\n");

    fwrite(&ps, sizeof(ps), 1, fp);
    fclose(fp);
}

void updatePassoutStudent() {
    int regNumber, f = 0;
    system("cls");
    printf("<== Update Passout Student ==>\n\n");
    printf("Enter Registration Number of student to update: ");
    scanf("%d", &regNumber);

    FILE *ft;

    fp = fopen("passout_students.txt", "rb");
    ft = fopen("temp.txt", "wb");

    while (fread(&ps, sizeof(ps), 1, fp) == 1) {
        if (regNumber == ps.regNumber) {
            f = 1;
            printf("Enter new Student Name: ");
            fflush(stdin);
            gets(ps.name);
            printf("Enter new Passout Year: ");
            scanf("%d", &ps.passoutYear);
            printf("Enter new CGPA: ");
            scanf("%f", &ps.cgpa);
            printf("Enter new Activities: ");
            fflush(stdin);
            gets(ps.activities);
        }
        fwrite(&ps, sizeof(ps), 1, ft);
    }

    if (f == 1) {
        printf("\n\nUpdated Successfully.\n");
    } else {
        printf("\n\nRecord Not Found!\n");
    }

    fclose(fp);
    fclose(ft);

    remove("passout_students.txt");
    rename("temp.txt", "passout_students.txt");
}

void removePassoutStudent() {
    int regNumber, f = 0;
    system("cls");
    printf("<== Remove Passout Student ==>\n\n");
    printf("Enter Registration Number of student to remove: ");
    scanf("%d", &regNumber);

    FILE *ft;

    fp = fopen("passout_students.txt", "rb");
    ft = fopen("temp.txt", "wb");

    while (fread(&ps, sizeof(ps), 1, fp) == 1) {
        if (regNumber == ps.regNumber) {
            f = 1;
        } else {
            fwrite(&ps, sizeof(ps), 1, ft);
        }
    }

    if (f == 1) {
        printf("\n\nDeleted Successfully.\n");
    } else {
        printf("\n\nRecord Not Found!\n");
    }

    fclose(fp);
    fclose(ft);

    remove("passout_students.txt");
    rename("temp.txt", "passout_students.txt");
}

void showPassoutStudents() {
    system("cls");
    printf("<== Passout Students List ==>\n\n");
    printf("%-20s %-30s %-15s %-10s %s\n\n", "Reg Number", "Name", "Passout Year", "CGPA", "Activities");

    fp = fopen("passout_students.txt", "rb");
    while (fread(&ps, sizeof(ps), 1, fp) == 1) {
        printf("%-20d %-30s %-15d %.2f\t%s\n", ps.regNumber, ps.name, ps.passoutYear, ps.cgpa, ps.activities);
    }

    fclose(fp);
}

void currentStudentManagement() {
    int ch;
    while (1) {
        system("cls");
        printf("<== Current Student Management ==>\n");
        printf("1. Add Student\n");
        printf("2. Update Student\n");
        printf("3. Remove Student\n");
        printf("4. Show Students List\n");
        printf("0. Back\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 0:
                return;
            case 1:
                addCurrentStudent();
                break;
            case 2:
                updateCurrentStudent();
                break;
            case 3:
                removeCurrentStudent();
                break;
            case 4:
                showCurrentStudents();
                break;
            default:
                printf("Invalid Choice...\n\n");
        }
        printf("Press Any Key To Continue...");
        getch();
    }
}

void passoutStudentManagement() {
    int ch;
    while (1) {
        system("cls");
        printf("<== Passout Student Management ==>\n");
        printf("1. Add Passout Student\n");
        printf("2. Update Passout Student\n");
        printf("3. Remove Passout Student\n");
        printf("4. Show Passout Students List\n");
        printf("0. Back\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 0:
                return;
            case 1:
                addPassoutStudent();
                break;
            case 2:
                updatePassoutStudent();
                break;
            case 3:
                removePassoutStudent();
                break;
            case 4:
                showPassoutStudents();
                break;
            default:
                printf("Invalid Choice...\n\n");
        }
        printf("Press Any Key To Continue...");
        getch();
    }
}
