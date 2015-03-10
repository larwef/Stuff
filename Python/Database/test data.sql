delete from Bruker where 1=1;
delete from Gruppe where 1=1;
delete from Gruppemedlem where 1=1;
delete from Avtale where 1=1;
delete from Invitasjon where 1=1;
delete from Moterom where 1=1;
delete from Booking where 1=1;

-- Brukere
insert into Bruker (brukerNavn, passord) values
	('dummy1','dummy1'),
	('dummy2','dummy2'),
    ('dummy3','dummy3'),
    ('dummy4','dummy4'),
    ('dummy5','dummy5'),
    ('dummy6','dummy6');

-- Grupper
insert into Gruppe (gruppeNavn) values
	('Gruppe1'),
    ('Gruppe2'),
    ('Gruppe3'),
    ('Alle');
    
-- Gruppemedlemmer
insert into Gruppemedlem (brukerId, gruppeId) values
	(1,1),
    (2,1),
    (3,1),
    (1,2),
    (3,2),
    (4,2),
    (1,4),
    (2,4),
    (3,4),
    (4,4),
    (5,4),
    (6,4);
    
-- Avtaler
insert into Avtale (ansvarlig, astart, aslutt, sted, beskrivelse, sistEndret) values
	(1, '2015-04-01 08:00', '2015-04-01 10:00', 'Gloshaugen', 'Prosjekt', NOW()),
    (1, '2015-04-01 11:00', '2015-04-01 12:30', 'Dragvoll', 'Seminar', NOW()),
    (1, '2015-04-03 09:00', '2015-04-03 11:00', 'Gloshaugen', 'Forelesning', NOW()),
    (1, '2015-06-08 08:15', '2015-06-08 09:15', 'P02', 'Mote', NOW()),
    (3, '2015-04-01 15:00', '2015-04-01 17:00', 'Torget', 'Shopping', NOW()),
    (3, '2015-04-05 21:00', '2015-04-05 23:15', 'Prinsen Kinosenter', 'Ubestemt Film', NOW()),
	(4, '2015-05-05 11:30', '2015-05-05 12:00', 'Kantina', 'Lunsj', NOW()),
    (4, '2015-05-06 11:30', '2015-05-06 12:00', 'Kantina', 'Lunsj', NOW()),
    (4, '2015-05-07 11:30', '2015-05-07 12:00', 'Kantina', 'Lunsj', NOW()),
    (4, '2015-05-08 11:30', '2015-05-08 12:00', 'Kantina', 'Lunsj', NOW()),
    (4, '2015-06-08 08:15', '2015-06-08 09:15', 'P03', 'Mote', NOW()),
    (6, '2015-06-08 08:15', '2015-06-08 09:15', 'P01', 'Mote', NOW()),
    (6, '2015-06-08 08:15', '2015-06-08 09:15', 'P04', 'Mote', NOW()),
    (6, '2015-06-09 08:15', '2015-06-09 09:15', 'E04', 'Mote', NOW()),
    (6, '2015-06-10 08:15', '2015-06-10 09:15', 'E05', 'Mote', NOW());

-- Invitasjoner
insert into Invitasjon (brukerId, avtaleId, responsDato, respons, skjult, alarm) values
	(1, 1, NULL, 'ja', NULL, NULL),
    (1, 2, NULL, 'ja', NULL, NULL),
    (1, 3, NULL, 'ja', NULL, NULL),
    (1, 4, NULL, 'ja', NULL, NULL),
    (3, 5, NULL, 'ja', NULL, NULL),
    (3, 6, NULL, 'ja', NULL, NULL),
    (4, 7, NULL, 'ja', NULL, NULL),
    (4, 8, NULL, 'ja', NULL, NULL),
    (4, 9, NULL, 'ja', NULL, NULL),
    (4, 10, NULL, 'ja', NULL, NULL),
    (4, 11, NULL, 'ja', NULL, NULL),
    (6, 12, NULL, 'ja', NULL, NULL),
    (6, 13, NULL, 'ja', NULL, NULL),
    (6, 14, NULL, 'ja', NULL, NULL),
    (6, 15, NULL, 'ja', NULL, NULL),
    
    (2, 1, NULL, 'nei', NULL, NULL),
    (3, 1, NULL, 'ja', NULL, NULL),
    (4, 1, NULL, NULL, NULL, NULL),
    (6, 1, NULL, NULL, NULL, NULL),
    
    (5, 6, NULL, NULL, NULL, NULL),
    (6, 6, NULL, 'ja', NULL, NULL),
    
    (1, 7, NULL, 'nei', NULL, NULL),
    (2, 7, NULL, 'nei', NULL, NULL),
    (3, 7, NULL, NULL, NULL, NULL),
    
    (2, 11, NULL, NULL, NULL, NULL),
    (3, 11, NULL, NULL, NULL, NULL),
    (5, 11, NULL, 'ja', NULL, NULL),
    (6, 11, NULL, NULL, NULL, NULL),
    
    (1, 12, NULL, 'nei', NULL, NULL),
    (3, 12, NULL, NULL, NULL, NULL),
    
    (1, 13, NULL, NULL, NULL, NULL),
    (2, 13, NULL, 'ja', NULL, NULL),
    (3, 13, NULL, NULL, NULL, NULL),
    
    (1, 15, NULL, NULL, NULL, NULL),
    (2, 15, NULL, 'ja', NULL, NULL),
    (3, 15, NULL, 'nei', NULL, NULL),
    (4, 15, NULL, NULl, NULL, NULL),
    (5, 15, NULL, 'ja', NULL, NULL);

-- Moterom
insert into Moterom (romNavn, kapasitet) values
	('P01', 1),
    ('P02', 2),
    ('P03', 3),
    ('P04', 4),
	('P05', 5),
	('E01', 1),
    ('E02', 2),
    ('E03', 3),
    ('E04', 4),
	('E05', 5);
    
-- Bookinger
insert into Booking values
	(4,2),
    (11,3),
    (12,1),
    (13,4),
    (14,9),
    (15,10);