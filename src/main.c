#include "attendance.h"

#include <stdio.h>

int main(void) {
    AttendanceList list;

    init_attendance_list(&list);
    printf("Attendance Demo initialized.\n");
    printf("Current records:\n");
    list_records(&list);
    return 0;
}
