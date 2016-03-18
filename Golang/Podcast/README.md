A simple program taking in an URL for a rss/xml file, crates a folder and downloads the mp3 files found. It was written uickly and for fun and it works, but its a bit messy and not at all optimized.

Tested with:
http://podkast.nrk.no/program/radioresepsjonen.rss
http://www.p4.no/lyttesenter/podcast.ashx?pid=330

Warning: This will probably tank both memory and network. The program starts a thread for each file it found and downloads it (probably not a great idea), and the writing to file prt seems to consume a lot of memory. It seems it would be a better idea to make sure only a few threads run at any given time, and rewrite the file saving part to be more of a open file-write-closefile thingy. Im not sure how ioutil.WriteFile works in detail.