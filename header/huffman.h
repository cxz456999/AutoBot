#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <stdio.h>
#include <windows.h>
#include <QString>
#include <iostream>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <fstream>
#include <time.h>
#include <ShellAPI.h>
#include <string>

enum Huffman_State{
    SUCCESS = 0, COMPRESSFILE = 1, ERROR_NOTCOMPRESSFILE = 1111111, ERROR_FILENOTEXSIT = 222222
};

using namespace  std;


class HNODE{
public:
    unsigned char value;
    unsigned long times;
    char* encode;
    HNODE* left;
    HNODE* right;
    HNODE* next;
    bool beenSelected;
    //void clone(HNODE*);
    HNODE(){ value = '\0'; times = 0; encode = ""; beenSelected = false;  left = NULL; right = NULL; next = NULL; }
};

class Huffman_Tree{
public:
    HNODE* nodes;
    unsigned long numOfNodes;
    unsigned long fileSize;
    unsigned long kindOfTimes;
    QString password;
    //bool addToTree(char);
    bool addToTree(HNODE*);
    bool addNewNode(HNODE*, HNODE*);
    bool createTree();
    bool saveEncode();
    void reverseLinkList();
    bool saveToFile(QString, QString);
    bool saveToFile(QString &content);
    bool headerToBits(FILE*, string);
    bool headerToBits(QString &content, QString fileType);
    bool deleteParents();
    Huffman_Tree(){ nodes = NULL; numOfNodes = 0, fileSize = 0, kindOfTimes = 1; }
};

class Huffman_Management{
public:
    //int Huffman();
    //Huffman_Order();//{ memset(srcFileName, '\0', sizeof(srcFileName)); memset(desFileName, '\0', sizeof(desFileName)); memset(password, '\0', sizeof(password)); theContent = NULL; }
    Huffman_Management(QString src, QString des, QString pass, QString content );
    ~Huffman_Management();
    static bool isCompressingFile(QString src);
    Huffman_State compressFile();
    Huffman_State decompressFile();
    QString getResult(){ return theContent; }
private:
    int order;
    QString srcFileName = "tmp.lock";
    QString desFileName = "tmp.lock";
    QString password;
    QString theContent;
};
#endif // HUFFMAN_H
