#include <iostream>
#include <cstdio>
#include <fstream>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
//#include "parser/tree.h"
#include "parser/tokens.h"

using namespace std;

const int MAX_PATH = 1000;

int main(int argc, char* argv[]) {
    char buffer[MAX_PATH];
    getcwd(buffer, MAX_PATH);
    if(argc > 1){
        printf("argc %d\n", argc);
        printf("argv %s\n", argv[1]);
        strcat(buffer, "/");
        strcat(buffer, argv[1]);

        FILE* fp=fopen(buffer, "r");
        if(fp == NULL)
        {
            printf("cannot open %s\n", buffer);
            return -1;
        }
        extern FILE* yyin;				//yyin和yyout都是FILE*类型
        yyin=fp;						//yacc会从yyin读取输入，yyin默认是标准输入，这里改为磁盘文件。yacc默认向yyout输出，可修改yyout改变输出目的

        printf("-----begin parsing %s\n", buffer);
        yyparse();						//使yacc开始读取输入和解析，它会调用lex的yylex()读取记号
        puts("-----end parsing");

        fclose(fp);
        // if( (access( "okkk", 0 )) != -1 ){
        //     cout << "database " << "okkk" << " was created before" << endl;
        // } else {
        //     int isCreate = mkdir("okkk", S_IRWXU);
        //     if( !isCreate )
        //         cout << "database " << "okkk" << " has been created" << endl;
        //     else
        //         cout << "create path failed!" << endl;
            
        // }
    } else{
        cout << "输入系统命令所在的文件" << endl;
    }

    return 0;

}
