#include "header/huffman.h"
#include <QFileInfo>
#include <qDebug>
HNODE* head = NULL, *current = NULL, *tail = NULL;

void deleteList(HNODE* node, int mode ){
    if (mode == 0) {
        if (node->left != NULL)
            deleteList(node->left, mode);
        if (node->right != NULL)
            deleteList(node->right, mode);
    } // if

    if ( node->next != NULL )
        deleteList(node->next, mode);
    delete node;
}

void Huffman_Tree::reverseLinkList(){
    HNODE* prev = NULL;
    HNODE* current = head;
    HNODE* next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    } // while

    head = prev;
    nodes = head;
}

bool Huffman_Tree::addToTree(HNODE* node){

    if (head == NULL) {
        head = node;
        tail = head;
        return true;
    } // if

    if (node->times <= head->times) { // smaller than head
        node->next = head;
        head = node;
        return true;
    } // if

    for (HNODE* i = head; i->next != NULL; i = i->next){
        if (node->times < i->next->times) {
            node->next = i->next;
            i->next = node;
            return true;
        }
    } // for

    tail->next = node;
    tail = node;
    return true;
}

bool Huffman_Tree::addNewNode(HNODE* left, HNODE* right){

    HNODE* parent = new HNODE;
    parent->left = left;
    parent->right = right;
    parent->times = left->times + right->times;
    addToTree(parent);
    return true;
}

bool Huffman_Tree::createTree(){

    bool findLeft = false;
    HNODE* left = NULL, *right = NULL;
    HNODE* i = head;

    while (i != NULL){
        for (i = head; i != NULL && i->times != 0; i = i->next) {

            if (!i->beenSelected) {
                if (!findLeft) {
                    left = i;
                    findLeft = true;
                    i->beenSelected = true;
                } // if
                else  {
                    right = i;
                    i->beenSelected = true;
                    addNewNode(left, right);
                    break;
                } // else
            } // if
        } // for

        findLeft = false;
    } // while


    return true;
}

bool Huffman_Tree::saveEncode(){


    nodes->encode = new char;
    nodes->encode[0] = '\0';
    for (HNODE* i = nodes; i != NULL; i = i->next) {
        if (i->left != NULL) {
            i->left->encode = new char[strlen(i->encode) + 2];
            if (i != nodes)
                for (int n = 0; n < (int)strlen(i->encode); n++) i->left->encode[n] = i->encode[n];
            i->left->encode[strlen(i->encode)] = '0';
            i->left->encode[strlen(i->encode) + 1] = '\0';
        } // if
        if (i->right != NULL) {
            i->right->encode = new char[strlen(i->encode) + 2];
            if (i != nodes)
                for (int n = 0; n < (int)strlen(i->encode); n++) i->right->encode[n] = i->encode[n];
            i->right->encode[strlen(i->encode)] = '1';
            i->right->encode[strlen(i->encode) + 1] = '\0';
        } // if

    } // for

    return true;
}

bool Huffman_Tree::headerToBits(FILE* fout, string fileType){

    int n = 0;
    char space = ' ';
    unsigned char gti = 104, ch;
    qDebug() << "1~~~~~~~~~~~" << fout;
    fwrite((char*)&gti, sizeof(unsigned char), 1, fout); // 加入判斷是否為壓縮檔
    qDebug() << "2~~~~~~~~~~~" << fileType.c_str() << fileType.length();
    fwrite((char*)fileType.c_str(), fileType.length(), 1, fout); // 副檔名
    fwrite((char*)&numOfNodes, sizeof(unsigned long), 1, fout); // num of kind
    fwrite((char*)&fileSize, sizeof(unsigned long), 1, fout); // size of file
    //qDebug() << numOfNodes << fileSize;
    unsigned long times = kindOfTimes;
    int total = 0;
    for (int j = 0; j < password.size(); j++) total += password[j].toLatin1();
    for (HNODE* i = nodes; i != NULL; i = i->next){
        ch = i->value + total;
        if (n < password.size()) ch += password[n++].toLatin1();
        fwrite((char*)&ch, sizeof(unsigned char), 1, fout);
        fwrite((char*)&i->times, sizeof(unsigned long), 1, fout);
    }

    return true;
}

bool Huffman_Tree::headerToBits(QString &content, QString fileType){

    int n = 0;
    char space = ' ';
    unsigned char gti = 104, ch;
    content += gti;// 加入判斷是否為壓縮檔
    content += fileType ; // 副檔名
    content += numOfNodes ; // num of kind
    qDebug() << numOfNodes;
    content += fileSize ; // size of file

    unsigned long times = kindOfTimes;
    int total = 0;
    for (int j = 0; j < strlen(password.toLatin1()); j++) total += password[j].toLatin1();
    for (HNODE* i = nodes; i != NULL; i = i->next){
        ch = i->value + total;
        if (n < password.size()) ch += password[n++].toLatin1();
        content += ch;
        content += i->times;
    }

    return true;
}

