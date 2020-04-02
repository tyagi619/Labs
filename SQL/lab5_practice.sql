drop database IF EXISTS lab5;
create database lab5;
use lab5;

create table Schedule(
    day VARCHAR(10),
    st_time TIME(0),
    end_time TIME(0),
    PRIMARY KEY (day,end_time,st_time)
);

INSERT INTO Schedule VALUES
    ('Monday','14:00:00','17:00:00'),
    ('Tuesday','09:00:00','10:00:00'),
    ('Monday','09:00:00','12:00:00'),
    ('Wednesday','14:00:00','15:00:00'),
    ('Wednesday','15:00:00','16:00:00'),
    ('Thursday','14:00:00','17:00:00')
;

create table Department(
    dept_id VARCHAR(5),
    dept_name VARCHAR(50) NOT NULL,
    PRIMARY KEY (dept_id)
);

INSERT INTO Department VALUES
    ('CSE','Computer Science And Engineering'),
    ('MnC','Maths And Computing')
;

create table Student(
    stud_id CHAR(9),
    name VARCHAR(50) NOT NULL,
    dept_id VARCHAR(5) NOT NULL,
    FOREIGN KEY(dept_id) REFERENCES Department(dept_id),
    PRIMARY KEY (stud_id)
);

INSERT INTO Student VALUES
  ('170101009','ANUBHAV TYAGI','CSE'),
  ('170101035','MANAN GUPTA','CSE'),
  ('170101038','MAYANK WADHWANI','MnC'),
  ('170101045','PIYUSH GUPTA','MnC'),
  ('170101053','RAVI SHANKAR','CSE')
;

create table Course(
    course_id VARCHAR(5),
    intake INT UNSIGNED NOT NULL,
    course_name VARCHAR(50) NOT NULL,
    course_type  VARCHAR(20) NOT NULL,
    room VARCHAR(10) NOT NULL,
    dept_id VARCHAR(5) NOT NULL,
    since INT UNSIGNED NOT NULL,
    PRIMARY KEY (course_id),
    FOREIGN KEY (dept_id) REFERENCES Department(dept_id)
);

INSERT INTO Course VALUES
    ('CS345',42,'Databases','Theory','L1','CSE',2013),
    ('CS349',26,'Databases Lab','Lab','CSE LAB','CSE',2011),
    ('MA321',28,'Optimization','Theory','L2','MnC',2007),
    ('CS343',88,'AI','Theory','5001','CSE',2007),
    ('MA224',30,'Probability','Theory','2001','MnC',2011),
    ('MA342',5,'Finance','Theory','5001','MnC',2015),
    ('CS341',28,'Networks Lab','Lab','CSE Lab','CSE',2013)
;

create table Professor(
    prof_id VARCHAR(5),
    prof_name VARCHAR(50) NOT NULL,
    sex ENUM('m','f') NOT NULL,
    dept_id VARCHAR(5) NOT NULL,
    PRIMARY KEY (prof_id),
    FOREIGN KEY (dept_id) REFERENCES Department(dept_id)
);

INSERT INTO Professor VALUES
    ('DEE','DEEPANJAN KESH','m','CSE'),
    ('SVR','SV RAO','m','CSE'),
    ('ANJ','ANJAN KC','m','MnC'),
    ('SUB','SUBRAMANYAN SAHA','m','MnC'),
    ('MOM','MOMITRA PATRA','f','CSE'),
    ('JOH','JOHN JOSE','m','CSE'),
    ('PIN','PINAKI MITRA','m','CSE')
;

create table Research_area(
    prof_id VARCHAR(5) NOT NULL,
    research VARCHAR(50) NOT NULL,
    PRIMARY KEY (prof_id,research),
    FOREIGN KEY (prof_id) REFERENCES Professor(prof_id)
);

INSERT INTO Research_area VALUES
    ('DEE','VLSI'),
    ('DEE','Signal Processing'),
    ('SVR','VLSI'),
    ('PIN','ALgorithms'),
    ('SVR','Signal Processing'),
    ('MOM','Data Structures'),
    ('SUB','Probability'),
    ('ANJ','Vector Space'),
    ('DEE','Artifical Intelligence'),
    ('DEE','Algorithms')
