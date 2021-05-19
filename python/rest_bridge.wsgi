#! /usr/bin/python3.6
import logging
import sys
logging.basicConfig(stream=sys.stderr)
sys.path.insert(0, '/root/GardenForce-Demo/python/')
from rest_bridge import app as application
application.secret_key = '*!)s6ZvD'