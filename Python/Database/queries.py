userQuery = """SELECT brukerId, brukerNavn, passord
				FROM Bruker
				WHERE brukerNavn = %s AND passord = %s"""

getNameQuery = """SELECT brukerNavn
				FROM Bruker
				WHERE brukerId = %s"""
getUserIdQuery = """SELECT brukerId
				FROM Bruker
				WHERE brukerNavn = %s"""

getAppQuery = """SELECT *
				FROM Avtale
				WHERE avtaleId = %s"""
# +1 inserion
addAppQuery = """INSERT INTO Avtale
				(ansvarlig, astart, aslutt, sted, beskrivelse, sistEndret) 
				VALUES (%s,%s,%s,%s,%s,%s)"""
# +1 insertion
addInviteQuery = """INSERT INTO Invitasjon
				(brukerId, avtaleId)
				VALUES (%s,%s)"""
# +1 join
getGrpMembersQuery = """SELECT brukerId
				FROM Gruppemedlem NATURAL JOIN Gruppe
				WHERE gruppeNavn = %s"""
# +1 delete
deleteAppQuery = """DELETE FROM Avtale
				WHERE avtaleId = %s"""
# +2 join
checkForInviteQuery = """SELECT i.avtaleId, i.respons 
				FROM Avtale as a
					NATURAL JOIN Invitasjon as i
					INNER JOIN Bruker AS b ON b.brukerId = i.brukerId
				WHERE i.brukerId = %s"""
# +1 update
updateResponsQuery = """UPDATE Invitasjon
				SET respons = %s
				WHERE brukerId = %s AND avtaleId = %s"""
# +1 update
updateAppQuery = """UPDATE Avtale
				SET astart = %s,
					aslutt = %s,
					sted = %s,
					beskrivelse = %s,
					sistEndret = %s
				WHERE avtaleId = %s"""

# For lik updateResponsQuery teller ikke +
setResponseNullQuery = """UPDATE Invitasjon
				SET respons = NULL
				WHERE avtaleId = %s"""

checkForRoomQuery = """SELECT *
				FROM Moterom
				WHERE romNavn = %s"""

# +1 insertion
addBookingQuery = """INSERT INTO Booking
				(avtaleId, romId)
				VALUES (%s, %s)"""
# +1 delete
delBookingQuery = """DELETE FROM Booking
				WHERE avtaleId = %s"""

# +1 delete +1 nested +2 join
delInvForBookQuery = """DELETE FROM Invitasjon
				WHERE avtaleId IN(SELECT a.avtaleId
								FROM Moterom as m
									NATURAL JOIN Booking as b
									NATURAL JOIN Avtale as a
								WHERE m.romNavn = %s)"""
# Brukes ikke, men la sta, kan vaere kjekk a ha
updateLocInvQuery = """UPDATE Avtale AS a, Invitasjon AS i
				SET a.sted = %s, i.respons = NULL
				WHERE a.avtaleId = i.avtaleId
					AND a.avtaleId = %s"""

# Backup dersom jeg ikke finner en annen update med join a bruke
updInvForBookQuery2 = """UPDATE Invitasjon
				SET respons = %s
				WHERE avtaleId IN(SELECT a.avtaleId
								FROM Moterom as m
									NATURAL JOIN Booking as b
									NATURAL JOIN Avtale as a
								WHERE m.romNavn = %s)"""

# +1 update +2 join +1 nested
updInvForBookQuery = """UPDATE Invitasjon
				SET respons = %s
				WHERE avtaleId	= %s
					AND brukerId IN(SELECT b.brukerId
									FROM Bruker AS b
										NATURAL JOIN Gruppemedlem as gm
										NATURAL JOIN Gruppe as g
									WHERE g.gruppeNavn = %s))"""
# +1 group by og having
membersInGrpQuery = """SELECT g.gruppeNavn, count(gm.brukerId) AS AntallMedlemmer
				FROM Gruppe AS g 
					LEFT JOIN Gruppemedlem AS gm
						ON g.gruppeId = gm.gruppeId
				GROUP BY g.gruppeNavn
				HAVING AntallMedlemmer >= %s"""

# Teller antall invitasjoner for hver ansvarlig tilhorende en gruppe
# +3 join  +1 group by og having +2 nested
respInvByGrpQuery = """SELECT b.brukerNavn, count(*) AS AntallInviterte
				FROM Avtale AS a
					NATURAL JOIN Invitasjon as i
					INNER JOIN Bruker as b
						ON b.brukerId = a.ansvarlig
				WHERE a.ansvarlig IN(SELECT a.ansvarlig
									FROM Avtale AS a
										INNER JOIN Gruppemedlem AS gm
											ON a.ansvarlig = gm.brukerId
									WHERE gm.gruppeId IN (SELECT gruppeId
														FROM Gruppe
														WHERE gruppeNavn = %s))
				GROUP BY b.brukerNavn
				HAVING AntallInviterte >= %s"""
# +1 join +1 group by og having
appOverViewQuery = """SELECT a.avtaleId, count(*) AS AntallInviterte
					FROM Avtale AS a
						NATURAL JOIN Invitasjon AS i
					GROUP BY a.avtaleId
					HAVING AntallInviterte >= %s"""
# +1 group by og having
roomCapQuery = """SELECT kapasitet, count(kapasitet)
				FROM Moterom
				GROUP BY kapasitet
				HAVING kapasitet >= %s
					AND kapasitet <= %s """
# +1 group by og having
howManyAttendingQuery = """SELECT respons, count(*) AS AntallRespons
				FROM Invitasjon
				WHERE avtaleId = %s
				GROUP BY respons
				HAVING AntallRespons >= %s"""

whosNotInvitedQuery = """SELECT brukerNavn
				FROM Bruker
				WHERE brukerId NOT IN(SELECT b.brukerId
									FROM Bruker AS b
									NATURAL JOIN Invitasjon as i
									WHERE i.avtaleId = %s)"""

# Total
# 12/5 join
# 5/5 nested queries
# 5/5 group by og having
# 3/3 insertions
# 3/3 updates (1 med join)
# 3/3 deletes (1 med join)