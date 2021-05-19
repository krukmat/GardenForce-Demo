#! /usr/bin/python3.6
sys.path.insert(0, '/rest /var/www/html/GardenForce-Demo/python/')
import logging
import sys
logging.basicConfig(stream=sys.stderr)
from rest_app import app as application
application.secret_key = '*!)s6ZvD'