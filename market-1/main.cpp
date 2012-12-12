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

void init_Vcus(){
    for (int i=10; i<20; i++) {
        Vcus.push_back(customer(i, i, 200));
    }
};

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

void writeback_cusinfo(){
    foreach(customer, t, vector<customer>, Vcus){
        if (t.get_uid()==(*customer_now).get_uid()) {
            t.set_fund((*customer_now).get_fund());
            return;
        }
    }
}


int main(int argc, const char * argv[])
{
    init_Vcus();
    init_market(10000, 0);
    init_drink(20, 0, 5.0, 3.5);
    init_food(20, 0, 15.0, 11.5);
    init_electricity(20, 0, 50.0, 38.0);
    int uid,pwd;

login:
    cout<<"Input your userid(Input -1 to exit):";
    cin>>uid;
    if (uid<0) {
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

