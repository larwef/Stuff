import os
import sqlite3

db_filename = "base.db"

conn = sqlite3.connect(db_filename)
c = conn.cursor()

if not os.path.exists(db_filename):
	print "Need to create schema"
else:
	print "Database exists"

# Creates a table if it doesnt exists
c.execute("CREATE TABLE IF NOT EXISTS base(id INTEGER PRIMARY KEY AUTOINCREMENT, my_var1 TEXT, my_var2 INT)")

# Insert values into base
c.execute("INSERT INTO base VALUES (NULL,'YES', 10)")
c.execute("INSERT INTO base VALUES (NULL,'NO', 12)")
c.execute("INSERT INTO base VALUES (NULL,'YES', 13)")

# Insert several lines
lines =[ (None,'YES', 1), (None,'NO', 0), (None,'YES', 3), (None,'YES', 9), (None,'YES', 10) ]
c.executemany('INSERT INTO base VALUES (?,?,?)', lines)

#c.execute("DELETE FROM base WHERE my_var1 = ?", ('NO', )) # Delete elements where my_var1 = NO

#c.execute("DROP TABLE base") # Delete table base

# Print rows where my_var2 = 12
for row in c.execute("SELECT * FROM base WHERE my_var2 = ?", (12, )):
	print row
	print "1: ", row[0], "2: ", row[1], "3: ", row[2]

print "\n"

# Print all rows
for row in c.execute("SELECT * FROM base"):
	print row
	print "1: ", row[0], "2: ", row[1], "3: ", row[2]


conn.commit()
conn.close()