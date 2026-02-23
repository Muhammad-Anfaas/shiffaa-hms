//MINHAL IMTIAZ
 #include<stdio.h>
 #include<stdlib.h>
 #include<ctype.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
 #include"admin_allied_panel.h"
 #include"admin_doctors_panel.h"
 #include"admin_patients_panel.h"
 #include"admin_portal.h"
 #include"admin_settings_panel.h"
 #include"ansi-color-codes.h"
 #include"patient_panel.h"
 #include"patient_portal_sign_up.h"
 #include"structures.h"
 #include"utility_functions.h"

 /////////////////////////////////////////////////////////////////////////////////////////////////
 //void list_all_allied_staff(); done AND TESTED
 //void remove_allied_staff(); done and dusted
 //void add_new_allied_staff(); done and dusted
 /////////////////////////////////////////////////////////////////////////////////////////////////




#define MAX 200

/* --------------------------------------------------
   FUNCTION 1: LIST ALL ALLIED STAFF
-------------------------------------------------- */
int list_all_allied_staff()
{
    FILE *fp = fopen("allied_staff_list.csv", "r");
    char job[100], name[100];

    if (!fp) {
        printf("Error opening file.\n");
        return 0;
    }

    printf(BHMAG"\n" TAB"%-20s \t %-20s\n", "Job Title", "Name"CRESET);
    printf(BHRED"\n" TAB"----------------------------------------\n"CRESET);

    while (fscanf(fp, "%[^,],%[^\n]\n", job, name) == 2)
    {
        printf(BHRED"\n"TAB"%-20s \t %-20s\n%s", job, name,CRESET);
    }

    fclose(fp);
    printf(BHMAG TAB"\nPress any key to go back..."CRESET);
    getche();
}

/* --------------------------------------------------
   FUNCTION 2: MARK STAFF POSITION AS VACANT
-------------------------------------------------- */
void mark_staff_vacant()
{
    FILE *fp = fopen("allied_staff_list.csv", "r");
    FILE *temp = fopen("temp.csv", "w");

    char jobs[MAX][100], names[MAX][100];
    int total = 0;

    if (!fp || !temp) {
        printf("File error.\n");
        return;
    }

    /* Read file into arrays */
    while (fscanf(fp, "%[^,],%[^\n]\n", jobs[total], names[total]) == 2)
    {
        total++;
    }
    fclose(fp);

    /* Display menu */
    printf(BHMAG"\n" TAB"Select a position to mark VACANT:\n\n"CRESET);
    for (int i = 0; i < total; i++) {
        printf(BHRED"\n"TAB"%c) %-20s %-20s\n%s", 'A' + i, jobs[i], names[i],CRESET);
    }

    printf(BHRED"\n"TAB"Enter choice: "CRESET);
    char ch = toupper(getche());
    int index = ch - 'A';

    if (index < 0 || index >= total) {
        printf(BHRED"\n"TAB"Invalid choice.\n"CRESET);
        fclose(temp);
        return;
    }

    /* Mark as vacant */
    strcpy(names[index], "vacant_position");

    /* Write updated data */
    for (int i = 0; i < total; i++) {
        fprintf(temp, "%s,%s\n", jobs[i], names[i]);
    }

    fclose(temp);
    remove("allied_staff_list.csv");
    rename("temp.csv", "allied_staff_list.csv");

    printf(BHRED"\n"TAB"Position marked as VACANT.\n"CRESET);
    getche();
}

/* --------------------------------------------------
   FUNCTION 3: FILL A VACANT POSITION
-------------------------------------------------- */
void fill_vacant_staff_position()
{
    FILE *fp = fopen("allied_staff_list.csv", "r");
    FILE *temp = fopen("temp.csv", "w");

    char jobs[MAX][100], names[MAX][100];
    int total = 0;

    if (!fp || !temp) 
	{
        printf("File error.\n");
        return;
    }

    /* Load file */
    while (fscanf(fp, "%[^,],%[^\n]\n", jobs[total], names[total]) == 2)
    {
        total++;
    }
    fclose(fp);

    /* Find vacant positions */
    int vacant_map[MAX];
    int count = 0;

    printf(BHRED"\n"TAB "Vacant Positions:\n\n"CRESET);
    for (int i = 0; i < total; i++) {
        if (strcmp(names[i], "vacant_position") == 0) {
            printf(BHRED"\n"TAB"%c) %s\n%s", 'A' + count, jobs[i],CRESET);
            vacant_map[count] = i;
            count++;
        }
    }

    if (count == 0) 
	{
        printf(BHRED"\n"TAB"No vacant positions available.\n"CRESET);
        fclose(temp);
        getche();
        return;
    }

    /* User selection */
    printf(BHRED"\n"TAB"Select position: "CRESET);
    char ch = toupper(getche());
    int choice = ch - 'A';

    if (choice < 0 || choice >= count) 
	{
        printf(BHRED"\n"TAB"Invalid choice.\n"CRESET);
        fclose(temp);
        return;
    }

    int actual_index = vacant_map[choice];

    /* Enter new staff name */
    printf(BHRED"\n"TAB"Enter new staff name: "CRESET);
    scanf(" %[^\n]", names[actual_index]);

    /* Save updated data */
    for (int i = 0; i < total; i++) 
	{
        fprintf(temp, "%s,%s\n", jobs[i], names[i]);
    }

    fclose(temp);
    remove("allied_staff_list.csv");
    rename("temp.csv", "allied_staff_list.csv");

    printf(BHMAG"\n"TAB"Vacant position filled successfully.\n"CRESET);
    getche();
}

