
drop table if exists students;
create table if not exists students (
	id integer primary key,
	firstname text,
	lastname text,
	class text
);

drop table if exists marks;
create table if not exists marks (
	id integer primary key,
	value real,
	exam_number	integer,
	student_id integer
);



insert into students(firstname,lastname,class) values("adil","belhaji","2EI");
insert into students(firstname,lastname,class) values("achraf","hammoumi","2EI");
insert into students(firstname,lastname,class) values("maryam","ghazwani","2EI");


insert into students(firstname,lastname,class) values("mohmed amine","rachdidi","1EI");
insert into students(firstname,lastname,class) values("khalid","saaid","1EI");
insert into students(firstname,lastname,class) values("hedo","diop","1EI");


insert into students(firstname,lastname,class) values("heloino","asaar","3EI");
insert into students(firstname,lastname,class) values("amine","benholi","3EI");
insert into students(firstname,lastname,class) values("rachid","skkal","3EI");




insert into marks(value,exam_number,student_id) values(19,1,1);
insert into marks(value,exam_number,student_id) values(17,2,1);

insert into marks(value,exam_number,student_id) values(20,1,2);
insert into marks(value,exam_number,student_id) values(10,2,2);

insert into marks(value,exam_number,student_id) values(19,1,3);
insert into marks(value,exam_number,student_id) values(19.5,2,3);

insert into marks(value,exam_number,student_id) values(15.75,1,4);
insert into marks(value,exam_number,student_id) values(1.5,2,4);

insert into marks(value,exam_number,student_id) values(19,1,5);
insert into marks(value,exam_number,student_id) values(19,2,5);

insert into marks(value,exam_number,student_id) values(17,1,6);
insert into marks(value,exam_number,student_id) values(17,2,6);












