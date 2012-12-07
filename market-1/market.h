//
//  market.h
//  market-1
//
//  Created by 康悦 on 12-12-4.
//  Copyright (c) 2012年 ky. All rights reserved.
//

#ifndef market_1_market_h
#define market_1_market_h

#endif
//声明两个user的类型，经理的user type为0，顾客的为1
#define _MNG 0
#define _CMR 1
using namespace std;

class market {
private:
    float fund;
    float income;
public:
    market(float fund,float income){this->fund=fund;this->income=income;};
    market(){};
    float get_fund(){return fund;};
    float set_fund(float fund){this->fund=fund;return fund;};
    float change_fund(float t){fund+=t;return fund;};
    float get_income(){return income;};
    float set_income(float income){this->income=income;return income;};
    float change_income(float t){income+=t;return income;};
};

market G_market;   //定义一个market全局变量

class user {
protected:
    int user_id;
    int password;
    int type;
public:
//    user(int uid,int pwd,int type){
//        user_id=uid;
//        password=pwd;
//        this->type=type;
//    }
    user(){};
    int login();
    int list();
    //int logtofile();
    int get_uid(){return user_id;};
    int get_password(){return password;};
    void set_uid(int uid){this->user_id=uid;};
    void set_password(int pwd){this->password=pwd;};
};

class customer: public user {
private:
    float fund;   //顾客当前账户上拥有的钱
public:
    customer(int uid,int pwd,int fund){
        user_id=uid;
        password=pwd;
        this->type=_CMR;
        this->fund=fund;
    }
    int login(){
        cout<<this->user_id<<" Login Successfully!"<<endl;
        showinfo();
        return 0;
    };
    int list();     //列出可操作的项目，返回用户输入的数字
    float get_fund(){return fund;};
    float set_fund(float fund){this->fund=fund;return fund;};
    float change_fund(float t){fund+=t;return fund;};
    void showinfo(){
        cout<<endl<<"Your user_id is "<<get_uid()<<endl;
        cout<<"Fund in your account "<<get_fund()<<endl<<endl;
    }
};
customer * customer_now=NULL;
vector<customer> Vcus;


class manager:public user {
private:
    
public:
    manager(int uid,int pwd){
        user_id=uid;
        password=pwd;
        type=_MNG;
    }
    int login(){
        cout<<"Manager Login Successfully!"<<endl;
        return 0;
    };
    int list(){
        int t;
        cout<<"Select a job you wanna do:"<<endl;
        cout<<"1.Show the SuperMarket info."<<endl;
        cout<<"2.Add some drinks."<<endl;
        cout<<"3.Add some foods."<<endl;
        cout<<"4.Add some electricities."<<endl;
        cout<<"0.Logout."<<endl;
        cin>>t;
        return t;
    };
    void show();
};



class goods {
protected:
    int number;
    int totalsold;
    float price;
    float chengben;
public:
    goods(){};
    float get_price(){return price;};
    float set_price(float price){this->price=price;return price;};
    float get_chengben(){return chengben;};
    float set_chengben(float chengben){this->chengben=chengben;return chengben;};
    int get_number(){return number;};
    int set_number(int n){this->number=n;return n;};
    int get_totalsold(){return totalsold;};
    int set_totalsold(int ts){this->totalsold=ts;return ts;};
    int change_number(int t){number+=t;return number;};
    int cost(unsigned int c);
    int load(unsigned int c);
    int soldout(unsigned int c){totalsold+=c;return totalsold;};
    void show(){
        cout<<"=  剩余件数:"<<get_number()<<endl;
        cout<<"=  共卖出件数:"<<get_totalsold()<<endl;
        cout<<"=  售价:"<<get_price()<<endl;
        cout<<"=  成本:"<<get_chengben()<<endl;
    }
    void showmin(){
        cout<<"售价:"<<get_price()<<"\t剩余件数:"<<get_number()<<endl;
    }
};


