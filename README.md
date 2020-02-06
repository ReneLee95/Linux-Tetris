Linux version 0.1.1 Tetris

this program is used to RaspberryPi3 B(raspbian)
you most install wiringPi

Let's introduce my program and how can we test program

main screan you can look four function , 1. gamestart   2. rank ( not implemented )   3. creater introduce   4. exit

go in gamestart, you can input your name.
next mode select                                                                                                                     =>my Linus tetris have two mode (newbie = easy , expert)
how different easy mode & expert??
easy mode : you can display mirror block. this block is already to show block position. and see a next block 

expert mode : you can't see two information ( mirror block and next block )

finally we are enjoy tetris game

if attain per one thousand , then game speed up 0.05 second (default speed 0.5)


* test program
First. install wiringPi

typing this command
command : git clone git://git.drogon.net/wiringPi

Why should we use to wiringPi ? my tetris program use the Gpio for sensor(Button , LED)
if you're not want use sensor, then you can modify my code.
look at gamestart() function. you can see triger and switch & case.
you can allocate another value. and modify int n = allocate value;
next case value modify you want input data.

Second. refer to macro, raspberrypi gpio connect sensor ( Pull up , Pull down does not matter)

Third. compile program.cpp

command : g++ -o Tetris tetris.cpp tetris.h map.h block.h sensor.h -lwiringPi

Last. test tetris program

command : ./Tetris

thank you for using my tetris program
