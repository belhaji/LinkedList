//
//  Mark.c
//  S2Project
//
//  Created by Adil on 3/10/16.
//  Copyright © 2016 Adil. All rights reserved.
//


#include "Mark.h"


Mark* mark_new(int id, double value, int examNumber, Student* student){
    Mark* mark = (Mark*) malloc(sizeof(Mark));
    if (!mark) {
        fprintf(stderr,"Error memory allocation");
        exit(EXIT_FAILURE);
    }
    mark->id = id;
    mark->value = value;
    mark->examNumber = examNumber;
    mark->student = student;
    return mark;
}

void mark_free(Mark* mark){
    if (mark) {
        student_free(mark->student);
        free(mark);
    }
}

int mark_save(sqlite3* db,Mark* mark){
    int rc,ret;
    sqlite3_stmt *stmt = NULL;
    char* sql ;
    if (mark->id < 1)
        sql = "INSERT INTO marks(value,exam_number,student_id) VALUES(?,?,?)";
    else
        sql = "UPDATE marks SET value = ? ,exam_number = ? , student_id = ? WHERE id = ?";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc) {
        fprintf(stderr,"Error stmt %s\n",sqlite3_errmsg(db));
        return 0;
    }
    sqlite3_bind_double(stmt, 1, mark->value);
    sqlite3_bind_int(stmt, 2, mark->examNumber);
    sqlite3_bind_int(stmt, 3, mark->student->id);
    if (mark->id > 0) {
        sqlite3_bind_int(stmt, 4, mark->id);
    }
    rc = sqlite3_step(stmt);
    
    if (rc == SQLITE_ERROR)
        ret = 0;
    else
        ret = (int) sqlite3_last_insert_rowid(db);
    
    sqlite3_finalize(stmt);
    
    return ret;
    
}

int mark_delete(sqlite3* db,int id){
    int rc,ret;
    sqlite3_stmt *stmt = NULL;
    char* sql ;
    sql = "DELETE FROM marks WHERE id = ?";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc) {
        fprintf(stderr,"Error stmt %s\n",sqlite3_errmsg(db));
        return 0;
    }
    sqlite3_bind_int(stmt, 1, id);
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE){
        ret = 0;
    }else
        ret = 1;
    sqlite3_finalize(stmt);
    return ret;
}

int mark_delete_all(sqlite3* db){
    int rc,ret;
    sqlite3_stmt *stmt = NULL;
    char* sql ;
    sql = "DELETE FROM marks WHERE 1 = 1";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc) {
        fprintf(stderr,"Error stmt %s\n",sqlite3_errmsg(db));
        return 0;
    }
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE){
        ret = 0;
    }else
        ret = 1;
    sqlite3_finalize(stmt);
    return ret;
}

int mark_delete_by_student_id(sqlite3* db,int id){
    int rc,ret;
    sqlite3_stmt *stmt = NULL;
    char* sql ;
    sql = "DELETE FROM marks WHERE student_id = ?";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc) {
        fprintf(stderr,"Error stmt %s\n",sqlite3_errmsg(db));
        return 0;
    }
    sqlite3_bind_int(stmt, 1, id);
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE){
        ret = 0;
    }else
        ret = 1;
    sqlite3_finalize(stmt);
    return ret;
}

Mark* mark_find(sqlite3* db,int id){
    int rc;
    Mark *ret = NULL;
    sqlite3_stmt *stmt = NULL;
    char* sql ;
    sql = "SELECT * FROM marks m JOIN students s WHERE m.id = ? AND s.id = m.student_id;";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc) {
        fprintf(stderr,"Error stmt %s\n",sqlite3_errmsg(db));
        return 0;
    }
    sqlite3_bind_int(stmt, 1, id);
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW){
        ret = NULL;
    }else{
        ret = mark_new(sqlite3_column_int(stmt, 0),
                       sqlite3_column_double(stmt, 1),
                       sqlite3_column_int(stmt, 2),
                       student_new(sqlite3_column_int(stmt, 3),
                                   (char*)sqlite3_column_text(stmt, 5),
                                   (char*)sqlite3_column_text(stmt, 6),
                                   (char*)sqlite3_column_text(stmt, 7),
                                   list_new() ) );
    }
    sqlite3_finalize(stmt);
    return ret;
}

LinkedList* mark_find_all(sqlite3* db,MarksOrder order){
    int rc;
    LinkedList* marks = NULL;
    Mark *mark = NULL;
    sqlite3_stmt *stmt = NULL;
    char* sql = NULL;
    switch (order) {
        case VALUE:
            sql = "SELECT * FROM marks m JOIN students s WHERE s.id = m.student_id ORDER BY value";
            ;  break;
        case EXAM_NUMBER:
            sql = "SELECT * FROM marks m JOIN students s WHERE s.id = m.student_id ORDER BY exam_number";
            break;
        default:
            break;
    }
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc) {
        fprintf(stderr,"Error stmt %s\n",sqlite3_errmsg(db));
        return 0;
    }
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW){
        marks = NULL;
    }else{
        marks = list_new();
        do {
            mark = mark_new(sqlite3_column_int(stmt, 0),
                            sqlite3_column_double(stmt, 1),
                            sqlite3_column_int(stmt, 2),
                            student_new(sqlite3_column_int(stmt, 3),
                                        (char*)sqlite3_column_text(stmt, 5),
                                        (char*)sqlite3_column_text(stmt, 6),
                                        (char*)sqlite3_column_text(stmt, 7),
                                        list_new() ) );
            list_add(marks, mark);
        }while ( (rc=sqlite3_step(stmt)) == SQLITE_ROW);
    }
    sqlite3_finalize(stmt);
    return marks;
}

LinkedList* mark_find_by_student_id(sqlite3* db,int student_id,MarksOrder order){
    int rc;
    LinkedList* marks = NULL;
    Mark *mark = NULL;
    sqlite3_stmt *stmt = NULL;
    char* sql = NULL;
    switch (order) {
        case VALUE:
            sql = "SELECT * FROM marks m JOIN students s WHERE m.student_id = s.id AND m.student_id = ? ORDER BY value";
            break;
        case EXAM_NUMBER:
            sql = "SELECT * FROM marks m JOIN students s WHERE m.student_id = s.id AND m.student_id = ? ORDER BY exam_number";
            break;
        default:
            break;
    }
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc) {
        fprintf(stderr,"Error stmt %s\n",sqlite3_errmsg(db));
        return 0;
    }
    sqlite3_bind_int(stmt, 1, student_id);
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW){
        marks = NULL;
    }else{
        marks = list_new();
        do {
            mark = mark_new(sqlite3_column_int(stmt, 0),
                            sqlite3_column_double(stmt, 1),
                            sqlite3_column_int(stmt, 2),
                            student_new(sqlite3_column_int(stmt, 3),
                                        (char*)sqlite3_column_text(stmt, 5),
                                        (char*)sqlite3_column_text(stmt, 6),
                                        (char*)sqlite3_column_text(stmt, 7),
                                        list_new() ) );
            list_add(marks, mark);
        }while ( (rc=sqlite3_step(stmt)) == SQLITE_ROW);
    }
    sqlite3_finalize(stmt);
    return marks;
}










