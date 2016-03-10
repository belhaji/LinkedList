//
//  Mark.h
//  S2Project
//
//  Created by Adil on 3/10/16.
//  Copyright © 2016 Adil. All rights reserved.
//

#ifndef Mark_h
#define Mark_h

#include "Student.h"
#include "LinkedList.h"
#include "App.h"



typedef enum {
    VALUE,
    EXAM_NUMBER,
} MarksOrder;

typedef struct {
    int         id;
    double       value;
    int         examNumber;
    Student*    student;
} Mark;


Mark* mark_new(int id, double value, int examNumber, Student* student);

void mark_free(Mark* mark);

int mark_save(sqlite3* db,Mark* mark);

int mark_delete(sqlite3* db,int id);

int mark_delete_all(sqlite3* db);

int mark_delete_by_student_id(sqlite3* db,int id);

Mark* mark_find(sqlite3* db,int id);

LinkedList* mark_find_all(sqlite3* db,MarksOrder order);

LinkedList* mark_find_by_student_id(sqlite3* db,int student_id,MarksOrder order);

#endif /* Mark_h */
