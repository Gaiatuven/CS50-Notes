#include <stdio.h>
#include <string.h>

struct Weekdays work_days_selection();

struct Work_functions {
  char functions[50];
};

struct Weekdays {
  int work_days[5];
  char communte[50];
};

int main() {
    struct Weekdays mySchedule = work_days_selection();

    printf("\n--- Your Work Schedule ---\n");

    for (int i = 0; i < 5; i++) {
        // If the value is NOT 0, they are in the office
        if (mySchedule.work_days[i] != 0) {
            printf("Day %d: In office %d\n", i + 1, mySchedule.work_days[i]);
        } 
        // If the value IS 0, they are at home
        else {
            printf("Day %d: Working from Home\n", i + 1);
        }
    }

    return 0;
}

// day selector select 3 days in office remaining 2 days automatically become
// WFH transport choice per office day prompt taxi or train store along with day
// cost entry - input the cost for that day communte hardcode values
// daily task/activity log - daily functions

struct Weekdays work_days_selection() {
  struct Weekdays week_day;
  printf("Enter your 3 office days (e.g., 1 3 5, Press x if you working from "
         "home):\n");

  for (int i = 0; i < 5; i++) {
    printf("Day %d: ", i + 1);
    // The space before %d skips the 'Enter' key from previous input
    scanf(" %d", &week_day.work_days[i]);
  }

  return week_day;
}
