//
//  Student.c
//  S2Project
//
//  Created by Adil on 3/10/16.
//  Copyright © 2016 Adil. All rights reserved.
//

#include "Student.h"




Student* student_new(int id, char* firstName, char* lastName, char* class,LinkedList* marks){
    Student* student = (Student*) malloc(sizeof(Student));
    if (!student) {
        perror("memory allocation error");
        exit(EXIT_FAILURE);
    }
    student->id = id;
    strncpy(student->firstName, firstName, NAME_LEN);
    strncpy(student->lastName, lastName, NAME_LEN);
    strncpy(student->class, class, NAME_LEN);
    student->marks = marks;
    return student;
}

void student_free(Student* s){
    if(s){
        list_free(s->marks);
        free(s);
    }
}

