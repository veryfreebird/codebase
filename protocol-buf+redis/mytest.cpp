/* 
 * File:   main.cpp
 * Author: Vicky.H
 * Email:  eclipser@163.com
 */
#include <iostream>
#include <fstream>
#include "person.pb.h"
#include "hiredis.h"

/*
 * 
 */
int main(void) {

    // 创建User对象
    cn::vicky::model::seri::User u;
    u.set_id(1);
    u.set_username("Jack");
    u.set_password("123456");
    u.set_email("289997171@qq.com");

    // 创建User中的一个角色
    cn::vicky::model::seri::Person* _person1 = u.add_person();
    _person1->set_id(1);
    _person1->set_name("P1");

    // 创建角色中的一个电话号码:1
    cn::vicky::model::seri::PhoneNumber* _phone1 = _person1->add_phone();
    _phone1->set_number("+8613618074943");
    _phone1->set_type(cn::vicky::model::seri::MOBILE);

    // 创建角色中的一个电话号码:2
    cn::vicky::model::seri::PhoneNumber* _phone2 = _person1->add_phone();
    _phone2->set_number("02882334717");
    _phone2->set_type(cn::vicky::model::seri::WORK);


    // 创建User中的一个角色
    cn::vicky::model::seri::Person* _person2 = u.add_person();
    _person2->set_id(2);
    _person2->set_name("P2");

    // 创建角色中的一个电话号码:1
    cn::vicky::model::seri::PhoneNumber* _phone3 = _person2->add_phone();
    _phone3->set_number("+8613996398667");
    _phone3->set_type(cn::vicky::model::seri::MOBILE);

    // 创建角色中的一个电话号码:2
    cn::vicky::model::seri::PhoneNumber* _phone4 = _person2->add_phone();
    _phone4->set_number("02882334717");
    _phone4->set_type(cn::vicky::model::seri::WORK);


    std::cout << "----------Following uses Disk file for persistent-----------------" << std::endl;

    // 持久化到文件:
    std::fstream out("User.pb", std::ios::out | std::ios::binary | std::ios::trunc);
    u.SerializeToOstream(&out);
    out.close();

    // 从文件对象化:
    cn::vicky::model::seri::User u2;
    std::fstream in("User.pb", std::ios::in | std::ios::binary);
    if (!u2.ParseFromIstream(&in)) {
        std::cerr << "Failed to parse User.pb." << std::endl;
        exit(1);
    }
    
    std::cout << u2.id() << std::endl;
    std::cout << u2.username() << std::endl;
    std::cout << u2.password() << std::endl;
    std::cout << u2.email() << std::endl;

    std::cout << "---------------------------" << std::endl;
    for(int i = 0;i < u2.person_size();i++) {
        cn::vicky::model::seri::Person* p = u2.mutable_person(i);
        std::cout << p->id() << std::endl;
        std::cout << p->name() << std::endl;
        for (int j = 0;j < p->phone_size();j++) {
            cn::vicky::model::seri::PhoneNumber* phone = p->mutable_phone(j);
            std::cout << phone->number() << std::endl;
        }
        std::cout << "---------------------------" << std::endl;
    }

    std::cout << "----------Following uses Redis for persistent-----------------" << std::endl;
    
    
    //将对象以二进制保存  
    const int byteSize = u.ByteSize();  
    std::cout << "byteSize = " << byteSize << std::endl;  
    char buf[byteSize];  
    bzero(buf, byteSize);  
    u.SerializeToArray(buf, byteSize);  


    // 建立redis链接  
    redisContext *c;  
    redisReply *reply;  

    struct timeval timeout = {1, 500000}; // 1.5 seconds  
    c = redisConnectWithTimeout((char*) "10.133.141.167", 6379, timeout);  
    if (c->err) {  
    printf("Connection error: %s\n", c->errstr);  
    exit(1);  
    }  

    //第一次执行:将对象写入redis数据库  
    reply = (redisReply*) redisCommand(c, "SET %b %b", u.username().c_str(), (int) u.username().length(), buf, byteSize); // 重点!!!  
    printf("SET (binary API): %s\n", reply->str);  
    freeReplyObject(reply);  

    //第二次执行:从redis数据库读取对象数据  
    reply = (redisReply*) redisCommand(c, "Get Jack");  
    std::cout << "reply->len = " << reply->len << "\nreply->str : \n" << reply->str << std::endl; // 这里打印不完  

    std::cout << u2.id() << std::endl;
    std::cout << u2.username() << std::endl;
    std::cout << u2.password() << std::endl;
    std::cout << u2.email() << std::endl;

    std::cout << "---------------------------" << std::endl;
    for(int i = 0;i < u2.person_size();i++) {
        cn::vicky::model::seri::Person* p = u2.mutable_person(i);
        std::cout << p->id() << std::endl;
        std::cout << p->name() << std::endl;
        for (int j = 0;j < p->phone_size();j++) {
            cn::vicky::model::seri::PhoneNumber* phone = p->mutable_phone(j);
            std::cout << phone->number() << std::endl;
        }
        std::cout << "---------------------------" << std::endl;
    }

    return 0;
}

