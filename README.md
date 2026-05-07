# refactored-octo-robot

This repository is now a **C demo project** for student attendance management.

## Features

- Add a student attendance record
- Remove a record by ID
- List all records with attendance percentage
- Search records by student ID
- Update attendance values
- Sort records by name
- Sort records by attendance percentage
- Save records to CSV
- Load records from CSV

## Project Structure

```
.
├── Makefile
├── README.md
├── docs/
│   └── branching_workflow.md
└── src/
    ├── attendance.c
    ├── attendance.h
    └── main.c
```

## Build and Run

From the repository root:

```bash
make
./attendance_demo
```

## Menu Options

When the app runs, choose from:

1. Add record
2. Remove record
3. List records
4. Search record by ID
5. Update record
6. Sort by name
7. Sort by attendance percentage
8. Save to file (`attendance_data.csv`)
9. Load from file (`attendance_data.csv`)
0. Exit

## Notes

- Source code is modular and documented with inline comments.
- Input validation is included for invalid totals, duplicate IDs, and malformed input.
- A sample run transcript is available at `docs/demo_session.txt`.
