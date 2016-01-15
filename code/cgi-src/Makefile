SRC=cgi_common.c writeTermioParas.c
TARGET=writeTermioParas.cgi

start:
	g++ $(SRC) -o $(TARGET)

arm-compile:
	arm-linux-g++ $(SRC) -o $(TARGET)

clean:
	rm -fr $(TARGET)
