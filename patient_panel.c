#include<stdio.h> 
#include<string.h>
#include<stdlib.h>
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
#include<ctype.h>
/////////////////////////////////////////////////////////////////////////////////////////////////

const char *hour_labels[12] = {
    "09:00-10:00","10:00-11:00","11:00-12:00","12:00-13:00",
    "13:00-14:00","14:00-15:00","15:00-16:00","16:00-17:00",
    "17:00-18:00","18:00-19:00","19:00-20:00","20:00-21:00"
};

// ----------------------------------------------------------------------
// PATIENT PANEL MENU
// ----------------------------------------------------------------------
void patient_panel_menu(int patient_id) 
{
    while (1) 
    {
         clear_screen();

    printf(BHRED"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\tWelcome to the Patient Panel!\n"CRESET);
    printf(BHRED"%s\n"CRESET, h_line);

    printf(BHBLU"\n\t\t\t\t\t\t\t\tPlease Select an appropriate option\n\n"CRESET);
    printf(BHBLU"\t\t\t\t\t\t\t\t1) Book Appointment\n"CRESET);
    printf(BHBLU"\t\t\t\t\t\t\t\t2) Cancel Appointment\n"CRESET);
    printf(BHBLU"\t\t\t\t\t\t\t\t3) View Your Biodata\n"CRESET); //DUA + MINHAL
    printf(BHBLU"\t\t\t\t\t\t\t\t4) View Doctors List\n"CRESET); //DUA + MINHAL
    printf(BHBLU"\t\t\t\t\t\t\t\t5) View Doctor Schedule\n"CRESET);
    printf(BHBLU"\t\t\t\t\t\t\t\t6) Return to Previous Menu\n"CRESET);
    printf(BHBLU"\t\t\t\t\t\t\t\t7) Exit Application\n"CRESET);

    printf(BHRED"%s\n"CRESET, h_line);
    printf(BHGRN"\t\t\t\t\t\t\t\tPlease Enter Your Choice: "CRESET);

    int choice = getche();

        switch (choice) 
        {
           case '1':
    loading_bar("Booking Appointment");
    book_patient_appointment(patient_id);
    break;

case '2':
    loading_bar("Canceling Appointment");
    cancel_patient_appointment(patient_id);
    break;

case '3':
    loading_bar("Loading Biodata");
    view_patient_biodata(patient_id);
    break;

case '4':
       loading_bar("Loading Doctors List");
    clear_screen();
    view_doctors_list();
    
    break;

case '5':
 loading_bar("Loading Doctor Schedule");
    show_doctor_slots();
    break;

case '6':
       loading_bar("Returning to Previous Menu");
    return; // Return to previous menu
    break;
    case '7':
 loading_bar("Exiting Application");
    clear_screen();
    printf(BHRED"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\tGood Bye!\n"CRESET);
    exit(0); // Exit application
    break;

            default:
                printf("Invalid choice!\nPress Enter to try again...");
                clearInputBuffer();
                getchar();
        }
    }
}
//DUA + MINHAL
// ----------------------------------------------------------------------
// VIEW DOCTORS LIST
// ----------------------------------------------------------------------
void view_doctors_list()
{
    FILE *fp = fopen("doctors_list_sp,nm,id.csv", "r");
    if (!fp) {
        printf("Error: Could not open file.\n");
        return;
    }

    char line[1024];
    int first_row = 1;
printf(BHCYN"\n\n\n\t\t\t\t\t\t\t\t   DOCTOR NAME %s%s\t\t  SPECIALIZATION\n"CRESET,CRESET,BHBLU );
    while (fgets(line, sizeof(line), fp)) {
        if (first_row) { first_row = 0; continue; }

        char *saveptr;
        char *col1 = strtok_r(line, ",", &saveptr);
        char *col2 = strtok_r(NULL, ",", &saveptr);
        char *col3 = strtok_r(NULL, ",", &saveptr);
		
        if (col2 && col3) 
		{
        	
            printf(BHRED"\n\t\t\t\t\t\t\t\t%-25s %s%s%-25s"CRESET, col2,CRESET,BHMAG ,col3);
        }
    }

    fclose(fp);
    printf("\t\t\t\t\t\t\tPress any key to return to the Patient Panel...\n"TAB);
    getche();
}

