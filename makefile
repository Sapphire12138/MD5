TARGET = mainProgram.exe
CODEFILE = src
SOURCECODE = main.cpp MD5.cpp
MIDDLEFILE = main.o MD5.o
CONDITION = -std=c++11
G = g++

$(TARGET) : $(MIDDLEFILE)
	@if exist $(TARGET) del $(TARGET)
	$(G) $(MIDDLEFILE) -o $(TARGET) $(CONDITION)
	@make clean
	@echo $(TARGET) is constructed successfully.

main.o : $(CODEFILE)\main.cpp
	@if exist main.o del main.o
	$(G) -c $(CODEFILE)\main.cpp -o main.o $(CONDITION)
	@echo main.cpp is compiled successfully.

MD5.o : $(CODEFILE)\MD5.cpp
	@if exist MD5.o del MD5.o
	$(G) -c $(CODEFILE)\MD5.cpp -o MD5.o $(CONDITION)
	@echo MD5.cpp is compiled successfully.

.PHONY : clean

clean : 
	@rm -f $(MIDDLEFILE)
	@echo $(MIDDLEFILE) is deleted successfully.