#!/usr/bin/python3

#http://www.runoob.com/python3/python3-data-type.html

counter = 100          # 整型变量
miles   = 1000.0       # 浮点型变量
name    = "james"     # 字符串
 
print (counter)
print (miles)
print (name)

counter, miles, name = 111, 1.1, 'james2'
print(counter, miles, name)

###Python3 中有六个标准的数据类型：
#Python3 的六个标准数据类型中：
##不可变数据（3 个）：Number（数字）、String（字符串）、Tuple（元组）；
##可变数据（3 个）：List（列表）、Dictionary（字典）、Set（集合）。

#Number（数字）: int, float, bool, complex
print ("+++++++++++++++++Number examples+++++++++++++++++") 
print(type(counter),type(miles), type(name))

##/ 返回一个浮点数，// 返回一个整数。
print(type(4/2),type(4//2))
#在混合计算时，Python会把整型转换成为浮点数。

comp1 = 1+2j
comp2 = complex(1,4)
print(comp1, type(comp1),comp2, isinstance(comp2, complex))

floatnum = 32.33e+20
print(floatnum, type(floatnum))

#String（字符串）
#索引值以 0 为开始值，-1 为从末尾的开始位置。
print ("+++++++++++++++++String examples+++++++++++++++++") 
str = 'Helloworld'
print (str)          # 输出字符串
print (str[0:-1])    # 输出第一个到倒数第二个的所有字符
print (str[0])       # 输出字符串第一个字符
print (str[2:5])     # 输出从第三个开始到第五个的字符
print (str[2:])      # 输出从第三个开始的后的所有字符
print (str * 2)      # 输出字符串两次
print (str + "TEST") # 连接字符串

#使用反斜杠(\)转义特殊字符，如果你不想让反斜杠发生转义，可以在字符串前面添加一个 r，表示原始字符串
print('Ru\noob')
print(r'Ru\noob')


#Tuple（元组）
#元组（tuple）与列表类似，不同之处在于元组的元素不能修改。元组写在小括号 () 里，元素之间用逗号隔开
print ("+++++++++++++++++Tuple examples+++++++++++++++++") 
tuple = ( 'abcd', 786 , 2.23, 'runoob', 70.2  )
tinytuple = (123, 'runoob')
print (tuple)             # 输出完整元组
print (tuple[0])          # 输出元组的第一个元素
print (tuple[1:3])        # 输出从第二个元素开始到第三个元素
print (tuple[2:])         # 输出从第三个元素开始的所有元素
print (tinytuple * 2)     # 输出两次元组
print (tuple + tinytuple) # 连接元组

#虽然tuple的元素不可改变，但它可以包含可变的对象，比如list列表。
#构造包含 0 个或 1 个元素的元组比较特殊，所以有一些额外的语法规则：
tup1 = ()    # 空元组
tup2 = (20,) # 一个元素，需要在元素后添加逗号
print(tup1, tup2)

#List（列表）
#和字符串一样，列表同样可以被索引和截取，列表被截取后返回一个包含所需元素的新列表。
#变量[头下标:尾下标]
print ("+++++++++++++++++List examples+++++++++++++++++") 
list = [ 'abcd', 786 , 2.23, 'runoob', 70.2 ]
tinylist = [123, 'runoob']
print (list)            # 输出完整列表
print (list[0])         # 输出列表第一个元素
print (list[1:3])       # 从第二个开始输出到第三个元素
print (list[2:])        # 输出从第三个元素开始的所有元素
print (tinylist * 2)    # 输出两次列表
print (list + tinylist) # 连接列表

#与Python字符串不一样的是，列表中的元素是可以改变的
a = [1, 2, 3, 4, 5, 6]
print(a)
a[2:5] = [13, 14, 15]
print(a)
#List 内置了有很多方法，例如 append()、pop() 

inputstr = "I love Rose"
inputwords = inputstr.split(" ")
inputwords = inputwords[-1::-1]
outputstr = ' '.join(inputwords)
print(inputstr, "=>", outputstr)

#Dictionary（字典）
print ("+++++++++++++++++Dictionary examples+++++++++++++++++") 
#列表是有序的对象集合，字典是无序的对象集合。两者之间的区别在于：字典当中的元素是通过键来存取的，而不是通过偏移存取。
#字典是一种映射类型，字典用 { } 标识，它是一个无序的 键(key) : 值(value) 的集合。
#键(key)必须使用不可变类型。
#在同一个字典中，键(key)必须是唯一的。
dict = {}
dict['one'] = "1 - 菜鸟教程"
dict[2]     = "2 - 菜鸟工具"
tinydict = {'name': 'runoob','code':1, 'site': 'www.runoob.com'}
print (dict['one'])       # 输出键为 'one' 的值
print (dict[2])           # 输出键为 2 的值
print (tinydict)          # 输出完整的字典
print (tinydict.keys())   # 输出所有键
print (tinydict.values()) # 输出所有值

#构造函数 dict() 可以直接从键值对序列中构建字典
websites = {('Runoob', 1), ('Google', 2), ('Taobao', 3)}
values = {x: x**2 for x in (2, 4, 6)}
#websites2 = {Runoob=1, Google=2, Taobao=3}
print(websites, values)
#字典类型也有一些内置的函数，例如clear()、keys()、values()等。

#Set（集合）
#集合（set）是由一个或数个形态各异的大小整体组成的，构成集合的事物或对象称作元素或是成员。
#基本功能是进行成员关系测试和删除重复元素。
#可以使用大括号 { } 或者 set() 函数创建集合，注意：创建一个空集合必须用 set() 而不是 { }，因为 { } 是用来创建一个空字典。
#parame = {value01,value02,...}
#或者
#set(value)
print ("+++++++++++++++++Set examples+++++++++++++++++") 
student = {'Tom', 'Jim', 'Mary', 'Tom', 'Jack', 'Rose'}
print(student)   # 输出集合，重复的元素被自动去掉
# 成员测试
if 'Rose' in student :
    print('Rose 在集合中')
else :
    print('Rose 不在集合中')

# set可以进行集合运算
a = set('abracadabra')
b = set('alacazam')
print(a,b)
print(a - b)     # a 和 b 的差集
print(a | b)     # a 和 b 的并集
print(a & b)     # a 和 b 的交集
print(a ^ b)     # a 和 b 中不同时存在的元素

#int(x [,base]) 将x转换为一个整数
#float(x) 将x转换到一个浮点数
#complex(real [,imag]) 创建一个复数
#str(x) 将对象 x 转换为字符串
#repr(x) 将对象 x 转换为表达式字符串
#eval(str) 用来计算在字符串中的有效Python表达式,并返回一个对象
#tuple(s) 将序列 s 转换为一个元组
#list(s) 将序列 s 转换为一个列表
#set(s) 转换为可变集合
#dict(d) 创建一个字典。d 必须是一个序列 (key,value)元组。
#frozenset(s) 转换为不可变集合
#chr(x) 将一个整数转换为一个字符
#ord(x) 将一个字符转换为它的整数值
#hex(x) 将一个整数转换为一个十六进制字符串
#oct(x) 将一个整数转换为一个八进制字符串