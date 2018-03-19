#include <bits/stdc++.h>
#include <cxxabi.h>
#define eb emplace_back
#define X first
#define Y second
#define endl '\n'
#define tell(args...){string s_args=#args;replace(s_args.begin(),s_args.end(),',',' ');stringstream arg_names(s_args);istream_iterator<string>it(arg_names);cerr<<"["<<__LINE__<<"]  ";__tell(it,args);}
using namespace std;
template<class T>string get_type(T&&a){int stt;char*tmp=abi::__cxa_demangle(typeid(a).name(),0,0,&stt);string res(tmp);free(tmp);return res;}
template<class T>void __tell(auto&& name, T&& a){cerr<<"("<<get_type(a)<<")"<<name<<" = "<<a;}
template<class T>void __tell(istream_iterator<string>a_name,T&&a){__tell(*a_name, a);cerr<<"|\n";}
template<class T,class... Ts>void __tell(istream_iterator<string>a_name,T&&a,Ts&&...args){__tell(*a_name,a);cerr<<" --- ";__tell(++a_name,args...);}
