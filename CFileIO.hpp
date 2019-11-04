#ifndef CFILEIO_HPP
#define CFILEIO_HPP

#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xmlreader.h>
#include <string>
#include <map>

std::string xmlchar_to_string(const xmlChar* str);

double xml_read_num(const xmlNodePtr& node);    // 读取数值节点
void xml_judge_read_num(const char* name, const xmlNodePtr& node, double& num);    // 判断节点名称读取数值节点
void xml_judge_read_num(const char* name, const xmlNodePtr& node, int& num);   // 判断节点名称读取数值节点
xmlNodePtr xml_write_num(const char* name, double num); // 写入数值节点
void xml_addchild_num(const char* name, double num, const xmlNodePtr& node);    // 添加数值类型的子节点

std::string xml_read_string(const xmlNodePtr& node);    // 读取字符串节点
void xml_judge_read_string(const char* name, const xmlNodePtr& node, std::string& str);    // 判断节点名称读取字符串节点
xmlNodePtr xml_write_string(const char* name, std::string str); // 写入字符串节点
void xml_addchild_string(const char* name, std::string str, const xmlNodePtr& node);    // 添加字符串类型的子节点

bool xml_judge_name(const char* name, const xmlNodePtr& node);  // 判断节点名称
int xml_get_child_num(const xmlNodePtr& node);  // 获取子节点数量

xmlNodePtr xml_find_child_node_content(const char* content, const xmlNodePtr& node);   // 寻找特定content的子节点

#endif
