#ifndef CFILEIO_CPP
#define CFILEIO_CPP

#include <iostream>
#include <sstream>
#include <string>

#include "CFileIO.hpp"

using namespace std;

static string num_to_string(int num){
    stringstream ss;
    ss << num;
    return ss.str();
}

static string num_to_string(double num){
    stringstream ss;
    ss.precision(15);
    ss << num;
    return ss.str();
}

static double string_to_num(const string& str){
    stringstream ss;
    ss << str;
    double num;
    ss >> num;
    return num;
}

string xmlchar_to_string(const xmlChar* str){
    return string((char*)str);
}

double xml_read_num(const xmlNodePtr& node){
    xmlChar *content = xmlNodeGetContent(node);
    return string_to_num(xmlchar_to_string(content));
}

void xml_judge_read_num(const char *name, const xmlNodePtr &node, double &num){
    if(xml_judge_name(name, node)){
        num = xml_read_num(node);
    }
}

void xml_judge_read_num(const char* name, const xmlNodePtr& node, int& num){
    if(xml_judge_name(name, node)){
        num = xml_read_num(node);
    }
}

xmlNodePtr xml_write_num(const char* name, double num){
    xmlNodePtr node = xmlNewNode(NULL, BAD_CAST name);
    xmlNodePtr content = xmlNewText(BAD_CAST (xmlChar *)num_to_string(num).c_str());
    xmlAddChild(node, content);
    return node;
}

void xml_addchild_num(const char* name, double num, const xmlNodePtr& node){
    xmlNodePtr elementNode = xml_write_num(name, num);
    xmlAddChild(node, elementNode);
}

string xml_read_string(const xmlNodePtr& node){
    xmlChar *content = xmlNodeGetContent(node);
    return xmlchar_to_string(content);
}

void xml_judge_read_string(const char* name, const xmlNodePtr& node, string& str){
    if(xml_judge_name(name, node)){
        str = xml_read_string(node);
    }
}

xmlNodePtr xml_write_string(const char* name, string str){
    xmlNodePtr node = xmlNewNode(NULL, BAD_CAST name);
    xmlNodePtr content = xmlNewText(BAD_CAST (xmlChar *)str.c_str());
    xmlAddChild(node, content);
    return node;
}

void xml_addchild_string(const char* name, string str, const xmlNodePtr& node){
    xmlNodePtr elementNode = xml_write_string(name, str);
    xmlAddChild(node, elementNode);
}

bool xml_judge_name(const char* name, const xmlNodePtr& node){
    return !((bool)xmlStrcmp(node->name, (const xmlChar *)name));
}

int xml_get_child_num(const xmlNodePtr& node){
    int num = 0;
    xmlNodePtr ptrNode = node->children;
    while(ptrNode != NULL){
        num++;
        ptrNode = ptrNode->next;
    }
    return num;
}

xmlNodePtr xml_find_child_node_content(const char* content, const xmlNodePtr& node){
    xmlNodePtr ptrNode = node->children;
    while(ptrNode != NULL){
        if(!xmlStrcmp(xmlNodeGetContent(node), (const xmlChar *)content)){
            return ptrNode;
        }
    }
    return NULL;
}

#endif