;

create table Dependents(
    dependent_name VARCHAR(50),
    age INT UNSIGNED NOT NULL,
    prof_id VARCHAR(5),
    PRIMARY KEY (dependent_name,prof_id),
    FOREIGN KEY (prof_id) REFERENCES Professor(prof_id)
);

INSERT INTO Dependents VALUES
    ('Rajesh',32,'DEE'),
    ('Rajesh',28,'SUB'),
    ('Sundar',25,'MOM'),
    ('Rishi',29,'PIN')
;

create table Scheduled_on(
    day VARCHAR(10),
    st_time TIME(0),
    end_time TIME(0),
    course_id VARCHAR(5),
    PRIMARY KEY (day,end_time,st_time,course_id),
    FOREIGN KEY (day,end_time,st_time) REFERENCES Schedule(day,end_time,st_time),
    FOREIGN KEY (course_id) REFERENCES Course(course_id)
);

INSERT INTO Scheduled_on VALUES
    ('Tuesday','09:00:00','10:00:00','CS345'),
    ('Monday','14:00:00','17:00:00','CS349'),
    ('Wednesday','15:00:00','16:00:00','MA321'),
    ('Wednesday','14:00:00','15:00:00','CS343'),
    ('Tuesday','09:00:00','10:00:00','MA224'),
    ('Tuesday','09:00:00','10:00:00','MA342'),
    ('Thursday','14:00:00','17:00:00','CS341')
;

create table Teaches(
    course_id VARCHAR(5),
    prof_id VARCHAR(5),
    PRIMARY KEY (course_id,prof_id),
    FOREIGN KEY (course_id) REFERENCES Course(course_id),
    FOREIGN KEY (prof_id) REFERENCES Professor(prof_id)
);

INSERT INTO Teaches VALUES
    ('CS345','DEE'),
    ('CS349','JOH'),
    ('MA321','SUB'),
    ('CS343','PIN'),
    ('MA224','ANJ'),
    ('MA342','SUB'),
    ('CS341','MOM')
;

create table Attends(
    stud_id CHAR(9) NOT NULL,
    course_id VARCHAR(5) NOT NULL,
    grade INT UNSIGNED NOT NULL,
    FOREIGN KEY (course_id) REFERENCES Course(course_id),
    FOREIGN KEY (stud_id) REFERENCES Student(stud_id),
    PRIMARY KEY (stud_id,course_id)
);

INSERT INTO Attends VALUES
    ('170101009','CS345',9),
    ('170101009','CS349',8),
    ('170101009','CS343',7),
    ('170101009','CS341',8),
    ('170101035','CS345',6),
    ('170101035','CS349',9),
    ('170101035','CS343',8),
    ('170101035','CS341',10),
    ('170101053','CS345',8),
    ('170101053','CS349',6),
    ('170101053','CS343',7),
    ('170101053','CS341',9),
    ('170101038','MA321',9),
    ('170101038','MA224',8),
    ('170101038','MA342',8),
    ('170101045','MA321',7),
    ('170101045','MA224',6),
    ('170101045','MA342',7)
;

create view q1 as select min(since) as since from Course;
select Course.course_id from Course JOIN q1 ON q1.since = Course.since;

create view q2 as select max(intake) as intake from Course;
select Course.course_id from Course JOIN q2 ON q2.intake = Course.intake where Course.since >= 2000;

create view q3 as select Student.stud_id, Student.name, Course.course_id, Course.intake, Course.course_name,Course.course_type,Course.grade from Student natural join (select * from Course natural join Attends) as Course;
select DISTINCT stud_id from q3 where intake > 30;
select stud_id, course_id from q3 where grade >=8;
select DISTINCT stud_id from q3 where course_type = 'lab';
select course_id, count(stud_id) as 'No of students' from q3 where grade >= 9 group by course_id;