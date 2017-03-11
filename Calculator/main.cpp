//
//  main.cpp
//  Calculator
//
//  Created by 赵毅 on 3/5/17.
//  Copyright © 2017 赵毅. All rights reserved.
//

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
using namespace std;

class Calculator {
    const char TABLE[7][7] = {{ 1,  1, -1, -1, -1,  1,  1},
        {1,  1, -1, -1, -1,  1,  1},
        {1,  1,  1,  1, -1,  1,  1},
        {1,  1,  1,  1, -1,  1,  1},
        {-1, -1, -1, -1, -1,  0,  9},
        {1,  1,  1,  1,  9,  1,  1},
        {-1, -1, -1, -1, -1,  9,  0}};
    const char OPC[7] = {'+', '-', '*', '/', '(', ')', '='};
    
    vector<double> nums;
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
    double operate(double a, char op, double b){
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
    double my_stod(string a){
        return stod("0"+a);
    }
public:
    Calculator(){
        nums.clear();
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
                            double a=nums[nums.size()-2];
                            double b=nums[nums.size()-1];
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
        if(is_num(ch)){
            if(nums.size()<ops.size()){
                temp_input="";
                nums.push_back(0.0);
            }
            if(temp_input.find(ch)==string::npos) temp_input=temp_input+ch;
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

int main(void){
    Calculator s;
    //    cout<<s.update("1-2+3=")<<endl;
    while(s.isactive()){
        string str;
        cin>>str;
        cout<<s.update(str)<<endl;
    }
}
