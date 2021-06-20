	DROP DATABASE IF EXISTS LAB2;
	CREATE DATABASE LAB2;
	USE LAB2;


	CREATE TABLE EMPLOYEES(
    	ssn CHAR(11) NOT NULL,
    	name VARCHAR(50) NOT NULL,
    	lot INT NOT NULL,
    	PRIMARY KEY ( ssn )
    );

    INSERT INTO EMPLOYEES VALUES
    	('123-22-3666','Manan',48),
    	('231-31-5368','Aman',22),
    	('131-24-3650','Piyush',35)
   	;

    CREATE TABLE DEPARTMENTS(
    	did INT UNSIGNED NOT NULL,
    	dname VARCHAR(30) NOT NULL,
    	budget INT UNSIGNED NOT NULL,
    	PRIMARY KEY ( did )
    );

    INSERT INTO DEPARTMENTS VALUES
    	(324,'Finance',630000),
    	(104,'Technical',3600),
    	(287,'HR',9800)
   	;

    CREATE TABLE WORK_IN2(
    	ssn CHAR(11) NOT NULL,
    	did INT UNSIGNED NOT NULL,
    	since DATE NOT NULL,
    	FOREIGN KEY (ssn) REFERENCES EMPLOYEES (ssn),
    	FOREIGN KEY (did) REFERENCES DEPARTMENTS (did),
    	PRIMARY KEY (ssn,did)
    );

    INSERT INTO WORK_IN2 VALUES
    	('123-22-3666',287,'92-09-10'),
    	('231-31-5368',324,'96-01-06'),
    	('131-24-3650',324,'93-06-28')
   	;


    CREATE TABLE MANAGER(
    	m_id INT UNSIGNED NOT NULL,
    	name VARCHAR(50) NOT NULL,
    	location VARCHAR(50) NOT NULL,
    	PRIMARY KEY ( m_id )
    );

    INSERT INTO MANAGER VALUES
    	(120123,'Abhishek','Banglore'),
    	(201012,'Ravi','Gurgaon'),
    	(110072,'Anubhav','Pune')
    ;

    CREATE TABLE EMPLOYEE(
    	emp_id INT UNSIGNED NOT NULL,
    	name VARCHAR(50) NOT NULL,
    	expertise VARCHAR(50) NOT NULL,
    	m_id INT UNSIGNED NOT NULL,
    	FOREIGN KEY (m_id) REFERENCES MANAGER (m_id),
    	PRIMARY KEY ( emp_id )
    );

    INSERT INTO EMPLOYEE VALUES
    	(9718,'Manan','Software',120123),
    	(9101,'Mayank','Security',201012),
    	(8826,'Aman','Front Desk',201012),
    	(7624,'Piyush','Software',110072)
    ;

    CREATE TABLE DEPARTMENT(
    	dept_id INT UNSIGNED NOT NULL,
    	dept_name VARCHAR(50) NOT NULL,
    	PRIMARY KEY(dept_id)
   	);

   	INSERT INTO DEPARTMENT VALUES
    	(324,'Finance'),
    	(104,'Technical'),
    	(287,'HR')
   	;

    CREATE TABLE HOD(
    	emp_id INT UNSIGNED NOT NULL,
    	f_name VARCHAR(50) NOT NULL,
    	l_name VARCHAR(50) NOT NULL,
    	email VARCHAR(20) NOT NULL,
    	dept_id INT UNSIGNED NOT NULL UNIQUE,
    	FOREIGN KEY (dept_id) REFERENCES DEPARTMENT (dept_id),
    	PRIMARY KEY(emp_id)
   	);

   	INSERT INTO HOD VALUES
    	(9101,'Mayank','Wadhwani','mayank@gmail.com',104),
    	(8826,'Aman','Raj','aman@gmail.com',287),
    	(7624,'Piyush','Gupta','piyush@gmail.com',324)
    ;

   	CREATE TABLE STUDENT(
    	stud_id INT UNSIGNED NOT NULL,
    	name VARCHAR(50) NOT NULL,
    	PRIMARY KEY(stud_id)
   	);

   	INSERT INTO STUDENT VALUES
    	(324,'Aman'),
    	(104,'Manan'),
    	(287,'Anubhav')
   	;

   	CREATE TABLE CONTACTS(
   		stud_id INT UNSIGNED NOT NULL,
   		phone INT UNSIGNED NOT NULL UNIQUE,
   		FOREIGN KEY (stud_id) REFERENCES STUDENT (stud_id),
   		PRIMARY KEY (stud_id,phone)
   	);

   	INSERT INTO CONTACTS VALUES
    	(324,971738),
    	(104,971638),
    	(287,971825),
    	(324,971838),
    	(104,971938),
    	(287,971225)
   	;

   	CREATE TABLE SUPERVISOR(
    	ssn_sub CHAR(11) NOT NULL,
    	ssn_emp CHAR(11) NOT NULL,
    	FOREIGN KEY (ssn_sub) REFERENCES EMPLOYEES (ssn),
    	FOREIGN KEY (ssn_emp) REFERENCES EMPLOYEES (ssn),
    	PRIMARY KEY ( ssn_sub,ssn_emp )
    );

    INSERT INTO SUPERVISOR VALUES
    	('123-22-3666','231-31-5368'),
    	('231-31-5368','131-24-3650')
   	;

    CREATE TABLE DEPENDENTS(
    	pname VARCHAR(50) NOT NULL,
    	age INT NOT NULL,
    	cost INT NOT NULL,
    	ssn CHAR(11) NOT NULL,
    	FOREIGN KEY (ssn) REFERENCES EMPLOYEES (ssn) ON DELETE CASCADE,
    	PRIMARY KEY (pname,ssn)
    );

    INSERT INTO DEPENDENTS VALUES
    	('Abhishek',20,300,'231-31-5368'),
    	('Aman',20,600,'123-22-3666'),
    	('Anubhav',20,500,'131-24-3650')
    ;
