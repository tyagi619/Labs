drop database IF EXISTS lab3;
create database lab3;
use lab3;

create table Schedule(
    day VARCHAR(10),
    end_time TIME(0),
    st_time TIME(0),
    PRIMARY KEY (day,end_time,st_time)
);

create table Department(
    dept_id VARCHAR(5),
    dept_name VARCHAR(20) NOT NULL,
    PRIMARY KEY (dept_id)
);

create table Course(
    course_id VARCHAR(5),
    intake INT UNSIGNED NOT NULL,
    course_name VARCHAR(20) NOT NULL,
    course_type  VARCHAR(20) NOT NULL,
    room VARCHAR(10) NOT NULL,
    dept_id VARCHAR(5) NOT NULL,
    since INT UNSIGNED NOT NULL,
    PRIMARY KEY (course_id),
    FOREIGN KEY (dept_id) REFERENCES Department(dept_id)
);

create table Professor(
    prof_id VARCHAR(5),
    prof_name VARCHAR(50) NOT NULL,
    sex ENUM('m','f') NOT NULL,
    dept_id VARCHAR(5) NOT NULL,
    PRIMARY KEY (prof_id),
    FOREIGN KEY (dept_id) REFERENCES Department(dept_id)
);

create table Research_area(
    prof_id VARCHAR(5) NOT NULL,
    research VARCHAR(50) NOT NULL,
    PRIMARY KEY (prof_id,research),
    FOREIGN KEY (prof_id) REFERENCES Professor(prof_id)
);

create table Dependents(
    dependent_name VARCHAR(20),
    age INT UNSIGNED NOT NULL,
    prof_id VARCHAR(5),
    PRIMARY KEY (dependent_name,prof_id),
    FOREIGN KEY (prof_id) REFERENCES Professor(prof_id)
);

create table Scheduled_on(
    day VARCHAR(10),
    end_time TIME(0),
    st_time TIME(0),
    course_id VARCHAR(5),
    PRIMARY KEY (day,end_time,st_time,course_id),
    FOREIGN KEY (day,end_time,st_time) REFERENCES Schedule(day,end_time,st_time),
    FOREIGN KEY (course_id) REFERENCES Course(course_id)
);

create table Teaches(
    course_id VARCHAR(5),
    prof_id VARCHAR(5),
    PRIMARY KEY (course_id,prof_id),
    FOREIGN KEY (course_id) REFERENCES Course(course_id),
    FOREIGN KEY (prof_id) REFERENCES Professor(prof_id)
);

SELECT course_id FROM Course WHERE room='2001';
SELECT DISTINCT dept_name FROM Department WHERE dept_id IN (SELECT dept_id FROM Course WHERE room='L1' or room='L2' or room='L3' );
SELECT prof_name FROM Professor WHERE dept_id IN (SELECT dept_id FROM Department WHERE dept_name='CSE');
SELECT prof_name,prof_id FROM Professor WHERE prof_id IN (SELECT prof_id FROM Teaches WHERE course_id='CS345');
SELECT DISTINCT dept_name,dept_id FROM Department WHERE dept_id IN (SELECT dept_id FROM Course WHERE course_id in (SELECT course_id FROM Schedule WHERE st_time>='15:00:00' AND end_time<='16:00:00'));
SELECT DISTINCT prof_name,prof_id FROM Professor WHERE prof_id NOT IN (SELECT prof_id FROM Teaches WHERE course_id IN (SELECT course_id FROM Scheduled_on WHERE day='Monday' and st_time>='09:00:00' and end_time<='10:00:00'));
SELECT DISTINCT prof_name,prof_id FROM Professor WHERE sex='f' and dept_id IN (SELECT dept_id FROM Department WHERE dept_name='CIVIL DEPARTMENT');
SELECT course_id FROM Course WHERE since>=2016;
SELECT dependent_name,age FROM Dependents WHERE prof_id in (SELECT prof_id FROM Professor WHERE prof_name='Mr X');
SELECT prof_name FROM Professor WHERE prof_id IN (SELECT prof_id FROM Research_area WHERE research='Machine Learning' OR research='Data Mining');
