Object=main.o ApplicationThread.o UartThread.o UsrProtocol.o Led.o Beep.o
CPPFLAG=
CLIBFLAG=-lpthread
CC=arm-linux-gnueabihf-g++
TARGET=system_app

$(TARGET):$(Object)
	$(CC) -o $(TARGET) $(Object) $(CLIBFLAG)
	chmod 777 $(TARGET)

main.o:main.cpp
	$(CC) $(CPPFLAG) -c main.cpp

ApplicationThread.o:ApplicationThread.cpp
	$(CC) $(CPPFLAG) -c ApplicationThread.cpp

UartThread.o:UartThread.cpp
	$(CC) $(CPPFLAG) -c UartThread.cpp

UsrProtocol.o:UsrProtocol.cpp
	$(CC) $(CPPFLAG) -c UsrProtocol.cpp

Led.o:driver/Led.cpp
	$(CC) $(CPPFLAG) -c driver/Led.cpp

Beep.o:driver/Beep.cpp
	$(CC) $(CPPFLAG) -c driver/Beep.cpp

.PHYONE: clean
clean:
	rm -rf $(TARGET) *.o
