//
//  main.cpp
//  market-1
//
//  Created by 康悦 on 12-12-4.
//  Copyright (c) 2012年 ky. All rights reserved.
//

#include <iostream>
#include <vector>
#include <stdlib.h>
#include "market.h"
//定义foreach语句
#define foreach(elementType, element, containerType, container) \
    for (containerType::iterator iter = container.begin(); iter != container.end(); iter++)\
    for (bool go = true; go;)\
    for (elementType & element = *iter;go; go=false)


using namespace std;

manager cage = manager(0,0);

//void init_Vcus(){
//    for (int i=10; i<20; i++) {
//        Vcus.push_back(customer(i, i, 200));
//    }
//};

int check_cus_login(int uid,int pwd){
    foreach(customer, t, vector<customer>, Vcus){
        if(uid==t.get_uid()&&pwd==t.get_password())
        {t.login();customer_now=&t;return 0;}
    }
    return 1;
};

void init_market(float fund,float income){
    G_market.set_fund(fund);
    G_market.set_income(income);
};

void init_drink(int number,int ts,float price,float cb){
    G_drink.set_number(number);
    G_drink.set_totalsold(ts);
    G_drink.set_price(price);
    G_drink.set_chengben(cb);
};

void init_food(int number,int ts,float price,float cb){
    G_food.set_number(number);
    G_food.set_totalsold(ts);
    G_food.set_price(price);
    G_food.set_chengben(cb);
};

void init_electricity(int number,int ts,float price,float cb){
    G_electricity.set_number(number);
    G_electricity.set_totalsold(ts);
    G_electricity.set_price(price);
    G_electricity.set_chengben(cb);
};

//void writeback_cusinfo(){
//    foreach(customer, t, vector<customer>, Vcus){
//        if (t.get_uid()==(*customer_now).get_uid()) {
//            t.set_fund((*customer_now).get_fund());
//            return;
//        }
//    }
//};

int init_files(){  //打开log文件和data数据文件，以准备init所有用户的信息以及记录所有操作
    try {
        infs.open("data.txt",ios::binary);
    } catch (exception & e) {
        cout<<"Error! "<<e.what()<<endl;
        return 1;
    }
//    try {
//        outfs.open("data.dat",ios::binary|ios::ate);
//    } catch (exception &e) {
//        cout<<"Error! "<<e.what()<<endl;
//        return 1;
//    }
    try {
        logfs.open("log.txt",ios::binary|ios::app);
    } catch (exception &e) {
        cout<<"Error! "<<e.what()<<endl;
        return 1;
    }
    return 0;
};

int init_from_file(){
    float fa,fb;
    int ia,ib,ic;
    string temp;
    
    getline(infs,temp); //初始化超市信息
    fa=stof(temp);
    getline(infs,temp);
    fb=stof(temp);
    init_market(fa, fb);
    
    for (int i=0; i<3; i++) {   //初始化三种商品的信息
        getline(infs,temp);
        ia=stoi(temp);
        getline(infs,temp);
        ib=stoi(temp);
        getline(infs,temp);
        fa=stof(temp);
        getline(infs,temp);
        fb=stof(temp);
        switch (i) {
            case 0:
                init_drink(ia, ib, fa, fb);
                break;
            case 1:
                init_food(ia, ib, fa, fb);
                break;
            case 2:
                init_electricity(ia, ib, fa, fb);
                break;
            default:
                break;
        }
    }
    
    getline(infs,temp);   //读取顾客数量
    ic=stoi(temp);
    
    for (int i=0; i<ic; i++) {  //将顾客信息添加到Vcus中
        getline(infs,temp);
        ia=stoi(temp);
        getline(infs,temp);
        ib=stoi(temp);
        getline(infs,temp);
        fa=stof(temp);
        Vcus.push_back(customer(ia, ib, fa));
    }
    
    return 0;
}

int save_state(){
    try {
        outfs.open("data.txt",ios::binary|ios::trunc);
    } catch (exception &e) {
        cout<<"Error! "<<e.what()<<endl;
        return 1;
    }
    outfs<<G_market.get_fund()<<endl;
    outfs<<G_market.get_income()<<endl;
    outfs<<G_drink.get_number()<<endl;
    outfs<<G_drink.get_totalsold()<<endl;
    outfs<<G_drink.get_price()<<endl;
    outfs<<G_drink.get_chengben()<<endl;
    outfs<<G_food.get_number()<<endl;
    outfs<<G_food.get_totalsold()<<endl;
    outfs<<G_food.get_price()<<endl;
    outfs<<G_food.get_chengben()<<endl;
    outfs<<G_electricity.get_number()<<endl;
    outfs<<G_electricity.get_totalsold()<<endl;
    outfs<<G_electricity.get_price()<<endl;
    outfs<<G_electricity.get_chengben()<<endl;
    outfs<<Vcus.size()<<endl;
    for (int i=0; i<Vcus.size(); i++) {
        outfs<<Vcus[i].get_uid()<<endl;
        outfs<<Vcus[i].get_password()<<endl;
        outfs<<Vcus[i].get_fund()<<endl;
    }
    return 0;
}
int main(int argc, const char * argv[])
{
    if(init_files())
        return 0;   //如果打开文件失败，则退出
    init_from_file();  //从文件读取超市信息，物品信息以及顾客信息，并初始化
//    init_Vcus();
//    init_market(10000, 0);
//    init_drink(20, 0, 5.0, 3.5);
//    init_food(20, 0, 15.0, 11.5);
//    init_electricity(20, 0, 50.0, 38.0);
    int uid,pwd;

login:
    cout<<"Input your userid(Input -1 to exit):";
    cin>>uid;
    if (uid<0) {
        save_state();
        return 0;
    }
    cout<<"Input your password:";
    cin>>pwd;
    
    if (uid==cage.get_uid()&&pwd==cage.get_password()) {
        cage.login();
        int choice=cage.list();
        while (choice!=0) {
            unsigned int c;
            switch (choice) {
                case 1:
                    cage.show();
                    break;
                case 2:
                    cout<<"How many drinks do you wanna add:";
                    cin>>c;
                    G_drink.load(c);
                    break;
                case 3:
                    cout<<"How many foods do you wanna add:";
                    cin>>c;
                    G_food.load(c);
                    break;
                case 4:
                    cout<<"How many electricities do you wanna add:";
                    cin>>c;
                    G_electricity.load(c);
                    break;
                default:
                    cout<<"Please input a correct choice."<<endl;
                    break;
            }
            choice=cage.list();
        }
        customer_now=NULL;
        goto login;
    }
    else if(!check_cus_login(uid, pwd)){
        int choice=customer_now->list();
        while (choice!=0) {
            switch (choice) {
                case 1:
                    int t;
                    cout<<"How many do you wanna buy?"<<endl;
                    cin>>t;
                    G_drink.cost(t);
                    customer_now->showinfo();
                    break;
                case 2:
                    cout<<"How many do you wanna buy?"<<endl;
                    cin>>t;
                    G_food.cost(t);
                    customer_now->showinfo();
                    break;
                case 3:
                    cout<<"How many do you wanna buy?"<<endl;
                    cin>>t;
                    G_electricity.cost(t);
                    customer_now->showinfo();
                    break;
                case 4:
                    customer_now->charge();
                    break;
                default:
                    cout<<"Please input a correct choice."<<endl;
                    break;
            }
            choice=customer_now->list();
        }
        goto login;
    }
    else{
        cout<<"Wrong user id or password!!"<<endl;
        goto login;
    }
    
    return 0;
}

