#!/bin/bash

sudo apt-get update \
&& sudo apt-get install libsdl1.2-dev libsdl-image1.2-dev libsdl-mixer1.2-dev libsdl-ttf2.0-dev libsdl-gfx1.2-dev -y \
&& sudo apt-get install gcc make build-essential gcc-multilib -y