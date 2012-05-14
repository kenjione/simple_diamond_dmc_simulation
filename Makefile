C = g++
FLAGS = -Wall -O3 -std=c++0x -lboost_regex-mt
APP_NAME = simple_dmc

all :
	$(C) $(FLAGS) *.cpp *.h -o $(APP_NAME)

clean :
	rm -rf *.o
	rm diamond_easy
