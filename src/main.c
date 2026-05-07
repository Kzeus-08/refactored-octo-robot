#include "attendance.h"

#include <stdio.h>
#include <string.h>

static int read_int(const char *prompt, int *out) {
    int value;
    char buffer[64];

    if (prompt != NULL) {
        printf("%s", prompt);
    }

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }
    if (sscanf(buffer, "%d", &value) != 1) {
        return 0;
    }
    *out = value;
    return 1;
}

static int read_name(const char *prompt, char *name, size_t name_len) {
    if (prompt != NULL) {
        printf("%s", prompt);
    }
    if (fgets(name, (int) name_len, stdin) == NULL) {
        return 0;
    }

    name[strcspn(name, "\n")] = '\0';
    return name[0] != '\0';
}

static void print_menu(void) {
    printf("\n==== Attendance Management Menu ====\n");
    printf("1. Add record\n");
    printf("2. Remove record\n");
    printf("3. List records\n");
    printf("4. Search record by ID\n");
    printf("5. Update record\n");
    printf("6. Sort by name\n");
    printf("7. Sort by attendance percentage (high to low)\n");
    printf("8. Save to file\n");
    printf("9. Load from file\n");
    printf("0. Exit\n");
}

int main(void) {
    AttendanceList list;
    int running = 1;

    init_attendance_list(&list);

    while (running) {
        int choice;
        print_menu();

        if (!read_int("Choose an option: ", &choice)) {
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        switch (choice) {
            case 1: {
                int id;
                int total;
                int attended;
                char name[MAX_NAME_LEN];
                if (!read_int("Enter ID: ", &id) ||
                    !read_name("Enter name: ", name, sizeof(name)) ||
                    !read_int("Enter total classes: ", &total) ||
                    !read_int("Enter attended classes: ", &attended)) {
                    printf("Invalid input. Record was not added.\n");
                    break;
                }

                if (add_record(&list, id, name, total, attended)) {
                    printf("Record added successfully.\n");
                } else {
                    printf("Failed to add record. Check duplicate ID and values.\n");
                }
                break;
            }
            case 2: {
                int id;
                if (!read_int("Enter ID to remove: ", &id)) {
                    printf("Invalid input.\n");
                    break;
                }
                printf(remove_record(&list, id) ? "Record removed.\n" : "Record not found.\n");
                break;
            }
            case 3:
                list_records(&list);
                break;
            case 4: {
                int id;
                const AttendanceRecord *record;
                if (!read_int("Enter ID to search: ", &id)) {
                    printf("Invalid input.\n");
                    break;
                }
                record = find_record_by_id_const(&list, id);
                if (record == NULL) {
                    printf("Record not found.\n");
                } else {
                    printf("Found: %d | %s | %d/%d | %.2f%%\n",
                           record->id,
                           record->name,
                           record->attended_classes,
                           record->total_classes,
                           attendance_percentage(record));
                }
                break;
            }
            case 5: {
                int id;
                int total;
                int attended;
                if (!read_int("Enter ID to update: ", &id) ||
                    !read_int("Enter new total classes: ", &total) ||
                    !read_int("Enter new attended classes: ", &attended)) {
                    printf("Invalid input.\n");
                    break;
                }
                printf(update_record(&list, id, total, attended) ? "Record updated.\n" : "Update failed.\n");
                break;
            }
            case 6:
                sort_records_by_name(&list);
                printf("Records sorted by name.\n");
                break;
            case 7:
                sort_records_by_attendance_percent(&list, 1);
                printf("Records sorted by attendance percentage.\n");
                break;
            case 8:
                if (save_records_to_file(&list, "attendance_data.csv")) {
                    printf("Saved to attendance_data.csv\n");
                } else {
                    printf("Failed to save file.\n");
                }
                break;
            case 9:
                if (load_records_from_file(&list, "attendance_data.csv")) {
                    printf("Loaded from attendance_data.csv\n");
                } else {
                    printf("Failed to load file.\n");
                }
                break;
            case 0:
                running = 0;
                printf("Goodbye.\n");
                break;
            default:
                printf("Unknown option. Try again.\n");
                break;
        }
    }
    return 0;
}
