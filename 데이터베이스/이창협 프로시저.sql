DROP PROCEDURE IF EXISTS searchApplicant;
DELIMITER $$
CREATE PROCEDURE searchApplicant(IN Applicant_Id INT)
BEGIN
   SELECT * FROM Applicant WHERE Applicant.applicant_id = Applicant_Id;
END $$
DELIMITER ;

DROP PROCEDURE IF EXISTS insertApplicant;
DELIMITER $$
CREATE PROCEDURE insertApplicant(IN Incidnet_Id INT, IN name varchar(10), IN birth DATE, IN phone VARCHAR(14)
, IN date DATETIME, IN gender VARCHAR(2), IN address VARCHAR(45))
BEGIN
   INSERT INTO Applicant (name, birth, phone, date, gender, address) 
    VALUES (name, birth, phone, date, gender, address);
   UPDATE Incident SET Incident.applicant_id = (SELECT applicant_id FROM Applicant Where applicant_id = LAST_INSERT_ID())
    WHERE incident_id = Incidnet_Id;
END $$
DELIMITER ;

DROP PROCEDURE IF EXISTS updateApplicant;
DELIMITER $$
CREATE PROCEDURE updateApplicant(IN Applicant_Id INT, IN name varchar(10), IN birth DATE
	, IN phone VARCHAR(14), IN date DATETIME, IN gender VARCHAR(2), IN address VARCHAR(45))
BEGIN
UPDATE Applicant SET name = name, birth = birth, phone = phone, date = date, gender = gender, address = address
	WHERE Applicant.applicant_id = Applicant_Id;
END $$
DELIMITER ;

DROP PROCEDURE IF EXISTS searchSuspect;
DELIMITER $$
CREATE PROCEDURE searchSuspect(IN Suspect_Id INT)
BEGIN
   SELECT * FROM Suspect WHERE Suspect.suspect_id = Suspect_Id;
END $$
DELIMITER ;

DROP PROCEDURE IF EXISTS insertSuspect;
DELIMITER $$
CREATE PROCEDURE insertSuspect(IN Incidnet_Id INT, IN name varchar(10), IN birth DATE, IN phone VARCHAR(14), IN gender VARCHAR(2), IN address VARCHAR(45))
BEGIN
   INSERT INTO Suspect (name, birth, phone, gender, address) 
    VALUES (name, birth, phone, gender, address);
   INSERT INTO Incident_Suspect VALUES (Incidnet_Id, (SELECT suspect_id FROM Suspect WHERE suspect_id = LAST_INSERT_ID()));
END $$
DELIMITER ;

DROP PROCEDURE IF EXISTS updateSuspect;
DELIMITER $$
CREATE PROCEDURE updateSuspect(IN Suspect_Id INT, IN name varchar(10), IN birth DATE, IN phone VARCHAR(14), IN gender VARCHAR(2), IN address VARCHAR(45))
BEGIN
UPDATE Suspect SET name = name, birth = birth, phone = phone, gender = gender, address = address
	WHERE Suspect.suspect_id = Suspect_Id;
END $$
DELIMITER ;

DROP PROCEDURE IF EXISTS searchVictim;
DELIMITER $$
CREATE PROCEDURE searchVictim(IN Victim_Id INT)
BEGIN
   SELECT * FROM Victim WHERE Victim.victim_id = Victim_Id;
END $$
DELIMITER ;

DROP PROCEDURE IF EXISTS insertVictim;
DELIMITER $$
CREATE PROCEDURE insertVictim(IN Incidnet_Id INT, IN name varchar(10), IN birth DATE, IN phone VARCHAR(14), IN gender VARCHAR(2), IN address VARCHAR(45))
BEGIN
   INSERT INTO Victim (name, birth, phone, gender, address) 
    VALUES (name, birth, phone, gender, address);
   INSERT INTO Incident_Victim VALUES (Incidnet_Id, (SELECT victim_id FROM Victim WHERE victim_id = LAST_INSERT_ID()));
END $$
DELIMITER ;

DROP PROCEDURE IF EXISTS updateVictim;
DELIMITER $$
CREATE PROCEDURE updateVictim(IN Victim_Id INT, IN name varchar(10), IN birth DATE
	, IN phone VARCHAR(14), IN gender VARCHAR(2), IN address VARCHAR(45))
BEGIN
UPDATE Victim SET name = name, birth = birth, phone = phone, gender = gender, address = address
	WHERE Victim.victim_id = Victim_Id;
END $$
DELIMITER ;

DROP PROCEDURE IF EXISTS insertReport;
DELIMITER $$
CREATE PROCEDURE insertReport(IN title VARCHAR(45), IN content VARCHAR(45), IN Team_Id INT, IN Incidnet_Id INT)
BEGIN
   INSERT INTO Report (title, content, team_id, incident_id) 
	VALUES (title, content, Team_Id, Incident_Id);
END $$
DELIMITER ;

DROP PROCEDURE IF EXISTS searchReport;
DELIMITER $$
CREATE PROCEDURE searchReport(IN Report_Id INT)
BEGIN
	select r.report_id, CONCAT(s.name," ", d.name," ",t.name) as writer , re_date, ch_date, r.title, r.content
	 from Report r join Team_Incident ti on r.team_id = ti.team_id and r.incident_id = ti.incident_id
	 join Team t on t.team_id = ti.team_id
	 join Department d on d.department_id = t.department_id
	 join Station s on d.station_id = s.station_id
	 where r.report_id = Report_Id;
END $$
DELIMITER ;

DROP PROCEDURE IF EXISTS insertReport;
DELIMITER $$
CREATE PROCEDURE insertReport(IN title VARCHAR(45), IN content VARCHAR(45), IN Team_Id INT, IN Incident_Id INT)
BEGIN
	insert into Report (title, content, re_date, team_id, incident_id)
		values (title, content, default, Team_Id, Incident_Id);
END $$
DELIMITER ;

DROP PROCEDURE IF EXISTS updateReport;
DELIMITER $$
CREATE PROCEDURE updateReport(IN Report_Id INT, IN title VARCHAR(45), IN content VARCHAR(45))
BEGIN
	update Report set title=title, content=content , ch_date = now() where Report.report_id = Report_Id;
END $$
DELIMITER ;
