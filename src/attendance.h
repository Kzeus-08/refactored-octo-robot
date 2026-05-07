#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#include <stddef.h>

#define MAX_NAME_LEN 100
#define MAX_RECORDS 1000

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    int total_classes;
    int attended_classes;
} AttendanceRecord;

typedef struct {
    AttendanceRecord records[MAX_RECORDS];
    size_t size;
} AttendanceList;

/* Initializes an attendance list before use. */
void init_attendance_list(AttendanceList *list);

/* Adds a new record if values are valid and ID is unique. */
int add_record(AttendanceList *list, int id, const char *name, int total_classes, int attended_classes);

/* Removes one record by ID. Returns 1 on success, 0 if not found. */
int remove_record(AttendanceList *list, int id);

/* Finds a mutable record by ID. Returns NULL when not found. */
AttendanceRecord *find_record_by_id(AttendanceList *list, int id);

/* Finds a const record by ID. Returns NULL when not found. */
const AttendanceRecord *find_record_by_id_const(const AttendanceList *list, int id);

/* Updates total and attended values for an existing ID. */
int update_record(AttendanceList *list, int id, int total_classes, int attended_classes);

/* Sorts records in ascending name order. */
void sort_records_by_name(AttendanceList *list);

/* Sorts by attendance percentage (descending != 0 means highest first). */
void sort_records_by_attendance_percent(AttendanceList *list, int descending);

/* Calculates percentage attendance for one record. */
float attendance_percentage(const AttendanceRecord *record);

/* Saves all records to a CSV file path. */
int save_records_to_file(const AttendanceList *list, const char *file_path);

/* Loads records from a CSV file path into the list. */
int load_records_from_file(AttendanceList *list, const char *file_path);

/* Prints a tabular list of all records. */
void list_records(const AttendanceList *list);

#endif
