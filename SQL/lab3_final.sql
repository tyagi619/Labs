drop database IF EXISTS lab3;
create database lab3;
use lab3;

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

create table Professor(
    prof_id VARCHAR(5),
    prof_name VARCHAR(50) NOT NULL,
    sex ENUM('m','f') NOT NULL,
    dept_id VARCHAR(5) NOT NULL,
    PRIMARY KEY (prof_id),
    FOREIGN KEY (dept_id) REFERENCES Department(dept_id)
);

INSERT INTO Professor VALUES
    ('MAN','Manan Gupta','m','CSE'),
    ('ANU','Anubhav Tyagi','m','CSE'),
    ('MAY','Mayank WadhWani','m','MnC'),
    ('PIY','Piyush Gupta','m','MnC'),
    ('DEV','Devaishi Gupta','f','CSE'),
    ('AMA','AMAN RAJ','m','CSE'),
    ('ABH','ABHISHEK JAISWAL','m','CSE')
;

create table Course(
    course_id VARCHAR(5),
    intake INT UNSIGNED NOT NULL,
    course_name VARCHAR(20) NOT NULL,
    course_type  VARCHAR(20) NOT NULL,
    room VARCHAR(10) NOT NULL,
    dept_id VARCHAR(5) NOT NULL,
    day VARCHAR(10),
    st_time TIME(0),
    end_time TIME(0),
    prof_id VARCHAR(5),
    PRIMARY KEY (course_id),
    FOREIGN KEY (dept_id) REFERENCES Department(dept_id),
    FOREIGN KEY (day,end_time,st_time) REFERENCES Schedule(day,end_time,st_time),
    FOREIGN KEY (prof_id) REFERENCES Professor(prof_id)
);

INSERT INTO Course VALUES
    ('CS345',42,'Databases','Theory','L1','CSE','Tuesday','09:00:00','10:00:00','DEV'),
    ('CS349',26,'Databases Lab','Lab','CSE LAB','CSE','Monday','14:00:00','17:00:00','MAN'),
    ('MA321',28,'Optimization','Theory','L1','MnC','Wednesday','14:00:00','15:00:00','MAY'),
    ('CS428',88,'AI','Theory','5001','CSE','Wednesday','14:00:00','15:00:00','ABH'),
    ('MA224',30,'Probability','Theory','2001','MnC','Tuesday','09:00:00','10:00:00','PIY'),
    ('CS343',5,'Networks','Theory','5001','CSE','Tuesday','09:00:00','10:00:00','MAN'),
    ('CS341',28,'Networks Lab','Lab','CSE Lab','CSE','Thursday','14:00:00','17:00:00','ANU')
;

create table Research_area(
    prof_id VARCHAR(5) NOT NULL,
    research VARCHAR(50) NOT NULL,
    PRIMARY KEY (prof_id,research),
    FOREIGN KEY (prof_id) REFERENCES Professor(prof_id)
);

INSERT INTO Research_area VALUES
    ('AMA','VLSI'),
    ('AMA','Signal Processing'),
    ('MAN','VLSI'),
    ('MAN','ALgorithms'),
    ('ANU','Signal Processing'),
    ('ANU','Data Structures'),
    ('PIY','Probability'),
    ('MAY','Vector Space'),
    ('ABH','Artifical Intelligence'),
    ('DEV','Algorithms')
;

create table Dependents(
    dependent_name VARCHAR(20),
    age INT UNSIGNED NOT NULL,
    prof_id VARCHAR(5),
    PRIMARY KEY (dependent_name,prof_id),
    FOREIGN KEY (prof_id) REFERENCES Professor(prof_id)
);

INSERT INTO Dependents VALUES
    ('Rajesh',32,'MAN'),
    ('Rajesh',28,'AMA'),
    ('Sundar',25,'MAY'),
    ('Rishi',29,'PIY')
;


SELECT DISTINCT prof_name FROM Professor WHERE prof_id IN (SELECT prof_id FROM Dependents WHERE dependent_name = 'Rajesh');

SELECT DISTINCT prof_name FROM Professor WHERE prof_id IN (SELECT prof_id FROM Research_area WHERE research='VLSI') AND prof_id IN (SELECT prof_id FROM Research_area WHERE research='Signal Processing');

SELECT DISTINCT prof_name FROM Professor WHERE prof_id IN (SELECT prof_id FROM Course WHERE intake<=30);

SELECT DISTINCT prof_id FROM Course WHERE prof_id IN (SELECT prof_id FROM Course WHERE course_id='CS345') AND prof_id NOT IN (SELECT prof_id FROM Course WHERE course_id='CS428');

SELECT DISTINCT course_id FROM Course WHERE course_type='Lab' AND day='Monday' AND st_time='14:00:00' AND end_time='17:00:00';
