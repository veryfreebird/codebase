from microbit import *
#write your program:
name="xxx"
flag=False
while True:
    if uart.any():
        s=str(uart.readall(),"UTF-8").strip("\n")
        light = pin1.read_analog()
        x=name+" 1 "+str(light)
        print(x)
        if s=="1":
            pin2.write_digital(1)
            display.show(1)
        elif s=="2":
            pin2.write_digital(0)
            display.show(2)            
    else:
        display.show(Image.SAD)
    sleep(1000)
