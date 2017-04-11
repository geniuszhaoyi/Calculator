//
//  main.cpp
//  leetcode3
//
//  Created by 赵毅 on 4/8/17.
//  Copyright © 2017 赵毅. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <set>
using namespace std;

//#define USE_DOUBLE
#ifdef USE_DOUBLE
#define DOUBLE double
#else
#define DOUBLE long long int
#endif

class Calculator {
    const char TABLE[7][7] = {{ 1,  1, -1, -1, -1,  1,  1},
        {1,  1, -1, -1, -1,  1,  1},
        {1,  1,  1,  1, -1,  1,  1},
        {1,  1,  1,  1, -1,  1,  1},
        {-1, -1, -1, -1, -1,  0,  9},
        {1,  1,  1,  1,  9,  1,  1},
        {-1, -1, -1, -1, -1,  9,  0}};
    const char OPC[7] = {'+', '-', '*', '/', '(', ')', '='};
    
    vector<DOUBLE> nums;
    vector<char> ops;
    string temp_input;
    
    bool is_op(char ch){
        string str="+-*x/()=";
        if(str.find(ch)!=string::npos) return true;
        return false;
    }
    bool is_num(char ch){
        string str="0123456789.";
        if(str.find(ch)!=string::npos) return true;
        return false;
    }
    int opc_opn(char c){
        for(int i=0;i<7;i++) if(OPC[i]==c) return i;
        return -1;
    }
    int cmp_op(char a, char b){
        if(a=='x') a='*';
        if(b=='x') b='*';
        return TABLE[opc_opn(a)][opc_opn(b)];
    }
    DOUBLE operate(DOUBLE a, char op, DOUBLE b){
        switch (op) {
            case '+':
                return a+b;
            case '-':
                return a-b;
            case '*':
            case 'x':
                return a*b;
            case '/':
                return a/b;
        }
        return 0.0;
    }
    template<typename T, typename A>
    static void printvector(string name, vector<T,A> a){
        cout<<name<<":\t";
        for(int i=0;i<a.size();i++){
            cout<<a[i]<<"\t";
        }
        cout<<endl;
    }
    DOUBLE my_stod(string a){
        // cout<<a<<endl;
        return stoll("0"+a);
        //        return stod("0"+a);
    }
public:
    Calculator(){
        nums.clear();
        temp_input="";
        nums.push_back(0);
        ops.clear();
        ops.push_back('=');
    }
    string update(char ch){
        // = + - * / sin cos tan pi
        if(is_op(ch)){
            char flag=1;
            while(flag){
                switch (cmp_op(ops[ops.size()-1],ch)) {
                    case 0:
                        ops.pop_back();
                        flag=0;
                        break;
                    case -1:
                        ops.push_back(ch);
                        flag=0;
                        break;
                    case 1:
                        if(ops.size() && nums.size()>1){
                            char op=ops[ops.size()-1];
                            ops.pop_back();
                            DOUBLE a=nums[nums.size()-2];
                            DOUBLE b=nums[nums.size()-1];
                            nums.pop_back();
                            nums.pop_back();
                            nums.push_back(operate(a,op,b));
                        }
                    case 9:
                        // throw error
                        break;
                }
            }
        }
        if(ch=='+' || ch=='-' || ch=='*' || ch=='/'){
            temp_input="";
            nums.push_back(0);
        }
        if(is_num(ch)){
            // if(nums.size()<ops.size()){
            // }
            // if(temp_input.find(ch)==string::npos)
            temp_input=temp_input+ch;
            nums[nums.size()-1]=my_stod(temp_input);
        }
        return to_string(nums[nums.size()-1]);
    }
    string update(string str) {
        string ans;
        for(int i=0;i<str.length();i++){
            ans=update(str.at(i));
            //            cout<<str.at(i)<<endl;
            //            printvector("nums",nums);
            //            printvector("ops",ops);
        }
        return ans;
    }
    string display(){
        return to_string(nums[nums.size()-1]);
    }
    bool isactive(){
        if(ops.size()>0 && ops[0]=='=') return true;
        return false;
    }
};


class Solution {
public:
    int calculate(string s) {
        string input="";
        for(int i=0;i<s.length();i++){
            if(s[i]!=' ') input+=s[i];
        }
        input="0+"+input+"=";
        Calculator c;
        c.update(input);
        return stoi(c.display());
    }
};

int main(void){
    Calculator c;
    string str="";
    while(str!="="){
        cin>>str;
        c.update(str);
        cout<<c.display()<<endl;
    }
}