bool Huffman_Tree::deleteParents(){

    HNODE* newList = NULL, *newListTail = NULL, *deleteH = new HNODE, *deleteT = deleteH; // new list without parents
    for (HNODE* i = nodes; i != NULL; i = i->next) {
        if (i->left == NULL && i->right == NULL) {
            numOfNodes++;
            if (i->next != NULL && i->next->times != i->times) kindOfTimes++; // 有幾種不同的次數
            if (newList == NULL) {
                newList = i;
                newListTail = i;
            } // if
            else {
                newListTail->next = i;
                newListTail = i;
            } // else
        } // if
        else {
            deleteT->next = i;
            deleteT = deleteT->next;
        } // else
    } // for

    deleteT->next = NULL;
    deleteList(deleteH, 1);
    nodes = newList;
    return true;
}

bool Huffman_Tree::saveToFile(QString fileName, QString desFileName){

    unsigned char ch;
    char data[256] = "\0";
    FILE* file;
    FILE* fout = fopen(desFileName.toLatin1(), "wb");;
    HNODE* cur = NULL;
    int nLen = 0;
    if ( fout == NULL )
    {
        qDebug() << "fuck";
        return false;
    }

    file = fopen(fileName.toLatin1(), "rb");

    //qDebug() << desFileName << fopen_s(&fout, desFileName.toLocal8Bit().data(), "wb");
    //return false;

    headerToBits(fout, "botx ");

    fread((char *)&ch, sizeof(unsigned char), 1, file);
    while (!feof(file)){
        for (cur = nodes; cur != NULL; cur = cur->next)
            if (ch == cur->value) {
                strcat(data, cur->encode);
                break;
            } // if

        while (strlen(data) >= 8) {
            ch = 0;
            for (int i = 0; i < 8; ++i) {
                ch <<= 1;
                if (data[i] == '1')	ch |= 1;
            } // for

            fwrite(&ch, sizeof(unsigned char), 1, fout);
            nLen++;
            strcpy(data, data + 8);
        } // if

        fread((char *)&ch, sizeof(unsigned char), 1, file);
    }// while

    for (int i = strlen(data); i < 8; i++) data[i] = '0';
    ch = 0;
    for (int i = 0; i < 8; ++i){
        ch <<= 1;
        if (data[i] == '1') ch |= 1;
    }

    fwrite(&ch, sizeof(unsigned char), 1, fout);
    int pp = 97;
    fwrite(&pp, sizeof(int), 1, fout);
    fclose(file);
    fclose(fout);
    return true;
} //

bool Huffman_Tree::saveToFile(QString& content){

    unsigned char ch;
    char data[256] = "\0";
    HNODE* cur = NULL;
    int nLen = 0;
    QString output = "";
    headerToBits(output, "bot");
    for ( QChar qch : content ) {
        ch = qch.toLatin1();
        for (cur = nodes; cur != NULL; cur = cur->next)
            if (ch == cur->value) {
                strcat(data, cur->encode);
                break;
            } // if

        while (strlen(data) >= 8) {
            ch = 0;
            for (int i = 0; i < 8; ++i) {
                ch <<= 1;
                if (data[i] == '1')	ch |= 1;
            } // for

            output += ch;
            nLen++;
            strcpy(data, data + 8);
        } // if


    }// while

    for (int i = strlen(data); i < 8; i++) data[i] = '0';
    ch = 0;
    for (int i = 0; i < 8; ++i){
        ch <<= 1;
        if (data[i] == '1') ch |= 1;
    }

    output += ch;
    int pp = 97;
    output += pp;
    content = output;
    return true;
} //

Huffman_Management::Huffman_Management(QString src, QString des, QString pass, QString content)
{
    srcFileName = src;
    desFileName = des;
    password = pass;
    theContent = content;
}

Huffman_Management::~Huffman_Management()
{

}


Huffman_State Huffman_Management::compressFile()
{
    //qDebug() << srcFileName;
    if (!QFileInfo(srcFileName).exists() ) return ERROR_FILENOTEXSIT;
    //qDebug() << "~~~~~~~~~~~";
    Huffman_Tree huffmanTree;
    huffmanTree.nodes = new HNODE[256];
    huffmanTree.password = password;
    //time_t start = time(NULL);
    FILE* file;
    unsigned char ch;

    file = fopen(srcFileName.toLatin1(), "rb");
    fread((char *)&ch, sizeof(unsigned char), 1, file);
    while (!feof(file)){
        qDebug() << QString(ch);
        huffmanTree.fileSize++;
        huffmanTree.nodes[(int)ch].value = (unsigned char)ch;
        huffmanTree.nodes[(int)ch].times++;
        fread((char *)&ch, sizeof(unsigned char), 1, file);
    } // while

    fclose(file);
    for (int i = 0; i < 256; i++)
        if (huffmanTree.nodes[i].times != 0) huffmanTree.addToTree(&huffmanTree.nodes[i]);


    huffmanTree.createTree();
    huffmanTree.reverseLinkList();
    huffmanTree.saveEncode();
    huffmanTree.deleteParents();

    huffmanTree.saveToFile(srcFileName, desFileName);

    head = NULL, current = NULL, tail = NULL;
    //cout << "spend" << time(NULL) - start << endl;
    return SUCCESS;
} //

