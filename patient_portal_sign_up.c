#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
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
#include <conio.h>
#include<windows.h>

/////////////////////////////////////////////////////////////////////////////////////////////////
void patient_portal(void)
{

while (1) // Infinite loop to keep the patient portal running
{
    clear_screen();

    printf(BHRED"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\tWelcome To Patient Portal\n"CRESET);
    printf(BHRED"%s\n"CRESET, h_line);

    printf(BHBLU"\n\t\t\t\t\t\t\t\tPlease Select an appropriate option\n\n"CRESET);
    printf(BHBLU"\t\t\t\t\t\t\t\t1) Patient Login\n"CRESET);
    printf(BHBLU"\t\t\t\t\t\t\t\t2) New Patient Registration\n"CRESET);
    printf(BHBLU"\t\t\t\t\t\t\t\t3) Go Back to Welcome Screen\n"CRESET);
    printf(BHBLU"\t\t\t\t\t\t\t\t4) Exit Application\n\n"CRESET);

    printf(BHRED"%s\n"CRESET, h_line);
    printf(BHGRN"\t\t\t\t\t\t\t\tPlease Enter Your Choice: "CRESET);

  char   patient_p_choice = getche();

    switch (patient_p_choice)
    {
        case '1':
            printf(BHBLU"\n\t\t\t\t\t\t\t\tLoading Patient Login ["CRESET);
            for (int i = 0; i < 10; i++)
            {
                Sleep(80);
                printf(BHBLU"#"CRESET);
            }
            printf(BHBLU"]"CRESET);
            Sleep(200);
            patient_login();
            break;

        case '2':
            printf(BHBLU"\n\t\t\t\t\t\t\t\tLoading Patient Registration ["CRESET);
            for (int i = 0; i < 10; i++)
            {
                Sleep(80);
                printf(BHBLU"#"CRESET);
            }
            printf(BHBLU"]"CRESET);
            Sleep(200);
            patient_registration();
            break;

        case '3':
            return; // Return control to the front_screen() function

        case '4':
            clear_screen();
            printf(BHRED"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\tGood Bye!\n"CRESET);
            exit(0); // Exiting the program

        default:
            printf(BHMAG"\n\t\t\t\t\t\t\t\tInvalid choice!\n\t\t\t\t\t\t\t\tPress Any Key to try again..."CRESET);
            getch(); // Wait for key press before continuing
            break;
    }
}
}

