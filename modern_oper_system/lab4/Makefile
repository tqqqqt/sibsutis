main: num1-1 num1-2 num2 num3 num4

num1-1: main1_11.cpp /root/labs/plates.o
	g++ main1_11.cpp /root/labs/plates.o -l vg -o num1-1

num1-2: main1_22.cpp /root/labs/plates.o
	g++ main1_22.cpp /root/labs/plates.o -l vg -o num1-2

num2: main2-2.cpp /root/labs/plates.o
	g++ main2-2.cpp /root/labs/plates.o -l vg -o num2

num3: main3-2.cpp /root/labs/plates.o
	g++ main3-2.cpp /root/labs/plates.o -l vg -o num3

num4: main4-2.cpp /root/labs/plates.o
	g++ main4-2.cpp /root/labs/plates.o -l vg -o num4

.PHONY: clear
clear:
	rm -f num1-1
	rm -f num1-2
	rm -f num2
	rm -f num3
	rm -f num4