/*
Huffman_State Huffman_Management::compressFile()
{
    //if (QFileInfo(srcFileName).exists() ) return ERROR_FILENOTEXSIT;

    Huffman_Tree huffmanTree;
    huffmanTree.nodes = new HNODE[256];
    huffmanTree.password = password;
    //time_t start = time(NULL);
    unsigned char ch;
    for ( QChar qch : this->theContent )
    {
        ch = qch.toLatin1();
        huffmanTree.fileSize++;
        huffmanTree.nodes[(int)ch].value = (unsigned char)ch;
        huffmanTree.nodes[(int)ch].times++;
    } // while

    for (int i = 0; i < 256; i++)
        if (huffmanTree.nodes[i].times != 0) huffmanTree.addToTree(&huffmanTree.nodes[i]);

    huffmanTree.createTree();
    huffmanTree.reverseLinkList();
    huffmanTree.saveEncode();
    huffmanTree.deleteParents();
    huffmanTree.saveToFile(this->theContent);

    head = NULL, current = NULL, tail = NULL;
    //cout << "spend" << time(NULL) - start << endl;
    return SUCCESS;
} //
*/
 bool Huffman_Management::isCompressingFile( QString src )
{
    FILE* fin;
    char ch = '\0';
    fin = fopen(src.toLatin1(), "rb");

    fread((char*)&ch, sizeof(unsigned char), 1, fin); // 判斷是否為壓縮檔

    if (ch != 104) {
        fclose(fin);
        return false;
    } // if

    fclose(fin);
    return true;
}

Huffman_State Huffman_Management::decompressFile()
{
    if (!QFileInfo(srcFileName).exists() ) return ERROR_FILENOTEXSIT;
    Huffman_Tree huffmanTree;
    huffmanTree.password = password;
    HNODE* nodes;
    int i = 0;
    unsigned long fileSize = 0, numOfKind = 0;
    unsigned char ch = '\0';

    FILE* fin;
    fin = fopen(srcFileName.toLatin1(), "rb");

    fread((char*)&ch, sizeof(unsigned char), 1, fin); // 判斷是否為壓縮檔

    if (ch != 104) {
        fclose(fin);

        return ERROR_NOTCOMPRESSFILE;
    } // if

    char fileType[128] = { 0 };
    while (fread((char*)&fileType[i], sizeof(char), 1, fin) == 1 && fileType[i++] != ' ');
    fileType[i - 1] = '\0';

    fread((char*)&numOfKind, sizeof(unsigned long), 1, fin);
    fread((char*)&fileSize, sizeof(unsigned long), 1, fin);

    int pLen = password.size(), total = 0;
    for (int np = 0; np < password.size(); np++) total += password[np].toLatin1();
    qDebug() << "STOP1" << fileType << numOfKind;
    //return 0;
    nodes = new HNODE[(int)(numOfKind)];

    for (int k = 0; k < numOfKind; k++) {
        fread((char*)&nodes[k].value, sizeof(unsigned char), 1, fin);
        fread((char*)&nodes[k].times, sizeof(unsigned long), 1, fin);
        nodes[k].value -= (int)total;
        if (k < pLen) nodes[k].value -= (int)password[k].toLatin1();
        huffmanTree.addToTree(&nodes[k]);
    } // for

    huffmanTree.createTree();
    huffmanTree.reverseLinkList();
    huffmanTree.saveEncode();

        nodes = huffmanTree.nodes;
        int isEnd = 0;
        if (theContent.isEmpty()) theContent = "";
        char* Content = new char[fileSize];
        while (isEnd < fileSize){
            fread((char *)&ch, sizeof(unsigned char), 1, fin);
            for (i = 0; i < 8; i++) {
                if (nodes != NULL) {
                    if (ch & 128) nodes = nodes->right; // 128 -> 10000000
                    else nodes = nodes->left;
                    if (nodes != NULL && nodes->left == NULL) {
                        Content[isEnd] = nodes->value;
                        nodes = huffmanTree.nodes;
                        Content[++isEnd] = '\0';
                        //isEnd++;
                        if (isEnd >= fileSize) break; // 以免多輸出字元
                    } // if
                } // if
                else {
                    fclose(fin);
                    head = NULL, current = NULL, tail = NULL;
                    return SUCCESS;
                } // else

                ch <<= 1;
            } // for
        }// while

        fclose(fin);
        head = NULL, current = NULL, tail = NULL;
    //qDebug() << "STOP1" << Content;
     theContent = QString::fromLocal8Bit(Content);
    //cout << "spend" << time(NULL) - start << endl;
    return SUCCESS;
}
