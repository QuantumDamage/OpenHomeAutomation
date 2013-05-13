import BaseHTTPServer
import sqlite3 as lite
import sys
import urllib2
import json 

con = None

try:
    con = lite.connect('data/baza.db')
    
    cur = con.cursor()    
    cur.execute('SELECT SQLITE_VERSION()')
    
    data = cur.fetchone()
    
    print "SQLite version: %s" % data                
    
except lite.Error, e:
    
    print "Error %s:" % e.args[0]
    sys.exit(1)
    




    


class Handler(BaseHTTPServer.BaseHTTPRequestHandler):
	def do_GET(self):
		print "Got %s!" % self.path[1:6]
		self.send_response(200)
		cels= self.path[1:6]
		#temperatura na zewnatrz:
		f = urllib2.urlopen('http://api.wunderground.com/api/a105856cea4d589b/conditions/q/pws:IDOLNOU013.json') 
		json_string = f.read() 
		parsed_json = json.loads(json_string) 
		temp_c = parsed_json['current_observation']['temp_c'] 
		#print "Current temperature is: %s" % (temp_c) 
		f.close()
		#koniec temperatury na zewnatrz
		with con:
		    cur = con.cursor()    
		    #cur.execute("CREATE TABLE temperatures(date INT, temperature FLOAT, temperature_outside FLOAT,  location TEXT)")
		    query = """INSERT INTO temperatures (date, temperature, temperature_outside , location) VALUES (datetime('now', 'localtime'), ?, ?, ?)"""
		    data =  [cels,temp_c,'sypialnia']
		    cur.execute(query, data)


BaseHTTPServer.HTTPServer(('', 12345), Handler).serve_forever() 

