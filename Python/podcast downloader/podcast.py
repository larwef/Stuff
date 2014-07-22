import urllib2
import os

print "Choose name of the folder you want to save in, it will appear in the same folder as the .py file"
folder = raw_input("Folder name: ")
if not os.path.exists(folder):
   os.makedirs(folder)
print "URL of the xml/rss file"
url = raw_input("URL: ")

print "Starting..."

response = urllib2.urlopen(url)

prog = False # Used to disregard the <titles> before the <items>
count = 0
audioFiles = []
audioTitles = []

for line in response:
	if "<item>" in line:
		prog = True

	if "<title>" in line and prog:
		audioTitle = line.lstrip()
		audioTitle = audioTitle.rstrip()
		audioTitle = audioTitle.replace("<title>", "")
		audioTitle = audioTitle.replace("</title>", "")

		audioTitles.append(audioTitle)

	if "<enclosure" in line:
		start = line.index("http://")
		end = line.index(".mp3")
		audioFiles.append(line[start:end+4])

nrOfFiles = len(audioFiles)
print nrOfFiles, " file links found"

print "Starting download..."
for audioFile in audioFiles:
	thisDir = os.path.dirname(__file__)
	filePath = folder + "/" + str(count + 1) + ":" + audioTitles[count] + ".mp3"
	absFilePath = os.path.join(thisDir, filePath)
	count += 1

	response = urllib2.urlopen(audioFile)
	content = response.read()
	newFile = open(absFilePath, 'w')
	newFile.write(content)
	newFile.close()
	print count,"/",nrOfFiles, " finished"

print "Finished!"
