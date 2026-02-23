//MUHAMMAD UMAIR
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<ctype.h>
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

//void doctors_schedule for admin();  //DONE + TESTED
//void change_doctors_schedule();    //DONE + TESTED
//void list_all_doctors();			//DONE + TESTED
/////////////////////////////////////////////////////////////////////////////////////////////////


void list_all_doctors()
{
	clear_screen();
    FILE *fp = fopen("doctors_list_sp,nm,id.csv", "r"); 
    if (!fp) 
    {
        printf("Error: Could not open file.\n");
        printf("\nPress Any Key to Return to Admin Doctors Panel");
    getche();
        return;
    }

    char line[500];
    int first_row = 1;
printf("\n");
    while (fgets(line, sizeof(line), fp)) 
	{

        if (first_row)  //THIS LOOP WILL ONLY RUN FOR A SINGLE TIME 
		{   
            first_row = 0;
            continue;
        }

        char *saveptr = NULL;
        char buffered_input[1024];
        strncpy(buffered_input, line, sizeof(buffered_input)-1);
        //buf[sizeof(buffered_input)-1] = '\0';

        char *col1 = strtok_r(buffered_input, ",", &saveptr);  // doctor_id
        char *col2 = strtok_r(NULL, ",", &saveptr);  // doctor_name
        char *col3 = strtok_r(NULL, ",", &saveptr);  // specialization

        if (col1 && col2 && col3)
		 {
            // trim newline from col3
            col3[strcspn(col3, "\n")] = '\0';
            printf(BHRED"\n"TAB"%-25s %-25s %-25s\n", col1, col2, col3);
        }
    }

    printf(BHMAG"\n"TAB"Press Any Key to Return to Admin Doctors Panel");
    getche();

    fclose(fp);
}




void doctors_schedule_for_admin(void) 
{
	clear_screen();
    Doctor doctors[MAX_DOCTORS];
    Patient patients[MAX_PATIENTS];
    int total_docs = load_doctors(doctors);
    int total_pats = load_patients(patients);

    if (total_docs == 0) {
        printf("Doctor list not found!\n");
        printf("\nPress Any Key to Return to Admin Doctors Panel");
        getche();
        return;
    }

    FILE *fp = fopen("doctors_daily_appointment_record.csv", "r");
    if (!fp)
	 {
        printf("doctors_daily_appointment_record.csv not found!\n");
        printf("\nPress Any Key to Return to Admin Doctors Panel");
        getche();
        return;
    }

    char line[MAX_LINE];

    // Time slot labels
//    const char *times[12] = 
//	{
//        "09:00 - 10:00", "10:00 - 11:00", "11:00 - 12:00", "12:00 - 13:00",
//        "13:00 - 14:00", "14:00 - 15:00", "15:00 - 16:00", "16:00 - 17:00",
//        "17:00 - 18:00", "18:00 - 19:00", "19:00 - 20:00", "20:00 - 21:00"
//    };
	//BHMAG BHRED BHBLU BHCYN BHMAG CREST
    printf(BHMAG"\n\t\t\t\t\t\t\t\t==== DOCTORS WEEKLY SCHEDULE (ADMIN VIEW) ====\n\n"CRESET);

    while (fgets(line, sizeof(line), fp)) {

        int doctor_id;
        int slots[12] = {0};

        char *token = strtok(line, ",");
        if (!token) continue;

        doctor_id = atoi(token);

        for (int i = 0; i < 12; i++) 
		{
            token = strtok(NULL, ",");
            slots[i] = token ? atoi(token) : 0;
        }

        char doc_name[100] = "Unknown";
        char doc_spec[100] = "Unknown";

        for (int i = 0; i < total_docs; i++) 
		{
            if (doctors[i].id == doctor_id) {
                strncpy(doc_name, doctors[i].name, sizeof(doc_name) - 1);
                strncpy(doc_spec, doctors[i].spec, sizeof(doc_spec) - 1);
                break;
            }
        }
		//tab colour
        printf(BHRED TAB"Doctor: %s (%s)\n%s", doc_name, doc_spec,CRESET);
        printf(BHRED TAB"ID: %d\n%S", doctor_id,CRESET);
        printf(BHRED TAB"-----------------------------------------------------\n"CRESET);

        // Show only available or booked slots
        for (int i = 0; i < 12; i++) 
		{
            if (slots[i] == 1) 
			{
                printf(BHMAG TAB"[%02d:00-%02d:00]  Available\n%s", 9+i, 10+i,BHRED TAB);
            }
            else if (slots[i] > 1)
			 {
                printf(BHMAG TAB"[%02d:00-%02d:00]  Booked by Patient ID: %d\n%s", 9+i, 10+i, slots[i],CRESET);
            }
        }

        printf("\n");
    }

    fclose(fp);

    printf(BHRED"\n" TAB"\nPress Any Key to Return to Admin Doctors Panel"CRESET);
    getche();
}

