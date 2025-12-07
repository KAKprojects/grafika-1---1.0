#!/bin/bash

# Uruchomić z virtual display i zrobić screenshot
export DISPLAY=:99
Xvfb :99 -screen 0 800x600x24 &
XVFB_PID=$!
sleep 2

# Uruchomić program
timeout 3 ./testsfml2.5 &
sleep 1

# Zrobić screenshot
import -window root screenshot.png 2>/dev/null || echo "Screenshot nie udany"

# Czyszczenie
kill $XVFB_PID 2>/dev/null
echo "Gotowe! Screenshot: screenshot.png"
