#include "attendance.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Initializes the list before first use. */
void init_attendance_list(AttendanceList *list) {
    if (list == NULL) {
        return;
    }
    list->size = 0;
}

/* Adds a single student attendance record if the input is valid. */
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

/* Removes a record by id by shifting remaining items left. */
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

/* Finds a mutable record pointer for a student id. */
AttendanceRecord *find_record_by_id(AttendanceList *list, int id) {
    size_t i;

    if (list == NULL) {
        return NULL;
    }

    for (i = 0; i < list->size; ++i) {
        if (list->records[i].id == id) {
            return &list->records[i];
        }
    }
    return NULL;
}

/* Finds a read-only record pointer for a student id. */
const AttendanceRecord *find_record_by_id_const(const AttendanceList *list, int id) {
    size_t i;

    if (list == NULL) {
        return NULL;
    }

    for (i = 0; i < list->size; ++i) {
        if (list->records[i].id == id) {
            return &list->records[i];
        }
    }
    return NULL;
}

/* Updates attendance totals for an existing student id. */
int update_record(AttendanceList *list, int id, int total_classes, int attended_classes) {
    AttendanceRecord *record = find_record_by_id(list, id);

    if (record == NULL || total_classes < 0 || attended_classes < 0 || attended_classes > total_classes) {
        return 0;
    }

    record->total_classes = total_classes;
    record->attended_classes = attended_classes;
    return 1;
}

float attendance_percentage(const AttendanceRecord *record) {
    if (record == NULL || record->total_classes == 0) {
        return 0.0f;
    }
    return (record->attended_classes * 100.0f) / (float) record->total_classes;
}

static int compare_names(const char *a, const char *b) {
    size_t i = 0;
    char ca;
    char cb;

    while (a[i] != '\0' && b[i] != '\0') {
        ca = (char) tolower((unsigned char) a[i]);
        cb = (char) tolower((unsigned char) b[i]);
        if (ca != cb) {
            return (int) (unsigned char) ca - (int) (unsigned char) cb;
        }
        ++i;
    }
    return (int) (unsigned char) a[i] - (int) (unsigned char) b[i];
}

/* Sorts records alphabetically by student name using bubble sort for clarity. */
void sort_records_by_name(AttendanceList *list) {
    size_t i;
    size_t j;

    if (list == NULL || list->size < 2) {
        return;
    }

    for (i = 0; i < list->size - 1; ++i) {
        for (j = 0; j < list->size - 1 - i; ++j) {
            if (compare_names(list->records[j].name, list->records[j + 1].name) > 0) {
                AttendanceRecord tmp = list->records[j];
                list->records[j] = list->records[j + 1];
                list->records[j + 1] = tmp;
            }
        }
    }
}

/* Sorts by percentage, ascending or descending according to flag. */
void sort_records_by_attendance_percent(AttendanceList *list, int descending) {
    size_t i;
    size_t j;

    if (list == NULL || list->size < 2) {
        return;
    }

    for (i = 0; i < list->size - 1; ++i) {
        for (j = 0; j < list->size - 1 - i; ++j) {
            float left = attendance_percentage(&list->records[j]);
            float right = attendance_percentage(&list->records[j + 1]);
            int should_swap = descending ? (left < right) : (left > right);
            if (should_swap) {
                AttendanceRecord tmp = list->records[j];
                list->records[j] = list->records[j + 1];
                list->records[j + 1] = tmp;
            }
        }
    }
}

/* Saves current list into a simple CSV file. */
int save_records_to_file(const AttendanceList *list, const char *file_path) {
    FILE *fp;
    size_t i;

    if (list == NULL || file_path == NULL) {
        return 0;
    }

    fp = fopen(file_path, "w");
    if (fp == NULL) {
        return 0;
    }

    for (i = 0; i < list->size; ++i) {
        if (fprintf(fp, "%d,%s,%d,%d\n",
                    list->records[i].id,
                    list->records[i].name,
                    list->records[i].total_classes,
                    list->records[i].attended_classes) < 0) {
            fclose(fp);
            return 0;
        }
    }

    fclose(fp);
    return 1;
}

/* Loads records from CSV and replaces current in-memory records. */
int load_records_from_file(AttendanceList *list, const char *file_path) {
    FILE *fp;
    char line[256];
    AttendanceList new_list;

    if (list == NULL || file_path == NULL) {
        return 0;
    }

    fp = fopen(file_path, "r");
    if (fp == NULL) {
        return 0;
    }

    init_attendance_list(&new_list);

    while (fgets(line, sizeof(line), fp) != NULL) {
        int id;
        int total_classes;
        int attended_classes;
        char name[MAX_NAME_LEN];

        if (sscanf(line, "%d,%99[^,],%d,%d", &id, name, &total_classes, &attended_classes) == 4) {
            if (!add_record(&new_list, id, name, total_classes, attended_classes)) {
                fclose(fp);
                return 0;
            }
        }
    }

    fclose(fp);
    *list = new_list;
    return 1;
}

void list_records(const AttendanceList *list) {
    size_t i;

    if (list == NULL || list->size == 0) {
        printf("No attendance records available.\n");
        return;
    }

    printf("\nID\tName\t\tAttended/Total\tPercent\n");
    printf("--------------------------------------------------------\n");
    for (i = 0; i < list->size; ++i) {
        printf("%d\t%-16s %d/%d\t\t%.2f%%\n",
               list->records[i].id,
               list->records[i].name,
               list->records[i].attended_classes,
               list->records[i].total_classes,
               attendance_percentage(&list->records[i]));
    }
}
