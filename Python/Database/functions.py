import MySQLdb
import sys
import datetime
import getpass

from queries import *

class User:
	def __init__(self, loggedIn ,userId, userName):
		self.loggedIn = loggedIn
		self.userId = userId
		self.userName = userName

	def login(self, cursor):
		tryCount = 0
		tryThres = 3

		while tryCount < tryThres:
			brukernavn = raw_input("Brukernavn: ")
			passord = getpass.getpass("Passord: ")

			cursor.execute(userQuery, (brukernavn, passord))
			data = cursor.fetchall()

			if data and brukernavn == data[0][1] and passord == data[0][2]:
				self.loggedIn = True
				self.userId = data[0][0]
				self.userName = brukernavn

				print "Logget pa som", brukernavn, "\n"
				self.checkForInvites(cursor)
				return
			else:
				tryCount = tryCount + 1
				print "Feil brukernavn og/eller passord.",tryThres-tryCount, "Forsok igjen."
		print "\n"
		return

	def logout(self):
		print "Logget ut", self.userName, "\n"
		self.loggedIn = False
		self.userId = None
		self.userName = None

	def checkForInvites(self, cursor):
		cursor.execute(checkForInviteQuery, self.userId)
		data = cursor.fetchall()

		if data:
			for x in data:
				if x[1] == None:
					print "Du er invitert til"
					cursor.execute(getAppQuery, x[0])
					data = cursor.fetchall()
					if data:
						avtale = Appointment()
						avtale.loadApp(data[0][0],
										data[0][1],
										data[0][2],
										data[0][3],
										data[0][4],
										data[0][5],
										data[0][6])
						avtale.printApp(cursor)

						respons = raw_input("Respons(ja/nei): ")
						while respons != "ja" and respons != "nei":
							print "Ugyldig respons"
							respons = raw_input("Respons(ja/nei): ")
						cursor.execute(updateResponsQuery, (respons, self.userId, avtale.appId))

class Appointment:
	appId = None
	responsible = None
	start = None
	end = None
	location = None
	description = None
	lastEdited = None

	def loadApp(self, appId, responsible, start, end, location, description, lastEdited):
		self.appId = appId
		self.responsible = responsible
		self.start = start
		self.end = end
		self.location = location
		self.description = description
		self.lastEdited = lastEdited

	def addApp(self, user, cursor):
		self.appId = None
		self.responsible = user.userId

		start = str(raw_input("Start(Y-m-d H:M): "))
		start = start + ":00"
		try:
			self.start = datetime.datetime.strptime(start, "%Y-%m-%d %H:%M:%S")
		except ValueError:
			print "Incorrect format"

		end = str(raw_input("Slutt(Y-m-d H:M): "))
		end = end + ":00"
		try:
			self.end = datetime.datetime.strptime(end, "%Y-%m-%d %H:%M:%S")
		except ValueError:
			print "Incorrect format"

		self.location = raw_input("Sted: ")
		self.description = raw_input("Beskrivelse: ")
		self.lastEdited = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")

		confirm = raw_input("Er alt riktig?: y/n ")
		if confirm == "y":
			cursor.execute(addAppQuery, (self.responsible,
										self.start,
										self.end,
										self.location,
										self.description,
										self.lastEdited))
			self.appId = cursor.lastrowid
			cursor.execute(checkForRoomQuery, self.location)
			data = cursor.fetchall()
			if data:
				cursor.execute(addBookingQuery, (cursor.lastrowid, data[0][0]))
		else:
			print "Begyn pa nytt"
			return

	def updateApp(self, user, cursor):
		choice = raw_input("Velg avtale Id: ")
		cursor.execute(getAppQuery, int(choice))
		data = cursor.fetchall()

		if data:
			self.appId = data[0][0]
			self.responsible = data[0][1]
		else:
			print "Ugyldig"
			return

		if self.responsible == user.userId:
			start = str(raw_input("Start(Y-m-d H:M): "))
			start = start + ":00"
			try:
				self.start = datetime.datetime.strptime(start, "%Y-%m-%d %H:%M:%S")
			except ValueError:
				print "Incorrect format"

			end = str(raw_input("Slutt(Y-m-d H:M): "))
			end = end + ":00"
			try:
				self.end = datetime.datetime.strptime(end, "%Y-%m-%d %H:%M:%S")
			except ValueError:
				print "Incorrect format"

			self.location = raw_input("Sted: ")
			self.description = raw_input("Beskrivelse: ")
			self.lastEdited = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")

			confirm = raw_input("Er alt riktig?: y/n ")
			if confirm == "y":
				cursor.execute(delBookingQuery, self.appId)
				cursor.execute(updateAppQuery, (self.start,
											self.end,
											self.location,
											self.description,
											self.lastEdited,
											self.appId))
				cursor.execute(setResponseNullQuery, self.appId)
				cursor.execute(checkForRoomQuery, self.location)
				data = cursor.fetchall()
				if data:
					cursor.execute(addBookingQuery, (self.appId, data[0][0]))
				else:
					print "Begyn pa nytt"
					return
		else:
			print "Du er ikke ansvarlig for denne avtalen"

	def deleteApp(self, user, cursor):
		choice = raw_input("Velg avtale Id: ")
		cursor.execute(getAppQuery, int(choice))
		data = cursor.fetchall()

		if data:
			self.appId = data[0][0]
			self.responsible = data[0][1]
		else:
			print "Ugyldig"
			return

		if self.responsible == user.userId:
			cursor.execute(deleteAppQuery, self.appId)
		else:
			print "Du er ikke ansvarlig for denne avtalen"

	def inviteToApp(self, cursor):
		choice = raw_input("Velg avtale Id: ")
		cursor.execute(getAppQuery, int(choice))
		data = cursor.fetchall()

		if data:
			self.appId = data[0][0]
		else:
			print "Ugyldig"
			return

		choice = raw_input("p for person, g for gruppe: ")
		if choice == "p":
			pname = raw_input("Skriv brukernavn: ")
			cursor.execute(getUserIdQuery, pname)
			data = cursor.fetchall()
			if data:
				cursor.execute(addInviteQuery, (data[0][0],self.appId))

		elif choice == "g":
			gname = raw_input("Skriv gruppenavn: ")
			cursor.execute(getGrpMembersQuery, gname)
			data = cursor.fetchall()
			if data:
				for x in data:
					cursor.execute(addInviteQuery, (x[0],self.appId))

		else:
			print "Ugyldig valg"
		print "\n"

	def printApp(self, cursor):
		str1 = str(self.appId)
		cursor.execute(getNameQuery, self.responsible)
		data = cursor.fetchall()
		str2 = str(data[0][0])
		str3 = str(self.start)
		str4 = str(self.end)
		str5 = str(self.location)
		str6 = str(self.description)
		str7 = str(self.lastEdited)

		print "Id:\t\t", str1
		print "Ansvarlig:\t", str2
		print "Start:\t\t", str3
		print "Slutt:\t\t", str4
		print "Sted:\t\t", str5
		print "Beskrivelse:\t", str6
		print "Sist endret:\t", str7
		print "\n"

def liste():
	print "login"
	print "logout"
	print "nyavtale"
	print "slettavtale"
	print "oppdateravtale"
	print "inviter"
	print "slettforrom"
	print "oppdatergrpavtale"
	print "gruppeoversikt"
	print "invitasjonoversikt"
	print "avtaleoversikt"
	print "romkapasitet"
	print "deltakelse"
	print "\n"
