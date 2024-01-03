#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

struct student{
    char first_name[20];
    char last_name[20];
    char year[10];
    char utorid[10];
    char uoft_email[50];
    float gpa;
};

int main()
{
    int choice;
    while (choice != 5){
        printf("\n1. Students Information");
        printf("\n2. Search Student");
        printf("\n3. Add Student Information");
        printf("\n4. Delete Student Information");
        printf("\n5. Exit Program");
        printf("\n_____________________________");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                system("cls");
                displayInfo();
                system("cls");
                break;

            case 2:
                system("cls");
                searchStudent();
                system("cls");
                break;

            case 3:
                system("cls");
                addStudent();
                system("cls");
                break;

            case 4:
                system("cls");
                deleteStudent();
                system("cls");
                break;

            case 5:
                system("cls");
                printf("Bye!");
                exit(0);
                break;
        }
    }
}

void displayInfo(){
    FILE *fp;
    struct student info;
    fp = fopen("student_info.txt", "r");

    if (fp == NULL){
        fprintf(stderr, "Can't open file");
        return;
    }

    while(fread(&info, sizeof(struct student), 1, fp)){
        printf("Student Name: %s %s\n",info.first_name, info.last_name);
        printf("Year: %s\n",info.year);
        printf("Utorid: %s\n",info.utorid);
        printf("Email: %s\n",info.uoft_email);
        printf("GPA: %.1f\n\n",info.gpa);
    }
    fclose(fp);

    printf("Press any key to go back...");
    getch();
}

void searchStudent() {
    char searchName[20];
    FILE *fp;
    struct student info;
    int found = 0;
    char searchAgain;

    do {
        printf("Enter the first name to search: ");
        scanf("%s", searchName);

        fp = fopen("student_info.txt", "r");
        if (fp == NULL) {
            fprintf(stderr, "Can't open file");
            return;
        }

        while (fread(&info, sizeof(struct student), 1, fp)) {
            if (strcmp(info.first_name, searchName) == 0) {
                printf("\nStudent Found:\n");
                printf("Name: %s %s\n", info.first_name, info.last_name);
                printf("Year: %s\n", info.year);
                printf("Utorid: %s\n", info.utorid);
                printf("Email: %s\n", info.uoft_email);
                printf("GPA: %.2f\n\n", info.gpa);
                found = 1;
                break;
            }
        }

        fclose(fp);

        if (!found) {
            printf("\nStudent '%s' not found\n", searchName);
            do {
                printf("Do you want to search for another student? (y/n): ");
                scanf(" %c", &searchAgain);
            } while (searchAgain != 'y' && searchAgain != 'n');
        } else {
            do {
                printf("Do you want to search for another student? (y/n): ");
                scanf(" %c", &searchAgain);
            } while (searchAgain != 'y' && searchAgain != 'n');
        }
    } while (searchAgain == 'y');
}

void addStudent(){
    char another;
    FILE *fp;
    struct student info;

    do{
        system("cls");
        fp = fopen("student_info.txt", "a");
        printf("Enter first name: ");
        scanf("%s", &info.first_name);
        printf("Enter last name: ");
        scanf("%s", &info.last_name);
        printf("Enter year (Ex. First): ");
        scanf("%s", &info.year);
        printf("Enter utorid: ");
        scanf("%s", &info.utorid);
        printf("Enter uoft email: ");
        scanf("%s", &info.uoft_email);
        printf("Enter gpa: ");
        scanf("%f", &info.gpa);

        if (fp == NULL){
            fprintf(stderr, "Can't open file");
        }else{
            printf("\nRecord stored successfully\n");
        }

        fwrite(&info, sizeof(struct student), 1, fp);
        fclose(fp);

        printf("Do you want to add another record? (y/n): ");
        scanf("%s", &another);

    }while(another == 'y' || another == 'Y');
}

void deleteStudent() {
    char deleteName[20];
    FILE *fp, *tempFile;
    struct student info;
    int found = 0;
    char deleteAnother;

    do {
        printf("Enter the first name to delete: ");
        scanf("%s", deleteName);

        fp = fopen("student_info.txt", "r");
        if (fp == NULL) {
            fprintf(stderr, "Can't open file");
            return;
        }

        tempFile = fopen("temp.txt", "w");
        if (tempFile == NULL) {
            fprintf(stderr, "Can't create temporary file");
            fclose(fp);
            return;
        }

        while (fread(&info, sizeof(struct student), 1, fp)) {
            if (strcmp(info.first_name, deleteName) != 0) {
                fwrite(&info, sizeof(struct student), 1, tempFile);
            } else {
                found = 1;
            }
        }

        fclose(fp);
        fclose(tempFile);

        if (remove("student_info.txt") != 0) {
            fprintf(stderr, "Error deleting file");
            return;
        }

        if (rename("temp.txt", "student_info.txt") != 0) {
            fprintf(stderr, "Error renaming file");
            return;
        }

        if (found) {
            printf("\nStudent '%s' deleted successfully\n", deleteName);
        } else {
            printf("\nStudent '%s' not found\n", deleteName);
        }

        do {
            printf("Do you want to delete another student? (y/n): ");
            scanf(" %c", &deleteAnother);
        } while (deleteAnother != 'y' && deleteAnother != 'n');
    } while (deleteAnother == 'y');
}
