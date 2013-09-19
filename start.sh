#!/bin/bash

python drone.py &
sleep 1
python server.py &
sleep 1
python client.py
