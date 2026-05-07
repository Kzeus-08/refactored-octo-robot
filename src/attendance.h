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
void list_records(const AttendanceList *list);

#endif
