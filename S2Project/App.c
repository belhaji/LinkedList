//
//  main.c
//  S2Project
//
//  Created by Adil on 3/8/16.
//  Copyright © 2016 Adil. All rights reserved.
//

#include "App.h"
#include "Student.h"
#include "Mark.h"

void print_marks_list(LinkedList* marks){
    if (marks) {
        int i;
        Mark* m;
        for (i=0; i< list_size(marks); i++) {
            m = (Mark*) list_get(marks, i);
            printf("id=%d value=%lf examnum=%d stdname=%s %s \n",
                   m->id,
                   m->value,
                   m->examNumber,
                   m->student->firstName,
                   m->student->lastName
                   );
        }
    }
}

int main(int argc, const char * argv[]) {
    sqlite3* db = NULL;
    int ret;
    //Student s;
    //s.id = 6;
    Mark *m = NULL;
    LinkedList* list = NULL;
    int rc = sqlite3_open("app.db", &db);
    if (rc) {
        fprintf(stderr,"Error open db");
        sqlite3_close(db);
        exit(EXIT_FAILURE);
    }
    //m = mark_find(db, 50);
    list = mark_find_all(db, 0);
    if (list) {
        print_marks_list(list);
    }
    
    sqlite3_close(db);
    return 0;
}
