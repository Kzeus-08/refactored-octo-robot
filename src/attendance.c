#include "attendance.h"

#include <stdio.h>
#include <string.h>

void init_attendance_list(AttendanceList *list) {
    if (list == NULL) {
        return;
    }
    list->size = 0;
}

int add_record(AttendanceList *list, int id, const char *name, int total_classes, int attended_classes) {
    size_t i;

    if (list == NULL || name == NULL || list->size >= MAX_RECORDS) {
        return 0;
    }
    if (total_classes < 0 || attended_classes < 0 || attended_classes > total_classes) {
        return 0;
    }

    for (i = 0; i < list->size; ++i) {
        if (list->records[i].id == id) {
            return 0;
        }
    }

    list->records[list->size].id = id;
    strncpy(list->records[list->size].name, name, MAX_NAME_LEN - 1);
    list->records[list->size].name[MAX_NAME_LEN - 1] = '\0';
    list->records[list->size].total_classes = total_classes;
    list->records[list->size].attended_classes = attended_classes;
    list->size++;
    return 1;
}

int remove_record(AttendanceList *list, int id) {
    size_t i;

    if (list == NULL) {
        return 0;
    }

    for (i = 0; i < list->size; ++i) {
        if (list->records[i].id == id) {
            size_t j;
            for (j = i; j + 1 < list->size; ++j) {
                list->records[j] = list->records[j + 1];
            }
            list->size--;
            return 1;
        }
    }
    return 0;
}

void list_records(const AttendanceList *list) {
    size_t i;

    if (list == NULL || list->size == 0) {
        printf("No attendance records available.\n");
        return;
    }

    printf("\nID\tName\t\tAttended/Total\n");
    printf("----------------------------------------\n");
    for (i = 0; i < list->size; ++i) {
        printf("%d\t%-16s %d/%d\n",
               list->records[i].id,
               list->records[i].name,
               list->records[i].attended_classes,
               list->records[i].total_classes);
    }
}
