/* 
 * File:   main.cpp
 * Author: Vicky.H
 * Email:  eclipser@163.com
 */
#include <iostream>
#include <fstream>
#include "person.pb.h"
#include "sessions.pb.h"
#include "hiredis.h"

/*
 * 
 */
int main(int argc, char **argv) {
    nokia::asrnc::eipu::gtp gtp_session;
    gtp_session.set_ul_ip_idx       (1234);
    gtp_session.set_fwd_ip_idx      (1234);
    gtp_session.set_dl_ip_idx       (1234);
    gtp_session.set_dl_tei          (1234);
    gtp_session.set_ul_tei          (1234);
    gtp_session.set_fwd_tei         (1234);
    gtp_session.set_conn_id         (1234);
    gtp_session.set_aap_pid         (1234);
    gtp_session.set_l3_pid          (1234);
    gtp_session.set_l3_computer     (1234);
    gtp_session.set_ipbr_id         (1234);
    gtp_session.set_vrf_id          (1234);
    gtp_session.set_error_ind_cnt   (1234);
    gtp_session.set_pdcp_lid        (1234);
    gtp_session.set_imsi_id         (1234);
    gtp_session.set_mon_status      (1234);
    gtp_session.set_process_owner   (1234);
    gtp_session.set_phb             (1234);
    gtp_session.set_dl_dscp         (1234);
    gtp_session.set_qos_class       (1234);
    gtp_session.set_rab_state       (1234);
    gtp_session.set_saved_rab_state (1234);
    gtp_session.set_tunnel_reserved (1234);
    gtp_session.set_sv_inactive     (1234);
    gtp_session.set_fwd_ip_exist    (1234);
    gtp_session.set_dmpg_switch     (1234);
    gtp_session.set_pdcp_forward    (1234);
    gtp_session.set_que_id          (1234);
    gtp_session.set_fwd_state       (1234);

    nokia::asrnc::eipu::udp udp_session;
    udp_session.set_index         (9999);
    udp_session.set_flag          (9999);
    udp_session.set_free          (9999);
    udp_session.set_addr          (9999);
    udp_session.set_id            (9999);
    udp_session.set_id_hdr        (9999);
    udp_session.set_addr_hdr      (9999);
    udp_session.set_conn_id       (9999);
    udp_session.set_trace_id      (9999);
    udp_session.set_local_addr    (9999);
    udp_session.set_remote_addr   (9999);
    udp_session.set_flow_id       (9999);
    udp_session.set_unit_addr     (9999);
    udp_session.set_own_unit      (9999);
    udp_session.set_bind          (9999);
    udp_session.set_owner_id      (9999);
    udp_session.set_ifc           (9999);
    udp_session.set_muxi          (9999);
    udp_session.set_mux_src       (9999);
    udp_session.set_mux_dst       (9999);
    udp_session.set_l3_pid        (9999);
    udp_session.set_mon_type      (9999);
    udp_session.set_imsi          (9999);
    udp_session.set_mon_status    (9999);
    udp_session.set_max_mux_count (9999);

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
    const char *hostname = (argc > 1) ? argv[1] : "10.133.141.167";
 
    
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
    c = redisConnectWithTimeout(hostname, 6379, timeout);  
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

    cn::vicky::model::seri::User u3;
    u3.ParseFromArray(reply->str, reply->len); //反序列化

    std::cout << u3.id() << std::endl;
    std::cout << u3.username() << std::endl;
    std::cout << u3.password() << std::endl;
    std::cout << u3.email() << std::endl;

    std::cout << "---------------------------" << std::endl;
    for(int i = 0;i < u3.person_size();i++) {
        cn::vicky::model::seri::Person* p = u3.mutable_person(i);
        std::cout << p->id() << std::endl;
        std::cout << p->name() << std::endl;
        for (int j = 0;j < p->phone_size();j++) {
            cn::vicky::model::seri::PhoneNumber* phone = p->mutable_phone(j);
            std::cout << phone->number() << std::endl;
        }
        std::cout << "---------------------------" << std::endl;
    }

    std::cout << "----------Following uses Redis for persistenti of gtp udp session state-----------------" << std::endl;
    
    //将对象以二进制保存  
    const int byteSize1 = gtp_session.ByteSize();  
    std::cout << "GTP session byteSize = " << byteSize1 << std::endl;  
    char buf1[byteSize1];  
    bzero(buf1, byteSize1);  
    gtp_session.SerializeToArray(buf1, byteSize1);  

    //第一次执行:将对象写入redis数据库  
    reply = (redisReply*) redisCommand(c, "SET %d %b", gtp_session.conn_id(), buf1, byteSize1); // 重点!!!  
    printf("SET (binary API): %s\n", reply->str);  
    freeReplyObject(reply);  

    //第二次执行:从redis数据库读取对象数据  
    reply = (redisReply*) redisCommand(c, "Get 1234");  
    std::cout << "reply->len = " << reply->len << "\nreply->str : \n" << reply->str << std::endl; // 这里打印不完  
    
    nokia::asrnc::eipu::gtp gtp_session_restored;
    gtp_session_restored.ParseFromArray(reply->str, reply->len);

    std::cout << gtp_session_restored.ul_ip_idx() << std::endl;
    std::cout << gtp_session_restored.fwd_ip_idx() << std::endl;
    std::cout << gtp_session_restored.dl_ip_idx() << std::endl;
    std::cout << gtp_session_restored.conn_id() << std::endl;


    //将对象以二进制保存  
    const int byteSize2 = udp_session.ByteSize();  
    std::cout << "UDP session byteSize = " << byteSize2 << std::endl;  
    char buf2[byteSize2];  
    bzero(buf2, byteSize2);  
    udp_session.SerializeToArray(buf2, byteSize2);  

    //第一次执行:将对象写入redis数据库  
    reply = (redisReply*) redisCommand(c, "SET %d %b", udp_session.conn_id(), buf2, byteSize2); // 重点!!!  
    printf("SET (binary API): %s\n", reply->str);  
    freeReplyObject(reply);  

    //第二次执行:从redis数据库读取对象数据  
    reply = (redisReply*) redisCommand(c, "Get 9999");  
    std::cout << "reply->len = " << reply->len << "\nreply->str : \n" << reply->str << std::endl; // 这里打印不完  
    
    nokia::asrnc::eipu::udp udp_session_restored;
    udp_session_restored.ParseFromArray(reply->str, reply->len);

    std::cout << udp_session_restored.conn_id() << std::endl;
    std::cout << udp_session_restored.ifc() << std::endl;
    std::cout << udp_session_restored.id() << std::endl;
    return 0;
}