// ----------------------------------------------------------------------
// FETCH DOCTOR INFO
// ----------------------------------------------------------------------
int get_doctor_info(int doctor_id, char *name, char *spec)
{
    FILE *fp = fopen("doctors_list_sp,nm,id.csv", "r");
    if (!fp)
    {
	printf("\nError Opening File\n");
	 return 0;
	}
    char line[MAX_LINE];
    while (fgets(line, sizeof(line), fp)) {
        int id;
        char dname[200], dspec[200];

        char *token = strtok(line, ",");
        if (!token) continue;
        id = atoi(token);

        if (id == doctor_id) {
            token = strtok(NULL, ",");
            if (!token) continue;
            strcpy(dname, token);

            token = strtok(NULL, ",");
            if (!token) continue;
            strcpy(dspec, token);

            strcpy(name, dname);
            strcpy(spec, dspec);

            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

// ----------------------------------------------------------------------
// SHOW DOCTOR SLOTS
// ----------------------------------------------------------------------
void show_doctor_slots()

{
	clear_screen();
    FILE *fp = fopen("doctors_daily_appointment_record.csv", "r");
    if (!fp) { printf("Error: cannot open doctors_daily_appointment_record.csv\n"); return; }

    char line[MAX_LINE];

    while (fgets(line, sizeof(line), fp))
    {
        int values[MAX_COLS];
        int col = 0;
        char *token = strtok(line, ",");
        while (token && col < MAX_COLS) { values[col++] = atoi(token); token = strtok(NULL, ","); }
        if (col < MAX_COLS) continue;

        int doctor_id = values[0];
        char name[200], spec[200];
        if (!get_doctor_info(doctor_id, name, spec)) { strcpy(name, "Unknown"); strcpy(spec, "Unknown"); }

        printf("\n\t\t\t%s%s | %s%s\n", BHYEL, name, spec, CRESET);

        printf("\t\t\t%sAvailable Slots:%s\n", BHMAG, CRESET);
        int any_available = 0;
        for (int i = 1; i <= 12; i++) 
		{
            if (values[i] == 1) 
			{ 
			printf(BHCYN"%sAVAILABLE -> %s%s\n", TAB, hour_labels[i - 1], CRESET);
			 any_available = 1; 
			}
        }
        if (!any_available) printf(BHCYN"%s(No available slots)%s\n", TAB, CRESET);

        printf(BHCYN"\t\t\tBooked Slots:\n"CRESET);
        int any_booked = 0;
        for (int i = 1; i <= 12; i++) {
            if (values[i] > 1) {
			 printf(BHCYN"%sBOOKED   -> %s%s\n", TAB, hour_labels[i - 1], CRESET); 
			any_booked = 1; 
			}
        }
        if (!any_booked) 
		printf(BHCYN"%s(No booked slots)%s\n", TAB, CRESET);
    }

    printf(BHMAG"Press Any Key To Return To Patient Panel");
    getche();
    fclose(fp);
}


//DUA + MINHAL
// ----------------------------------------------------------------------
// VIEW PATIENT BIODATA
// ----------------------------------------------------------------------
void view_patient_biodata(int patient_id)
{
    FILE *fp = fopen("patient_biodata.csv", "r");
    if (!fp) { printf("Error: Could not open patient_biodata.csv\n"); return; }

    char line[512];
    int found = 0;

    while (fgets(line, sizeof(line), fp)) {
        int id, age;
        char full_name[100], f_s_name[100], gender;
        char phone[30], cnic[30], username[50];

        if (sscanf(line, "%d,%99[^,],%99[^,],%c,%d,%29[^,],%29[^,],%49[^\n]",
                   &id, full_name, f_s_name, &gender, &age, phone, cnic, username) == 8) {
            if (id == patient_id) {
                found = 1;
                clear_screen();
                printf(BHRED"\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t================ PATIENT BIODATA ================\n"CRESET);
                printf(BHMAG"\t\t\t\t\t\t\t\t%-20s : %d\n", "Patient ID"CRESET, id);
                printf(BHMAG"\t\t\t\t\t\t\t\t%-20s : %s\n", "Username"CRESET, username);
                printf(BHMAG"\t\t\t\t\t\t\t\t%-20s : %s\n", "Full Name"CRESET, full_name);
                printf(BHMAG"\t\t\t\t\t\t\t\t%-20s : %s\n", "Father/Spouse"CRESET, f_s_name);
                printf(BHMAG"\t\t\t\t\t\t\t\t%-20s : %c\n", "Gender"CRESET, gender);
                printf(BHMAG"\t\t\t\t\t\t\t\t%-20s : %d\n", "Age"CRESET, age);
                printf(BHMAG"\t\t\t\t\t\t\t\t%-20s : %s\n", "Phone Number"CRESET, phone);
                printf(BHMAG"\t\t\t\t\t\t\t\t%-20s : %s\n", "CNIC"CRESET, cnic);
                
                printf(BHRED"\t\t\t\t\t\t\t\t=================================================\n"CRESET);
                printf(BHBLU"\t\t\t\t\t\t\t\tPress Any Key to Go Back\n\t\t\t\t\t\t\t\t"CRESET);
                getche();
                break;
            }
        }
    }

    fclose(fp);
    if (!found) printf("No patient found with ID %d\n", patient_id);
}
//void auto_trim(char *s) {
//    if (!s) return;
//    // left trim
//    char *p = s;
//    while (*p && isspace((unsigned char)*p)) p++;
//    if (p != s) memmove(s, p, strlen(p)+1);
//    // right trim
//    int len = (int)strlen(s);
//    while (len > 0 && isspace((unsigned char)s[len-1])) s[--len] = '\0';
//}



void cancel_patient_appointment(int patient_id)
{
    Doctor doctors[MAX_DOCTORS];
    int total_docs = load_doctors(doctors);

    FILE *fp = fopen("doctors_daily_appointment_record.csv", "r");
    if (!fp) {
        printf("\t\t\t\t\t\t\t\t" BHRED "Schedule file error!\n" CRESET);
        getche();
        return;
    }

    typedef struct { int doc_id; int slot_idx; } Appointment;
    Appointment booked[50];
    int count = 0;

    char *times[MAX_SLOTS] = {
        "09:00-10:00","10:00-11:00","11:00-12:00","12:00-13:00",
        "13:00-14:00","14:00-15:00","15:00-16:00","16:00-17:00",
        "17:00-18:00","18:00-19:00","19:00-20:00","20:00-21:00"
    };

    char line[MAX_LINE];

    // --- Read all booked slots for this patient ---
    while (fgets(line, sizeof(line), fp)) {
        char line_copy[MAX_LINE];
        strcpy(line_copy, line);

        char *token = strtok(line_copy, ",");

        int doc_id = atoi(token);
        int slots[MAX_SLOTS];

        for (int i = 0; i < MAX_SLOTS; i++) {
            token = strtok(NULL, ",");
            slots[i] = token ? atoi(token) : 0;
        }

        for (int i = 0; i < MAX_SLOTS; i++) {
            if (slots[i] == patient_id) {
                booked[count].doc_id = doc_id;
                booked[count].slot_idx = i;
                count++;
            }
        }
    }
    fclose(fp);

    if (count == 0) {
        printf("\n\t\t\t\t\t\t\t\t" BHRED "No appointments found.\n\t\t\t\t\t\t\t\t" CRESET);
        getche();
        return;
    }

    // --- Display booked appointments ---
    printf("\n\t\t\t\t\t\t\t\t" BHYEL "Your booked appointments:\n" CRESET);
    for (int i = 0; i < count; i++) {
        char doc_name[100] = "Unknown";
        for (int j = 0; j < total_docs; j++) {
            if (doctors[j].id == booked[i].doc_id)
                strcpy(doc_name, doctors[j].name);
        }
        printf("\t\t\t\t\t\t\t\t" BHCYN "[%c] " CRESET "Dr. %s at %s\n",
               'A' + i, doc_name, times[booked[i].slot_idx]);
    }

    // --- Select appointment to cancel ---
printf("\t\t\t\t\t\t\t\t" BHCYN "Choose appointment to cancel: " CRESET);
char choice;
choice = getche();

// Convert to uppercase to make selection case-insensitive
if (choice >= 'a' && choice <= 'z') choice = choice - 'a' + 'A';

int sel = choice - 'A';
if (sel < 0 || sel >= count) {
    printf("\t\t\t\t\t\t\t\t" BHRED "Invalid choice!\n" CRESET);
    getche();
    return;
}
    

    // --- Update CSV safely using temp file ---
    FILE *f_orig = fopen("doctors_daily_appointment_record.csv", "r");
    FILE *f_temp = fopen("temp.csv", "w");
    if (!f_orig || !f_temp) {
        printf("\t\t\t\t\t\t\t\t" BHRED "File error!\n" CRESET);
        if(f_orig) fclose(f_orig);
        if(f_temp) fclose(f_temp);
        return;
    }

    while (fgets(line, sizeof(line), f_orig)) {
        char line_copy[MAX_LINE];
        strcpy(line_copy, line);

        char *saveptr;
        char *token = strtok_r(line_copy, ",", &saveptr);
        int doc_id = atoi(token);
        int slots[MAX_SLOTS];

        for (int i = 0; i < MAX_SLOTS; i++) {
            token = strtok_r(NULL, ",", &saveptr);
            slots[i] = token ? atoi(token) : 0;
        }

        if (doc_id == booked[sel].doc_id)
            slots[booked[sel].slot_idx] = 1;  // mark as available

        fprintf(f_temp, "%d", doc_id);
        for (int i = 0; i < MAX_SLOTS; i++)
            fprintf(f_temp, ",%d", slots[i]);
        fprintf(f_temp, "\n");
    }

    fclose(f_orig);
    fclose(f_temp);

    remove("doctors_daily_appointment_record.csv");
    rename("temp.csv", "doctors_daily_appointment_record.csv");

    printf("\n\t\t\t\t\t\t\t\t" BHGRN "Appointment canceled successfully.\n" CRESET);
    getche();
}

#define DOCTORS_CSV "doctors_list_sp,nm,id.csv"

int load_doctors_for_appointment(Doctor doctors[])
 {
    FILE *f = fopen(DOCTORS_CSV, "r");
    if (!f) 
	return 0;

    char line[256];
    int count = 0;

    while (fgets(line, sizeof(line), f) && count < MAX_DOCTORS) 
	{
        // Trim newline
        size_t ln = strlen(line);
        if (ln && (line[ln-1] == '\n'))
            line[ln-1] = '\0';

        // Skip empty lines
//        char *p = line;
//        while (*p && isspace((unsigned char)*p))
//		 p++;
//        if (*p == '\0')
//		 continue;

        // If CSV has header like "id,name,specialization", skip header detection:
        // naive header check: if the line contains non-digit at start and contains letters "name" etc.
        // Better: attempt to parse numeric id first; if it fails, skip header.
        int id;
        char *save = NULL;
        char *token = strtok_r(line, ",", &save);
        if (!token) continue;
        // try parse id
        char *endptr;
        id = (int)strtol(token, &endptr, 10);
        if (endptr == token)
		 {
            // first token not number -> maybe header; try to parse as "name, specialization" style
            // We'll treat token as name and try next token as specialization
            // Reset tokenizer on original (re-scan from line start)
            // Simple fallback: skip line (header) so we don't mis-fill index 0
            continue;
        }

        // now token was id, parse next tokens
        
        token = strtok_r(NULL, ",", &save); // name
        if (!token)
		 continue;
		 
        char namebuf[64];
        
		 strncpy(namebuf, token, sizeof(namebuf));
		
		  namebuf[sizeof(namebuf)-1]=0;
		  
		  
        token = strtok_r(NULL, ",", &save); // specialization (optional)
        
        char specbuf[64] = {0};
        
        if (token)
		 	{ 
		 strncpy(specbuf, token, sizeof(specbuf));
		  specbuf[sizeof(specbuf)-1]=0;
		  }

        // store into doctors[count]
        doctors[count].id = id;
        // trim leading/trailing spaces
        // simple trim helper:

        strncpy(doctors[count].name, namebuf, sizeof(doctors[count].name));
        
        doctors[count].name[sizeof(doctors[count].name)-1] = '\0';
        
        strncpy(doctors[count].spec, specbuf, sizeof(doctors[count].spec));
        
        doctors[count].spec[sizeof(doctors[count].spec)-1] = '\0';
        
        //doctors[count].available = 1; // default

        count++;
    }

    fclose(f);
    return count;
}

void book_patient_appointment(int patient_id)
 {
    Doctor doctors[MAX_DOCTORS];
    int total_docs = load_doctors_for_appointment(doctors);
    
	clear_screen();
    if (total_docs <= 0)
	 {
        printf(TAB BHCYN "No doctors found!\n" CRESET);
        return;
    }

    printf(BHCYN"\n\n\n\n\n"TAB"Select a doctor to book:\n"CRESET);

    int displayed = 0;
    for (int i = 0; i < total_docs; ++i) 
	{
        if (doctors[i].name[0] == '\0')
		 continue;
        printf( BHRED TAB "[%c] %s (%s)\n"CRESET, 'A'+displayed, doctors[i].name, doctors[i].spec);
        displayed++;

    }


    if (displayed == 0)
	 {
        printf(TAB BHCYN "No valid doctor entries to show.\n" CRESET);
        return;
    }

    printf(TAB BHMAG "Enter choice: "CRESET);

   char choice = toupper(getche());

   
    int selection_index = -1;
    
    if (choice >= 'A' && choice < 'A'+displayed)
	 selection_index = choice-'A';
	
    else { 
	printf(BHMAG"\n"TAB "Invalid choice.\n"CRESET);
	 return;
	  }

    int doctor_id = doctors[selection_index].id;

    // --- Load doctor slots for the day ---
    FILE *fp = fopen("doctors_daily_appointment_record.csv", "r");
    if (!fp)
	 { 
	 printf(TAB "Cannot open schedule file!\n");
	  return; 
	  }

    char line[256];
    int slots[MAX_SLOTS];
    int found = 0;

    while (fgets(line, sizeof(line), fp)) 
	{
        char *ptr = line;
        int id = atoi(strtok(ptr, ","));
        if (id == doctor_id)
		 {
            for (int i = 0; i < MAX_SLOTS; i++) 
			{
                char *token = strtok(NULL, ",");
                slots[i] = token ? atoi(token) : 0;
            }
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found) { printf(TAB "Doctor schedule not found.\n");
	getche(); return; }

    // --- Display available slots ---
    
    printf("\n"TAB "Available slots for %s:\n", doctors[selection_index].name);
    int slot_letters[MAX_SLOTS], available_count = 0;
    for (int i = 0; i < MAX_SLOTS; i++)
	 {
        if (slots[i] == 1) { // available
            printf(TAB "[%c] %02d:00-%02d:00\n", 'A'+available_count, 9+i, 10+i);
            slot_letters[available_count++] = i;
        }
    }

    if (available_count == 0) 
	{
        printf(TAB "No slots available.\n");
        getche();
        return;
    }

    printf(TAB "Enter slot choice: ");
      int slot_index = -1;
    char slot_choice = toupper(getche());
    
    if (slot_choice >= 'A' && slot_choice < 'A'+available_count) 
	slot_index = slot_letters[slot_choice-'A'];
    
    else 
	{ 
	printf(TAB "Invalid slot choice.\n");
	getche();
	 return;
	 }

    // --- Update CSV via temp file ---
    FILE *f_orig = fopen("doctors_daily_appointment_record.csv","r");
    FILE *f_temp = fopen("temp.csv","w");
    if (!f_orig || !f_temp) { printf(TAB "File error!\n");
	getche(); return; }

    while (fgets(line,sizeof(line),f_orig))
	 {
        char *ptr = strdup(line); // strdup creates duplicate for a string (duplicate for strtok)
        int id = atoi(strtok(ptr, ",")); // atoi = ASCII TO INTEGER
       
	    if (id == doctor_id) 
		{
            fprintf(f_temp,"%d",doctor_id);
            for (int i=0;i<MAX_SLOTS;i++) //MAX_SLOTS = 12 FOR 12 HOURS OF OUR BELOVED SCHEDULE
			 {
                if (i==slot_index) 
				fprintf(f_temp,",%d",patient_id);
                else {
                    char *token = strtok(NULL,",");
                    int val = token ? atoi(token) : 0;
                    fprintf(f_temp,",%d",val);
                }
            }
            fprintf(f_temp,"\n");
            
        } else
		 {
            fputs(line,f_temp);
        }
        free(ptr);
    }

    fclose(f_orig);
    fclose(f_temp);

    remove("doctors_daily_appointment_record.csv");
    rename("temp.csv","doctors_daily_appointment_record.csv");

    printf(TAB BHMAG "Appointment booked successfully!\n" CRESET);
    getche();
}


 



