import sqlite3
from flask import Flask, request, session, g, redirect, url_for, \
     abort, render_template, flash, _app_ctx_stack
from contextlib import closing
import calendar
from time import strftime 

# configuration
DATABASE = 'data/baza.db'
DEBUG = True

# create our little application :)
app = Flask(__name__)
app.config.from_object(__name__)

def get_db():
    top = _app_ctx_stack.top
    if not hasattr(top, 'sqlite_db'):
        sqlite_db = sqlite3.connect(app.config['DATABASE'])
        sqlite_db.row_factory = sqlite3.Row
        top.sqlite_db = sqlite_db

    return top.sqlite_db

@app.route('/')
def show_Dashboard():
	db = get_db()
	cur = db.execute('select strftime("%s",date) as date, date as datenormal ,temperature,temperature_outside,humidity from temperatures where temperatures.date > datetime(\'now\',\'-24 hour\', \'localtime\') order by date desc;')
	entries = cur.fetchall()
	return render_template('dashboard.html', entries=entries)


if __name__ == '__main__':
    app.run()

