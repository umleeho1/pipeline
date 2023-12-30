CC = gcc -O2
OBJS = CU.o DM.o FW.o HU.o IM.o RF.o ADDR.o ALU.o main.o LAT.o LOG.o MUX.o
TARGET = main

clean:
	rm -f *.o
	rm -f $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

CU.o: CU.c
DM.o: DM.c
FW.o: FW.c
HU.o: HU.c
IM.o: IM.c
RF.o: RF.c
ADDR.o: ADDR.c
ALU.o: ALU.c
GSH.o: GSH.c
LAT.o: LAT.c
LOG.o: LOG.c
MUX.o: MUX.c

main.o: cpu.h instruction.h register.h main.c