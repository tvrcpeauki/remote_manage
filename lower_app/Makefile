Object=main.o ApplicationThread.o UartThread.o UsrProtocol.o SocketThread.o Led.o Beep.o
CPPFLAG=
CLIBFLAG=-lpthread
CC=arm-linux-gnueabihf-g++
TARGET=system_app

$(TARGET):$(Object)
	$(CC) -o $(TARGET) $(Object) $(CLIBFLAG)
	chmod 777 $(TARGET)

main.o:main.cpp
	$(CC) $(CPPFLAG) -c main.cpp

ApplicationThread.o:source/ApplicationThread.cpp
	$(CC) $(CPPFLAG) -c source/ApplicationThread.cpp

UartThread.o:source/UartThread.cpp
	$(CC) $(CPPFLAG) -c source/UartThread.cpp

SocketThread.o:source/SocketThread.cpp
	$(CC) $(CPPFLAG) -c source/SocketThread.cpp

UsrProtocol.o:source/UsrProtocol.cpp
	$(CC) $(CPPFLAG) -c source/UsrProtocol.cpp

Led.o:driver/Led.cpp
	$(CC) $(CPPFLAG) -c driver/Led.cpp

Beep.o:driver/Beep.cpp
	$(CC) $(CPPFLAG) -c driver/Beep.cpp

.PHYONE: clean
clean:
	rm -rf $(TARGET) *.o
