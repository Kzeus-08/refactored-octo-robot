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

void init_attendance_list(AttendanceList *list);
int add_record(AttendanceList *list, int id, const char *name, int total_classes, int attended_classes);
int remove_record(AttendanceList *list, int id);
AttendanceRecord *find_record_by_id(AttendanceList *list, int id);
const AttendanceRecord *find_record_by_id_const(const AttendanceList *list, int id);
int update_record(AttendanceList *list, int id, int total_classes, int attended_classes);
void sort_records_by_name(AttendanceList *list);
void sort_records_by_attendance_percent(AttendanceList *list, int descending);
float attendance_percentage(const AttendanceRecord *record);
int save_records_to_file(const AttendanceList *list, const char *file_path);
int load_records_from_file(AttendanceList *list, const char *file_path);
void list_records(const AttendanceList *list);

#endif
