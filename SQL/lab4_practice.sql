drop database IF EXISTS lab4;
create database lab4;
use lab4;

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
    ('CS343',88,'AI','Theory','5001','CSE',2017),
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

select dept_id , count(prof_id) AS 'Total Professors' FROM Professor GROUP BY dept_id;
select course_id from Course where intake IN (select max(intake) from Course);
select dept_id, count(prof_id) AS 'Total Professors' from Professor GROUP BY dept_id ORDER BY count(prof_id) desc;
select day, count(course_id) AS 'Course' from Scheduled_on GROUP BY day ORDER BY count(course_id) desc;
select stud_id, avg(grade) AS 'Avg CPI' from Attends GROUP BY stud_id;

select Department.dept_name, Course.room from Course LEFT JOIN Department ON Department.dept_id = Course.dept_id where room = 'L1' OR room = 'L2' OR room = 'L3';
select Professor.prof_name from Professor JOIN Department ON Department.dept_id = Professor.dept_id where Department.dept_name = 'Computer Science And Engineering';
select Professor.prof_name,Professor.prof_id from Teaches JOIN Professor ON Professor.prof_id = Teaches.prof_id where Teaches.course_id = 'CS345';
select Department.dept_name, Department.dept_id from Scheduled_on JOIN Course ON Course.course_id = Scheduled_on.course_id JOIN Department ON Department.dept_id = Course.dept_id where Scheduled_on.st_time = '15:00:00' and Scheduled_on.end_time = '16:00:00';