// Change doctors schedule
void change_doctors_schedule() 
{
	clear_screen();
    Doctor doctors[MAX_DOCTORS];
    Patient patients[MAX_PATIENTS];
    int total_docs = load_doctors(doctors);
    int total_pats = load_patients(patients);

    if (total_docs == 0) 
	{
        printf(BHRED TAB"Doctor list not found!\n"CRESET);
         printf(BHRED TAB"Press Any Key to Return to Admin Doctors Panel\n"CRESET);
    getche();
        return;
    }

    int doc_id;
    printf(BHGRN"\n"TAB "Enter Doctor ID to edit schedule: " CRESET);
    if (scanf("%d", &doc_id) != 1) {
        clearInputBuffer();
        printf(BHRED "\n"TAB"Invalid input.\n" CRESET);
         printf(BHRED "\n"TAB"Press Any Key to Return to Admin Doctors Panel"CRESET);
    getche();
        return;
    }
    getchar(); // consume newline

    FILE *fp = fopen("doctors_daily_appointment_record.csv", "r");
    if (!fp)
	 {
        printf(BHRED "Schedule file not found!\n" CRESET);
         printf(BHRED "\n"TAB"Press Any Key to Return to Admin Doctors Panel"CRESET);
   	 getche();
        return;
    }

    FILE *temp = fopen("temp.csv", "w");
    if (!temp) 
	{
        printf(BHRED "\n" TAB"Cannot create temp file!\n" CRESET);
         printf(BHRED "\n"TAB"Press Any Key to Return to Admin Doctors Panel"CRESET);
    getche();
        fclose(fp);
        return;
    }

    char line[MAX_LINE]; //line - containers
    int found = 0; //found
    while (fgets(line, sizeof(line), fp)) //eof = NULL 0
	{
        char line_copy[MAX_LINE];
        strncpy(line_copy, line, sizeof(line_copy)-1);
        line_copy[sizeof(line_copy)-1] = '\0';

        char *token = strtok(line_copy, ",");
        int current_doc_id = atoi(token);

        if (current_doc_id == doc_id) {
            found = 1;

            // Find doctor info
            char doc_name[100] = "Unknown", doc_spec[100] = "Unknown";
            for (int i = 0; i < total_docs; i++)
			 {
                if (doctors[i].id == doc_id) {
                    strncpy(doc_name, doctors[i].name, sizeof(doc_name)-1);
                    doc_name[sizeof(doc_name)-1] = '\0';
                    strncpy(doc_spec, doctors[i].spec, sizeof(doc_spec)-1);
                    doc_spec[sizeof(doc_spec)-1] = '\0';
                    break;
                }
            }

            int slots[12] = {0};
            for (int i = 0; i < 12; i++) 
			{
                token = strtok(NULL, ",");
                if (token) 
                {
				
				slots[i] = atoi(token);
			}
                else slots[i] = 0;
            }

            // Display doctor info and slots
            const char *slot_labels[12] = {"A","B","C","D","E","F","G","H","I","J","K","L"};
//            const char *times[12] = 
//			{
//                "09:00-10:00","10:00-11:00","11:00-12:00","12:00-13:00",
//                "13:00-14:00","14:00-15:00","15:00-16:00","16:00-17:00",
//                "17:00-18:00","18:00-19:00","19:00-20:00","20:00-21:00"
//            };

            printf(BHRED "\n"TAB "Doctor: %s\n"TAB"ID: %d\n"TAB"Specialization: %s\n"CRESET, doc_name, doc_id, doc_spec);

            for (int i = 0; i < 12; i++) 
			{
                char status[20];
                if (slots[i] == 0) 
				strcpy(status, "UNAVAILABLE");
				
                else if (slots[i] == 1)
				 strcpy(status, "AVAILABLE");
				 
                else strcpy(status, "BOOKED");
                
                printf(BHMAG TAB "[%s] %02d:00-%02d:00 - %s\n%s", slot_labels[i], 9+i, 10+i, status,CRESET);
            }

            // Admin selects slot to edit
           printf(BHCYN TAB"Enter slot to edit (A-L): "CRESET);
			char choice = toupper(getche()); 



  // read single char and convert to uppercase
printf("\n");  // move to next line after getche()

int idx = choice - 'A';
if (idx < 0 || idx > 11)
 {
    printf(RED TAB "Invalid slot!\n" CRESET);
    printf(BHMAG TAB"Press Any Key to Go Back");
    getch();
    return;
} 
else
 {
    printf(BHGRN TAB "Enter 0 for Unavailable, 1 for Available, or Patient ID (>1) to Book: "CRESET);
    int new_val;
    if (scanf("%d", &new_val) != 1) 
	{
        clearInputBuffer();
        printf(BHRED TAB"Invalid value entered.\n"CRESET);
    } 
	else
	{
        slots[idx] = new_val;
    }
}

            // Write updated row to temp
            fprintf(temp, "%d", doc_id);
            for (int i = 0; i < 12; i++)
                fprintf(temp, ",%d", slots[i]);
            fprintf(temp, "\n");
        } else
		{
            // write unchanged line
            fputs(line, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    if (!found) 
	{
        printf(BHRED TAB"Doctor ID not found in schedule!\n" CRESET);
        remove("temp.csv");
        printf(BHMAG "\n"TAB"Press Any Key to Return to Admin Doctors Panel");
        getche();
        return;
    }

    // Replace original with temp
    remove("doctors_daily_appointment_record.csv");
    rename("temp.csv", "doctors_daily_appointment_record.csv");

    printf(BHGRN"\n"TAB "Schedule updated successfully!\n" CRESET);
      printf(BHGRN"\n"TAB"Press Any Key to Return to Admin Doctors Panel"CRESET);
    getche();
}
