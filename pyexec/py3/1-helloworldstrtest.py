#!/usr/bin/python3
 
print("Hello, World!")

flag = False

if flag:
    print("Hello, true world!")
else:
    print("hello, false wolrd!")

print("good bye!")

#Number, 4 types
# int
# bool: True, False
# float
# complex

str='James'
 
print(str)                 # 输出字符串
print(str[0:-1])           # 输出第一个到倒数第二个的所有字符
print(str[0])              # 输出字符串第一个字符
print(str[2:5])            # 输出从第三个开始到第五个的字符
print(str[2:])             # 输出从第三个开始的后的所有字符
print(str[1:4:2])          # 截取字符串， 1-4，步长2
print(str * 2)             # 输出字符串两次
print(str + '你好')        # 连接字符串
 
print('------------------------------')
 
print('hello\nJames')      # 使用反斜杠(\)+n转义特殊字符
print(r'hello\nJames')     # 在字符串前面添加一个 r，表示原始字符串，不会发生转义, r-> raw string

x="a"
y="b"
# 换行输出
print( x )
print( y )
 
print('---------')
# 不换行输出
print( x, end="" )
print( y, end="" )
print()

