#ifndef STRUCTURES_H
#define STRUCTURES_H

//Defining MACROS for Code Maintainability and Reducing Redundancy
#define MAX_LENGTH 1000

//Defining a structure to hold information about patients,doctors and admin
typedef struct 
{
    int patient_id;
    char full_name[MAX_LENGTH];
    char F_S_name[MAX_LENGTH];
    char gender;
    int age;
    char phone_number[20];
	char cnic[20];
    char address[MAX_LENGTH];
} patient_biodata;

typedef struct
{
    char username[MAX_LENGTH];
    unsigned long long password;
    int patient_id;
}patient_login_credentials;

typedef struct
{
    char username[MAX_LENGTH];
    char password[MAX_LENGTH];
} admin_login;

#define TAB "\t\t\t\t\t\t\t\t"
#define MAX_PATIENTS 2000
#define MAX_DOCTORS 200
#define MAX_SLOTS 12 
// Patient structure
typedef struct {
    int id;
    char full_name[50];
    char F_S_name[50];
    char gender;      
    int age;
    char phone_number[20];
    char cnic[20];
    char username[30];     
} Patient;

// Doctor structure
typedef struct {
    int id;
    char name[100];
    char spec[100];
    int available; // optional
} Doctor;


extern char h_line[200];



#endif

