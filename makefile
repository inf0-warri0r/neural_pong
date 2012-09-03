#
#Author :Tharindra Galahena
#Project:pong game playing neural network (AI)
#Date   :02/09/2012
#License:
# 
#     Copyright 2012 Tharindra Galahena
#
# This program is free software: you can redistribute it and/or modify it under the terms of 
# the GNU General Public License as published by the Free Software Foundation, either 
# version 3 of the License, or (at your option) any later version. This program is distributed
# in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied 
# warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General 
# Public License for more details.
#
# You should have received a copy of the GNU General Public License along with This program. 
# If not, see http://www.gnu.org/licenses/.
#
#/ 

FLAGS = -lGL -lglut -lGLU

all:
	g++ -c neural_net.cpp
	g++ -o pong_trainer pong_trainer.cpp neural_net.o $(FLAGS)
	g++ -o pong_play pong_play.cpp neural_net.o $(FLAGS)

	rm neural_net.o
