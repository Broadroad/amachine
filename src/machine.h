/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file machine.h
 * @author zk(zk@baidu.com)
 * @date 2015/04/04 11:32:24
 * @version $Revision$ 
 * @brief 
 *  
 **/
#ifndef CSPUB_MACHINE_H
#define CSPUB_MACHINE_H
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include "MPSegment.hpp"

using namespace std;
using namespace CppJieba;

class machine{
public:
    machine();
    ~machine();
public:
    void start() throw();
    std::vector<std::string> get_query_words();
    //void recommand(string input) throw();
    vector<string> split_sentence(std::string sentence);
    //parse the file like 
    bool get_key_words(std::vector<std::string> &key_words, std::vector<std::string> query_words);
    void query(std::string);
    void select_one_answer(std::vector<string>);
private:
    void set_keys_answers(std::string) noexcept; 
    std::map<std::string, std::string> cache;
    std::vector<std::string> _query_words;
    std::set<std::string> _key_words;
    std::map<vector<string>, string> _keys_answers; 
    MPSegment *_seg;
};

#endif  //CSPUB_MACHINE_H

/* vim: set ts=4 sw=4 sts=4 tw=100 */