class drink:public goods{
private:
    
public:
    int cost(unsigned int c){
        if (c>get_number()) {
            cout<<"Not enough drinks."<<endl;
            return 1;
        }
        else if (c * get_price() > customer_now->get_fund()){
            cout<<"No Enough Money!"<<endl;
            return 2;
        }
        else {
            change_number(0-c);
            //修改流水资金，增加log文件中的条目，修改总收入，总卖出的件数
            G_market.change_fund(c*get_price());
            G_market.change_income((get_price() - get_chengben())*c);
            customer_now->change_fund(0-c*get_price());
            soldout(c);
            cout<<"Successful bought "<<c<<" drinks."<<endl;
        }
        return 0;
    };
    int load(unsigned int c){
        G_market.change_fund(0-get_chengben()*c);
        cout<<"Successful increase the number of drinks to "<<change_number(c)<<endl;
        //减少流水资金，增加当前数目，增加log文件中的条目。
        return 0;
    };
    void show(){
        cout<<"==="<<endl<<"=drink:"<<endl;
        goods::show();
    }
    void showmin(){
        cout<<"Drink:\t\t\t";
        goods::showmin();
    }
};
drink G_drink;

class food:public goods {
private:
    
public:
    int cost(unsigned int c){
        if (c>get_number()) {
            cout<<"Not enough foods."<<endl;
            return 1;
        }
        else if (c * get_price() > (*customer_now).get_fund()){
            cout<<"No Enough Money!"<<endl;
            return 2;
        }
        else {
            change_number(0-c);
            //修改流水资金，增加log文件中的条目，修改总收入，总卖出的件数
            G_market.change_fund(c*get_price());
            G_market.change_income((get_price() - get_chengben())*c);
            soldout(c);
            cout<<"Successful bought "<<c<<"foods."<<endl;
        }
        return 0;
    };
    int load(unsigned int c){
        G_market.change_fund(0-get_chengben()*c);
        cout<<"Successful increase the number of foods to "<<change_number(c)<<endl;
        //减少流水资金，增加当前数目，增加log文件中的条目。
        return 0;
    };
    void show(){
        cout<<"==="<<endl<<"=food:"<<endl;
        goods::show();
    }
    void showmin(){
        cout<<"Food:\t\t\t";
        goods::showmin();
    };
};
food G_food;

class electricity:public goods {
private:
    
public:
    int cost(unsigned int c){
        if (c>get_number()) {
            cout<<"Not enough electricities."<<endl;
            return 1;
        }
        else if (c * get_price() > (*customer_now).get_fund()){
            cout<<"No Enough Money!"<<endl;
            return 2;
        }
        else {
            change_number(0-c);
            //修改流水资金，增加log文件中的条目，修改总收入，总卖出的件数
            G_market.change_fund(c*get_price());
            G_market.change_income((get_price() - get_chengben())*c);
            soldout(c);
            cout<<"Successful bought "<<c<<"electricities."<<endl;
        }
        return 0;
    };
    int load(unsigned int c){
        G_market.change_fund(0-get_chengben()*c);
        cout<<"Successful increase the number of electricities to "<<change_number(c)<<endl;
        //减少流水资金，增加当前数目，增加log文件中的条目。
        return 0;
    };
    void show(){
        cout<<"==="<<endl<<"=electricity:"<<endl;
        goods::show();
    };
    void showmin(){
        cout<<"Electricity:\t";
        goods::showmin();
    };
};
electricity G_electricity;


void manager::show(){
    cout<<"==================================="<<endl;
    cout<<"=  流动资金:"<<G_market.get_fund()<<endl;
    cout<<"=  收入:"<<G_market.get_income()<<endl;
    G_drink.show();
    G_food.show();
    G_electricity.show();
    cout<<"==================================="<<endl;
}

int customer::list(){
    int t;
    G_drink.showmin();
    G_food.showmin();
    G_electricity.showmin();
    cout<<"Select a job you wanna do:"<<endl;
    cout<<"1.Buy drinks."<<endl;
    cout<<"2.Buy foods."<<endl;
    cout<<"3.Buy electricities."<<endl;
    cout<<"0.Logout."<<endl;
    cin>>t;
    return t;
}
