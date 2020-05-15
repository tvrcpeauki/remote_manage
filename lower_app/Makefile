Object=main.o app_task.o uart_task.o led.o protocol.o beep.o
CPPFLAG=
CLIBFLAG=-lpthread
CC=arm-linux-gnueabihf-g++
TARGET=system_app

$(TARGET):$(Object)
	$(CC) -o $(TARGET) $(Object) $(CLIBFLAG)
	chmod 777 $(TARGET)

main.o:main.cpp
	$(CC) $(CPPFLAG) -c main.cpp

app_task.o:app_task.cpp
	$(CC) $(CPPFLAG) -c app_task.cpp

uart_task.o:uart_task.cpp
	$(CC) $(CPPFLAG) -c uart_task.cpp

led.o:driver/led.cpp
	$(CC) $(CPPFLAG) -c driver/led.cpp

beep.o:driver/beep.cpp
	$(CC) $(CPPFLAG) -c driver/beep.cpp

protocol.o:protocol.cpp
	$(CC) $(CPPFLAG) -c protocol.cpp

.PHYONE: clean
clean:
	rm -rf $(TARGET) *.o
