#ifndef FILE_MANAGER
#define FILE_MANAGER
#include <string>
#include <stdio.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "../utils/MyBitMap.h"
#include "../utils/pagedef.h"
//#include "../MyLinkList.h"
using namespace std;
class FileManager {
private:
	int fd[MAX_FILE_NUM];
	bool used[MAX_FILE_NUM];
    std::string fileName[MAX_FILE_NUM];
//	MyBitMap* fm;
//	MyBitMap* tm;
	int _createFile(const char* name) {
		FILE* f = fopen(name, "a+");
		if (f == NULL) {
			cout << "fail" << endl;
			return -1;
		}
		fclose(f);
		return 0;
	}
	int _openFile(const char* name, int fileID) {
		int f = open(name, O_RDWR);
		if (f == -1) {
			return -1;
		}
		fd[fileID] = f;
		return 0;
	}
public:
	/*
	 * FilManager构造函数
	 */
	FileManager() {
		for (int i=0;i<MAX_FILE_NUM;++i)
			used[i]=false;
//		fm = new MyBitMap(MAX_FILE_NUM, 1);
//		tm = new MyBitMap(MAX_TYPE_NUM, 1);
	}
	/*
	 * @函数名writePage
	 * @参数fileID:文件id，用于区别已经打开的文件
	 * @参数pageID:文件的页号
	 * @参数buf:存储信息的缓存(4字节无符号整数数组)
	 * @参数off:偏移量
	 * 功能:将buf+off开始的2048个四字节整数(8kb信息)写入fileID和pageID指定的文件页中
	 * 返回:成功操作返回0
	 */
	int writePage(int fileID, int pageID, char* buf, int off) {
		int f = fd[fileID];
		off_t offset = pageID;
		offset = (offset << PAGE_SIZE_IDX);
		off_t error = lseek(f, offset, SEEK_SET);
		if (error != offset) {
			return -1;
		}
        char* b = buf + off;
		error = write(f , b, PAGE_SIZE);
		return 0;
	}
	/*
	 * @函数名readPage
	 * @参数fileID:文件id，用于区别已经打开的文件
	 * @参数pageID:文件页号
	 * @参数buf:存储信息的缓存(4字节无符号整数数组)
	 * @参数off:偏移量
	 * 功能:将fileID和pageID指定的文件页中2048个四字节整数(8kb)读入到buf+off开始的内存中
	 * 返回:成功操作返回0
	 */
	int readPage(int fileID, int pageID, char* buf, int off) {
		//int f = fd[fID[type]];
		int f = fd[fileID];
		off_t offset = pageID;
		offset = (offset << PAGE_SIZE_IDX);
		off_t error = lseek(f, offset, SEEK_SET);
		if (error != offset) {
			return -1;
		}
        char* b = buf + off;
		error = read(f, b, PAGE_SIZE);
		return 0;
	}
	/*
	 * @函数名closeFile
	 * @参数fileID:用于区别已经打开的文件
	 * 功能:关闭文件
	 * 返回:操作成功，返回0
	 */
	int closeFile(int fileID) {
		int f = fd[fileID];
		close(f);used[fileID]=false;
		return 0;
	}

    int closeFile(std::string name){
        for (int i=0;i<MAX_FILE_NUM;++i)
            if (used[i]&&fileName[i]==name)
            {
                used[i]=false;close(fd[i]);
                return true;
            }
        return false;
    }
	/*
	 * @函数名createFile
	 * @参数name:文件名
	 * 功能:新建name指定的文件名
	 * 返回:操作成功，返回true
	 */
	bool createFile(const char* name) {
		_createFile(name);
		return true;
	}
	/*
	 * @函数名openFile
	 * @参数name:文件名
	 * @参数fileID:函数返回时，如果成功打开文件，那么为该文件分配一个id，记录在fileID中
	 * 功能:打开文件
	 * 返回:如果成功打开，在fileID中存储为该文件分配的id，返回true，否则返回false
	 */
	bool openFile(std::string name, int& fileID) {
        for (int i=0;i<MAX_FILE_NUM;++i)
            if (used[i]&&fileName[i]==name)
            {
                fileID=i;
                return true;
            }
		for (int i=0;i<MAX_FILE_NUM;++i)
			if (!used[i])
			{
				fileID=i;used[i]=true;fileName[i]=name;
				_openFile(name.c_str(), fileID);
				return true;
			}
		return false;
	}

	void closeAll()
	{
		for (int i=0;i<MAX_FILE_NUM;++i)
			if (used[i])
            {
                used[i]=false;
                close(fd[i]);
            }
	}
};
#endif
