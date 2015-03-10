#insert into Avtale (ansvarlig, astart, aslutt, sted, beskrivelse, sistEndret)
#	values (1, '2016-01-01 08:00', '2016-01-01 10:00', 'Gloshaugen', 'Prosjekt', NOW());


#insert into Invitasjon (brukerId, avtaleId)
#	values (1,6);


#insert into Booking (avtaleId, romId)
#	values (1,5);


#update Invitasjon
#set respons = NULL
#where brukerId = 1
#	and avtaleId = 1


#update Avtale
#set astart = '2016-01-01 09:00',
#	aslutt = '2016-01-01 11:00',
#    sted = 'Gloshaugen',
#    beskrivelse = 'Prosjekt',
#    sistEndret = NOW()
#where avtaleId = 1;


#update Invitasjon
#set respons = 'Ja'
#where avtaleId = 1
#	and brukerId in(select b.brukerId
#					from Bruker as b
#						natural join Gruppemedlem as gm
#                        natural join Gruppe as g
#					where g.gruppeNavn = 'Gruppe1');


#delete from Booking
#where avtaleId = 1;


#delete from Avtale
#where avtaleId = 1;


#delete from Invitasjon
#where avtaleId in(select a.avtaleId
#				from Moterom as m
#					natural join Booking as b
#                    natural join Avtale as a
#                where m.romNavn = 'P01');


select g.gruppenavn, count(gm.brukerId) as AntallMedlemmer
from Gruppe as g
	left join Gruppemedlem as gm
		on g.gruppeId = gm.gruppeId
group by g.gruppeNavn
having AntallMedlemmer >= 0;


select b.brukerNavn, count(*) as AntallInviterte
from Avtale as a
	natural join Invitasjon as i
    inner join Bruker as b
		on b.brukerId = a.ansvarlig
where a.ansvarlig in(select a.ansvarlig
					from Avtale as a
						inner join Gruppemedlem as gm
							on a.ansvarlig = gm.brukerId
                    where gm.gruppeId in(select gruppeId
										from Gruppe
										where gruppeNavn = 'Gruppe2'))
group by b.brukerNavn
having AntallInviterte >= 4;


select a.avtaleId, count(*) as AntallInviterte
from Avtale as a
	natural join Invitasjon as i
group by a.avtaleId
having AntallInviterte >= 3;


select kapasitet, count(kapasitet) as Antall
from Moterom
group by kapasitet
having kapasitet >= 2
	and kapasitet <= 4;


select respons, count(*) as AntallRespons
from Invitasjon
where avtaleId = 15
group by respons
having AntallRespons >= 0;


select brukerNavn
from Bruker
where brukerId not in(select b.brukerId
						from Bruker as b
							natural join Invitasjon as i
                            where i.avtaleId = 6);

# Total
# 8/5 join
# 4/5 nested queries
# 5/5 group by og having
# 3/3 insertions
# 3/3 updates (1 med join)
# 3/3 deletes (1 med join)
