#ifndef PATIENT_PANEL_H
#define PATIENT_PANEL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ANSI-color-codes.h"
#include "structures.h"
#include "utility_functions.h"

#define MAX_COLS 13
#define MAX_LINE 300
#define TAB "\t\t\t\t\t\t\t\t"



extern const char *hour_labels[12];

// ----------------------------------------------------------------------
// PATIENT PANEL MENU
// ----------------------------------------------------------------------
void patient_panel_menu(int patient_id);

// ----------------------------------------------------------------------
// VIEW DOCTORS LIST
// ----------------------------------------------------------------------
void view_doctors_list(void);

// ----------------------------------------------------------------------
// VIEW DOCTOR SLOTS (Available & Booked)
// ----------------------------------------------------------------------
void show_doctor_slots(void);

// ----------------------------------------------------------------------
// CHANGE PATIENT LOGIN CREDENTIALS
// ----------------------------------------------------------------------
void change_patient_login_credentials(int patient_id);

// ----------------------------------------------------------------------
// VIEW PATIENT BIODATA
// ----------------------------------------------------------------------
void view_patient_biodata(int patient_id);

// ----------------------------------------------------------------------
// BOOK / CANCEL APPOINTMENT
// ----------------------------------------------------------------------
void book_patient_appointment(int patient_id);
void cancel_patient_appointment(int patient_id);

// ----------------------------------------------------------------------
// FETCH DOCTOR INFO (NAME + SPECIALIZATION)
// ----------------------------------------------------------------------
int get_doctor_info(int doctor_id, char *name, char *spec);

#endif // PATIENT_PANEL_H
