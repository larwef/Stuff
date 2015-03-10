drop table Booking;
drop table Moterom;
drop table Invitasjon;
drop table Avtale;
drop table Gruppemedlem;
drop table Gruppe;
drop table Bruker;

create table Bruker(
	brukerId 	int auto_increment,
    brukerNavn 	varchar(24) not null,
    passord 	varchar(8) not null,
    
    constraint bruker_pk primary key(brukerId)
);

create table Gruppe(
	gruppeId 	int auto_increment,
    gruppeNavn 	varchar(24) not null,
    
    constraint gruppe_pk primary key(gruppeId)
);

create table Gruppemedlem(
	brukerId 	int,
    gruppeId	int,
    
	constraint gruppemedlem_pk primary key(brukerId, gruppeId),
    constraint gruppemedlem_fk1 foreign key(brukerId) references Bruker(brukerId)
		on update cascade
        on delete cascade,
	constraint gruppemedlem_fk2 foreign key(gruppeId) references Gruppe(gruppeId)
		on update cascade
        on delete cascade
);

create table Avtale(
	avtaleId	int auto_increment,
    ansvarlig	int,
    astart		datetime not null,
    aslutt		datetime not null,
    sted		varchar(50),
    beskrivelse	varchar(140),
    sistEndret datetime not null,
    
    constraint avtale_pk primary key(avtaleId),
    constraint avtale_fk foreign key(ansvarlig) references Bruker(brukerId)
		on update cascade
        on delete set null
);

create table Invitasjon(
	brukerId	int,
    avtaleId	int,
    responsDato	datetime,
    respons		varchar(10),
    skjult		bool,
    alarm		datetime,
    
    constraint invitasjon_pk primary key(brukerId, avtaleId),
    constraint invitasjon_fk1 foreign key(brukerId) references Bruker(brukerId)
		on update cascade
        on delete cascade,
	constraint invitasjon_fk2 foreign key(avtaleId) references Avtale(avtaleId)
		on update cascade
        on delete cascade
);

create table Moterom(
	romId		int auto_increment,
    romNavn		varchar(50),
    kapasitet	int not null,
    
    constraint moterom_pk primary key(romId)
);

create table Booking(
	avtaleId	int,
    romId		int,
    
    constraint booking_pk primary key(avtaleId, romId),
    constraint booking_fk1 foreign key(avtaleId) references Avtale(avtaleId)
		on update cascade
        on delete cascade,
	constraint booking_fk2 foreign key(romId) references Moterom(romId)
		on update cascade
        on delete cascade
);