void patient_registration(void)
{
clear_screen();
    patient_biodata p_bio;
    patient_login_credentials p_cred;
    FILE *f_plc = fopen("patient_login_credentials.csv", "a+"); // open for append+read
            // append mode
    if (f_plc == NULL) 
    {
        printf("Error opening file!\n");
        printf("Press Any Key to return to Patient Portal...");
        getche();
        return;
    }

printf(BHRED"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\tWelcome Dear Patient!! To Onboard You\n"CRESET);
printf(BHBLU"\t\t\t\t\t\t\t\tPlease Provide Us with Your Credentials\n"CRESET);
  printf(BHRED"%s"CRESET,h_line);
  
    //Patient IDs Start from 100000
    // ------------------ Generate new patient ID ------------------
    int last_id = 99999; // default if file empty
    char line[512];

    rewind(f_plc);
    while (fgets(line, sizeof(line), f_plc))
    {
        int temp_id;
        sscanf(line, "%d", &temp_id);
        if (temp_id > last_id)
            last_id = temp_id;
    }
    int new_id = last_id + 1;
    p_cred.patient_id = new_id;

    //  username
    while (1){
    	printf("\n");
        string_input_function(p_cred.username, BHMAG, "username");
    
        int exists = 0;
        rewind(f_plc);
        while (fgets(line, sizeof(line), f_plc))
        {
            char existing_user[MAX_LENGTH];
            sscanf(line, "%*d,%[^,]", existing_user);
            if (strcmp(existing_user, p_cred.username) == 0){
                exists = 1;
                break; }
        }
        if (exists)
        {
		
            printf(BHMAG"\t\t\t\t\t\t\t\tUsername already exists! Please choose another.\n"CRESET);
            printf(BHMAG"\t\t\t\t\t\t\t\tPress Any Key to Continue\n\t\t\t\t\t\t\t\t");
            getche();
        }
        else break; 
		}
    //pswrd
    char typed_password[MAX_LENGTH] = "password";
		string_input_function(typed_password, BHMAG, "Password");
	    p_cred.password = simple_hash(typed_password);
    fclose(f_plc);
    
    // get biodata
    printf(BHBLU"\t\t\t\t\t\t\t\tPlease Provide Your Biodata\n"CRESET);

	string_input_function(p_bio.full_name, BHMAG, "Full Name");
	string_input_function(p_bio.F_S_name, BHMAG, "Father/Spouse Name");
	p_bio.gender = getGender();
 	p_bio.age = getIntInRange("\t\tAge: ", 1, 120);
		string_input_limited(p_bio.phone_number,12,BHMAG, "Phone Number (03000000000)");
	string_input_limited(p_bio.cnic,14,BHMAG, "CNIC (13 digits, without dashes)");
	string_input_function(p_bio.address, BHMAG, "Address");
	FILE *f_plcs = fopen("patient_login_credentials.csv", "a+"); // open for append+read
            // append mode
    if (f_plcs == NULL)
    {
        printf("Error opening file!\n");
        printf("Press Enter to return to Patient Portal...");
        getche();
        return;
    }
     fprintf(f_plcs, "%d,%s,%llu\n", new_id, p_cred.username, p_cred.password);
    fclose(f_plcs);
FILE *f_pbd = fopen("patient_biodata.csv","a");
if (f_pbd == NULL)
{
    printf("Error opening patient_biodata.csv!\n");
    printf("Press Enter to continue...");
    getchar();
    return;
} 
    // ------------------ Save biodata ------------------
fprintf(f_pbd, "%d,%s,%s,%c,%d,%s,%s,%s\n",
        new_id,
        p_bio.full_name,
        p_bio.F_S_name,
        p_bio.gender,
        p_bio.age,
        p_bio.phone_number, 
        p_bio.cnic,           
        p_cred.username);


    fclose(f_pbd);

printf(BHMAG"\n\t\t\t\t\t\t\t\tPatient registered successfully!\n\t\t\t\t\t\t\t\tYour ID is: %d\n"CRESET, new_id);

    printf(BHMAG"\t\t\t\t\t\t\t\tPress Any Key to continue..."CRESET);
    getche();
}
char getGender() 
{
    char ch;
    while (1) {
        printf(BHMAG"\t\t\t\t\t\t\t\tGender (M/F): "CRESET);
//          int c;
//        while ((c = getchar()) != '\n' && c != EOF);
        ch = getche();
		printf("\n");
        // Flush leftover input
      

        ch = toupper(ch); // convert to uppercase

        if (ch == 'M' || ch == 'F') {
            return ch; // valid input
        }
        printf(BHMAG"\n\t\t\t\t\t\t\t\tInvalid input! Please enter M or F.\n"CRESET);
    }
}

void patient_login(void)
{
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
    int logging_in_id;

    while (1) 
    {
  clear_screen();
   printf(BHRED"\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\tWelcome To Patient Login Portal\n"CRESET);
  printf(BHRED"%s\n"CRESET,h_line);
        string_input_function(username, BHMAG, "username");
        string_input_function(password, BHMAG, "password");
        unsigned long long hashed_password = simple_hash(password);
        FILE *f_plc = fopen("patient_login_credentials.csv", "r");
        if (f_plc == NULL)
        {
            printf("Error opening file!\n");
            printf("Press Enter to return to Patient Portal...");
            getchar();
            return;
        }
        char line[512];
        int login_successful = 0;
        while (fgets(line, sizeof(line), f_plc))
        {
            int temp_id;
            char existing_user[MAX_LENGTH];
            unsigned long long existing_hashed_password;
            //%s stops at whitespaces, thats why we use %[^,]
            sscanf(line, "%d,%[^,],%llu", &temp_id, existing_user, &existing_hashed_password);
            if (strcmp(existing_user, username) == 0 && (existing_hashed_password == hashed_password))
            {
                login_successful = 1;
                logging_in_id = temp_id;
                break; // exit loop on successful login
            }
            else
            {
                continue;
            } 
        }
  
 
        fclose(f_plc);
        if(login_successful)
        {
           printf(BHGRN"\n\n\t\t\t\t\t\t\t\tLogin Successful!\n"CRESET);
printf(BHGRN"\t\t\t\t\t\t\t\tWelcome Dear %s\n"CRESET, username);
printf(BHGRN"\t\t\t\t\t\t\t\tPress Any Key to continue..."CRESET);
            getche();
            patient_panel_menu(logging_in_id); //Calling Patient Panel Function
        }
        else
        {
            printf(BHRED"\n\n\t\t\t\t\t\t\t\tInvalid credentials!\n"CRESET);
printf(BHRED"\t\t\t\t\t\t\t\tPress Any Key to go back to Welcome Screen..."CRESET);
            getche();
                return; // return to welcome screen
            

        }
    }
}

