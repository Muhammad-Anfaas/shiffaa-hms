# Shiffaa Hospital Management System

A Windows console application written in C for patient registration, appointment scheduling, and basic hospital administration. It stores its records in CSV files.

## Features

### Patient portal

- Register with a username, password, and biodata.
- Log in to a patient account.
- View patient biodata and the doctors list.
- View doctors’ appointment availability.
- Book an available appointment slot or cancel an existing one.

### Admin portal

- Log in with the configured admin credentials.
- View doctors and their schedules, and change slot availability.
- List patients and search by patient ID or username.
- List allied staff, mark a position vacant, or fill a vacant position.
- Change the admin username or password.
- Reset booked appointment slots to available.

## Requirements

- Windows console environment.
- Embarcadero Dev-C++ with its bundled TDM-GCC toolchain, as configured by the included `Makefile.win`.

The program uses Windows console functions such as `getche()` and `Sleep()`. The supplied build file also contains machine-specific Dev-C++ paths, so it may need adjustment on another computer. A portable Linux or macOS build is not documented or established by the repository.

## Build and run

1. Open `HMS.dev` in Embarcadero Dev-C++.
2. Build the project with the IDE.
3. Run `HMS.exe` from the project directory.

The application reads and writes CSV files using relative paths, so launch it with the project directory as its working directory. The repository includes doctor, schedule, allied staff, and admin credential CSV files. Patient account and biodata files are created during registration if they do not already exist.

## Data files

| File | Purpose |
| --- | --- |
| `admin_login_credentials.csv` | Admin username and stored password value |
| `doctors_list_sp,nm,id.csv` | Doctor IDs, names, and specializations |
| `doctors_daily_appointment_record.csv` | Doctor appointment slots |
| `allied_staff_list.csv` | Allied staff positions and names |
| `patient_login_credentials.csv` | Patient login records; created during registration |
| `patient_biodata.csv` | Patient biodata; created during registration |

Appointment records contain a doctor ID followed by 12 slot values, corresponding to hourly slots from 09:00–10:00 through 20:00–21:00. In the current code, `0` means unavailable, `1` means available, and a value greater than `1` represents a booked slot containing a patient ID.

Keep the CSV files in the application’s working directory. They contain account and personal data.

## Project structure

- `main.c` — application entry point and welcome screen
- `patient_portal_sign_up.c` — patient registration and login
- `patient_panel.c` — patient menu, biodata, doctors, and appointment operations
- `admin_portal.c` — admin login and administration menus
- `admin_doctors_panel.c` — doctor list and schedule management
- `admin_patients_panel.c` — patient listing and search
- `admin_allied_panel.c` — allied staff listing and position updates
- `admin_settings_panel.c` — admin credential changes and appointment reset
- `utility_functions.c` — input, display, and CSV-loading helpers
- `structures.c`, `structures.h` — shared data structures
- `ANSI-color-codes.h` — console color definitions
- `Makefile.win`, `HMS.dev`, `HMS.layout` — Dev-C++ project and build files

## Security and data limitations

This is a small local console project, not a production hospital system. Passwords are transformed with a simple unsalted integer hash; this is not a secure password-storage method. Records are stored in editable CSV files, and the application handles personal information such as phone numbers and CNICs. Do not use real patient data or rely on this software for clinical, operational, or regulatory needs.

## License

The repository includes a public-domain notice in `ANSI-color-codes.h`. No repository-wide license file was present when this README was prepared. Confirm the intended project license before distributing or reusing the complete project.
