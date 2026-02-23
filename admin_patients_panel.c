//DUA FATIMA TUL HASSAN
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include"admin_allied_panel.h"
#include"admin_doctors_panel.h"
#include"admin_patients_panel.h"
#include"admin_portal.h"
#include"admin_settings_panel.h"
#include"ANSI-color-codes.h"
#include"patient_panel.h"
#include"patient_portal_sign_up.h"
#include"structures.h"
#include"utility_functions.h"
#include<conio.h>
/////////////////////////////////////////////////////////////////////////////////////////////////
#include <windows.h> // For Sleep()

#define CSV_FILE "patient_biodata.csv"


// Function to simulate loading animation
void loading_animation(const char* message)
 {
    printf(BHBLU"\n\t\t\t\t\t\t\t\t%s ["CRESET, message);
    for (int i = 0; i < 10; i++) {
        Sleep(80);
        printf(BHBLU"#"CRESET);
    }
    printf(BHBLU"]"CRESET);
    Sleep(200);
}

// Function to list all patients
void list_all_patients() 
{
    loading_animation("Loading All Patients");

    FILE *f_pbd = fopen("patient_biodata.csv", "r");
    if (!f_pbd) {
        printf(BHRED"\n\t\t\t\t\t\t\t\tError opening file!\n"CRESET);
        return;
    }

    char line[256];
  printf(BHGRN"\n\t\t\t\t\t\t%-5s %-25s %-25s %-8s %-5s %-15s %-15s\n"CRESET,"ID", "Full Name", "Father/Spouse", "Gender", "Age", "Phone", "CNIC");
	printf(BHGRN"t\t\t\t\t\t\t--------------------------------------------------------------------------------------------------\n"CRESET);


   while (fgets(line, sizeof(line), f_pbd))
{
    Patient p;

    sscanf(line, "%d,%49[^,],%49[^,],%c,%d,%19[^,],%19[^,],%29[^\n]",
           &p.id,
           p.full_name,
           p.F_S_name,
           &p.gender,
           &p.age,
           p.phone_number,
           p.cnic,
           p.username);

    printf("\t\t\t\t\t\t%-5d %-25s %-25s %-8c %-5d %-15s %-15s\n",p.id,p.full_name,p.F_S_name,p.gender,p.age,p.phone_number,p.cnic);
}

    printf("\n\n\t\t\t\t\t\tPress Any Key To Return To Admin Portal Patient's Panel");
    getche();
	

    fclose(f_pbd);
}

// Function to search patient by ID
void search_patient_by_id() 
{
    int search_id;
    printf(BHGRN"\n\t\t\t\t\t\t\t\tEnter Patient ID to search: "CRESET);
    scanf("%d", &search_id);
    while (getchar() != '\n'); // clear leftover newline

    loading_animation("Searching Patient by ID");

    FILE *f_pbd = fopen("patient_biodata.csv", "r");
    if (!f_pbd) {
        printf(BHRED"\n\t\t\t\t\t\t\t\tError opening file!\n"CRESET);
        return;
    }

    char line[256];
    int found = 0;

    while (fgets(line, sizeof(line), f_pbd)) 
	{
        Patient p;

        // Directly read into struct
        sscanf(line, "%d,%49[^,],%49[^,],%c,%d,%19[^,],%19[^,],%29[^\n]",
               &p.id,
               p.full_name,
               p.F_S_name,
               &p.gender,      
               &p.age,
               p.phone_number,
               p.cnic,
               p.username);   

        if (p.id == search_id) 
		{
            printf(BHBLU"\n\t\t\t\t\t\t\t\tPatient Found:\n"CRESET);
            printf("\n\t\t\t\t\t\t\t\tID: %d\n", p.id);
            printf("\t\t\t\t\t\t\t\tFull Name: %s\n", p.full_name);
            printf("\t\t\t\t\t\t\t\tFather/Spouse: %s\n", p.F_S_name);
            printf("\t\t\t\t\t\t\t\tGender: %c\n", p.gender);
            printf("\t\t\t\t\t\t\t\tAge: %d\n", p.age);
            printf("\t\t\t\t\t\t\t\tPhone: %s\n", p.phone_number);
            printf("\t\t\t\t\t\t\t\tCNIC: %s\n", p.cnic);

            found = 1;
            printf(BHMAG TAB"Press Any Key To Return To Admin Portal Patient's Panel"CRESET);
            getche();
            break;
        }
    }

    if (!found)
	 {
        printf(BHMAG"\n\t\t\t\t\t\t\t\tPatient with ID %d not found.\n"CRESET, search_id);
        printf(BHMAG"\n\t\t\t\t\t\t\t\tPress Any Key To Return To Admin Portal Patient's Panel"CRESET);
        getche();
    }

    fclose(f_pbd);
}


// Function to search patient by Username

void search_patient_by_username() 
{
    char search_username[30];
    printf(BHGRN TAB"\n\t\t\t\t\t\t\t\tEnter Patient Username to search: "CRESET);
	 // clear newline from previous input
    fgets(search_username, sizeof(search_username), stdin);
    search_username[strcspn(search_username, "\n")] = 0; // Remove newline

    loading_animation("Searching Patient by Username");

    FILE *f_pbd = fopen("patient_biodata.csv", "r");
    if (!f_pbd) {
        printf(BHRED TAB"\n\t\t\t\t\t\t\t\tError opening file!\n"CRESET);
        return;
    }

    char line[256];
    int found = 0;
 while (fgets(line, sizeof(line), f_pbd)) {
    Patient p;

    sscanf(line, "%d,%49[^,],%49[^,],%c,%d,%19[^,],%19[^,],%29[^\n]",
           &p.id,
           p.full_name,
           p.F_S_name,
           &p.gender,        
           &p.age,
           p.phone_number,
           p.cnic,
           p.username);    

    if (strcmp(p.username, search_username) == 0) 
	{
        printf(BHBLU"\n\t\t\t\t\t\t\t\tPatient Found:\n"CRESET);
        printf("\t\t\t\t\t\t\t\tID: %d\n", p.id);
        printf("\t\t\t\t\t\t\t\tFull Name: %s\n", p.full_name);
        printf("\t\t\t\t\t\t\t\tFather/Spouse: %s\n", p.F_S_name);
        printf("\t\t\t\t\t\t\t\tGender: %c\n", p.gender);
        printf("\t\t\t\t\t\t\t\tAge: %d\n", p.age);
        printf("\t\t\t\t\t\t\t\tPhone: %s\n", p.phone_number);
        printf("\t\t\t\t\t\t\t\tCNIC: %s\n", p.cnic);

        found = 1;
        printf("Press Any Key To Return To Admin Portal Patient's Panel");
        getche();
        break;
    }
}


    if (!found) 
	{
        printf(BHMAG"\n\t\t\t\t\t\t\t\tPatient with Username '%s' not found.\n"CRESET, search_username);
        printf("Press Any Key To Return To Admin Portal Patient's Panel");
    getche();
    }

    fclose(f_pbd);
}
