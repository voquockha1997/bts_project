target = out
CXX=gcc
CFLAGS+=-I. -O3  -std=c++1y  -Wall -Wextra -Wpedantic 

# LDFLAGS+= 
 

SRCS = main.c \
	   sensor.c 
	   

	   
#

OBJ:= $(SRCS:%.cpp=%.o)
all: $(target)	

$(target): $(OBJ)
	$(CXX) $(CFLAGS) -o $@ $^ $(CXXFLAGS)

%.o : %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o $(target) 
