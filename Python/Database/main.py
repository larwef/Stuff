import MySQLdb
import sys

from functions import *

db = MySQLdb.connect("your database conection goes here")
cursor = db.cursor()

user = User(False, None, None)
command = None
while command != "exit":
	try:
		print "Ikke logget pa." 
		print "Skriv login for a logge inn eller exit for a avslutte."
		
		command = raw_input("Komando: ")
		if command == "login":
			user.login(cursor)
			db.commit()

		while user.loggedIn and command != "exit":
			command = raw_input("Komando: ")

			if command == "logout":
				user.logout()

			elif command == "nyavtale":
				avtale = Appointment()
				avtale.addApp(user, cursor)
				print "Lagt til: "
				avtale.printApp(cursor)

			elif command == "slettavtale":
				avtale = Appointment()
				avtale.deleteApp(user, cursor)

			elif command == "oppdateravtale":
				avtale = Appointment()
				avtale.updateApp(user, cursor)

			elif command == "inviter":
				avtale = Appointment()
				avtale.inviteToApp(cursor)

			# Disse er konstruerte for a oppfylle kravet til antall/type queries 
			elif command == "slettforrom":
				print "Sletter alle invitasjoner knyttet til et rom"
				romNavn = raw_input("Romnavn: ")
				cursor.execute(delInvForBookQuery, romNavn)

			elif command == "oppdatergrpavtale":
				print "Oppdaterer alle invitasjoner knyttet til en avtale og en gruppe"
				avtaleId = raw_input("AvtaleId: ")
				gruppeNavn = raw_input("Gruppenavn: ")
				respons = raw_input("Respons: ")
				cursor.execute(updInvForBookQuery, (respons, avtaleId, gruppeNavn))

			elif command == "gruppeoversikt":
				print "Liste over grupper og antall medlemmer"
				antall = raw_input("Min antall medlemmer: ")
				cursor.execute(membersInGrpQuery, antall)
				data = cursor.fetchall()
				if data:
					for x in data:
						print x[0], "\t", x[1], "medlemmer"
				print "\n"

			elif command == "invitasjonoversikt":
				print "Liste over hvilke ansvarlige som har sendt flest invitasjoner, som og tilhorer en gruppe"
				gruppeNavn = raw_input("Gruppenavn: ")
				antall = raw_input("Min antall inviterte: ")
				cursor.execute(respInvByGrpQuery, (gruppeNavn, antall))
				data = cursor.fetchall()
				if data:
					for x in data:
						print x[0], ":", x[1], "inviterte"
				print "\n"

			elif command == "avtaleoversikt":
				antall = raw_input("Min antall inviterte: ")
				cursor.execute(appOverViewQuery, antall)
				data = cursor.fetchall()
				if data:
					for x in data:
						print "AvtaleId:", x[0], ":", x[1], "inviterte"
				print "\n"

			elif command == "romkapasitet":
				nedre = raw_input("Nedre grense kapasitet: ")
				ovre = raw_input("Ovre grense kapasitet: ")
				cursor.execute(roomCapQuery, (nedre, ovre))
				data = cursor.fetchall()
				if data:
					for x in data:
						print "kapasitet:", x[0], "Antall rom:", x[1]
				print "\n"

			elif command == "deltakelse":
				avtaleId = raw_input("AvtaleId: ")
				nedre = raw_input("Nedre grense for antall svar: ")
				cursor.execute(howManyAttendingQuery, (avtaleId, nedre))
				data = cursor.fetchall()
				if data:
					for x in data:
						print "respons:", x[0], "\tAntall:", x[1]
				print "\n"

			elif command == "notinvited":
				print "Printer hvem som ikke er invitert til avtale"
				avtaleId = raw_input("AvtaleId: ")
				cursor.execute(whosNotInvitedQuery, avtaleId)
				data = cursor.fetchall()
				if data:
					for x in data:
						print x[0]
				print "\n"

			elif command == "liste":
				liste()

			db.commit()

		if command == "liste":
			liste()

	except KeyboardInterrupt:
		db.close()
		sys.exit()
		
db.close()
