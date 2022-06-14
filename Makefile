CXX = g++
CFLAGS = -std=c++14 -O2 -Wall -g

TARGET1 = server
TARGET2 = client
OBJS1 = ./src/server.cpp ./src/ftp_server.cpp ./src/epoll.cpp ./src/socket.cpp ./threadpool/threadpool.cpp ./threadpool/task.cpp
OBJS2 = ./src/client.cpp ./src/ftp_client.cpp ./src/socket.cpp

all: $(OBJS1) $(OBJS2)
		$(CXX) $(CFLAGS) $(OBJS1) -o $(TARGET1) -lpthread
		$(CXX) $(CFLAGS) $(OBJS2) -o $(TARGET2) -lpthread

clean:
		rm -rf ./$(OBJS1) ./$(OBJS2) $(TARGET1) $(TARGET2)
