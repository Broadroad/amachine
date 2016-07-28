/***************************************************************************
 * 
 * Copyright (c) 2015 zkdnfcf, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file machine.cpp
 * @author zk(zk@zkdnfcf.com)
 * @date 2015/04/09 17:36:00
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include "machine.h"
#include <iostream>
#include <fstream>
#include <thread>
#include "MPSegment.hpp"
using namespace CppJieba; 
const char* const JIEBA_DICT_FILE = "~/cppjieba/dict/jieba.dict.utf8";
const char* const KEY_WORDS_DICT_FILE = "/home/zk/cspubmachine/data/cspub/diction";
const char* const KEYS_ANSWERS_FILE = "/home/zk/cspubmachine/data/cspub/cspub.csv";
const int KEY_NUMS = 3;

machine::machine() {
    //start();
    _seg = new MPSegment("/home/zk/cppjieba/dict/jieba.dict.utf8");
    start();
}

machine::~machine() {
    delete _seg;
}

void machine::query(std::string query) {
    _query_words = split_sentence(query);
}

void machine::start() throw() {
    fstream key_words_file;
    char buffer[256];
    key_words_file.open(KEY_WORDS_DICT_FILE);
    while (!key_words_file.eof()) {
        key_words_file.getline(buffer, 100);
        std::string key = buffer;
        _key_words.insert(key);
        //std::cout << key << std::endl;
    }
    
    fstream keys_answers_file;
    keys_answers_file.open(KEYS_ANSWERS_FILE);
    char tmp[4096];
    while (!keys_answers_file.eof()) {
        keys_answers_file.getline(tmp, 4096);
        std::string question_answer = tmp;
        stringstream ss(question_answer);
        std::string question,answer;
        ss >> question >> answer;
        std::vector<std::string> words = split_sentence(question);
        std::vector<std::string> keys;
        if (get_key_words(keys, words)) {
            _keys_answers[keys] = answer;
        }else {
            continue;
        }

        /*std::map<std::vector<string>, std::string>::iterator it = _keys_answers.begin();
        for(; it != _keys_answers.end(); ++it) {
            std::cout << "key:";
            for(int i = 0;i < it->first.size(); i++) {
                std::cout << it->first[i] << " ";
            }
            std::cout << "value:" << it->second << std::endl;
        }*/
       // _keys_answers[keys] = answer;
    }
}

void set_keys_answers(std::string filename) noexcept{
       
}

std::vector<std::string> machine::get_query_words() {
    return _query_words;
}

std::vector<std::string> machine::split_sentence(std::string sentence) {
   // MPSegment seg("/home/zk/cppjieba/dict/jieba.dict.utf8");
    std::string res;
    std::vector<std::string> words;
    if(!sentence.empty()) {
        words.clear();
    _seg->cut(sentence, words);
    //_query_words = words;
    return words;
    join(words.begin(), words.end(), res, "/");
    //std::cout << res << std::endl;    
    }
} 

bool machine::get_key_words(std::vector<std::string> &key_words, std::vector<std::string> query_words) {
    int num = 0;
    for (int i = 0; i < query_words.size(); ++i) {
        std::set<std::string>::iterator it = _key_words.find(query_words[i]);
        if (it != _key_words.end()) {
            key_words.push_back(query_words[i]);
            ++num;
            if (num == KEY_NUMS) {
                return true;
            }
        }
    }
    return false; 
}

void machine::select_one_answer(std::vector<string> keys) {
    // for test time
    double start = clock(); 

    int max_pi = 0;
    std::vector<std::string> max_keys;
    std::map<std::vector<std::string>, std::string>::iterator it = _keys_answers.begin();
    for(; it != _keys_answers.end(); ++it) {
        int tmp = 0;
        for (int i = 0; i < keys.size(); ++i) {
            for (int j = 0; j < it->first.size(); ++j) {
                if (keys[i] == it->first[j]) {
                    ++tmp;
                    break;
                }
            }
        }
        if (tmp > max_pi) {
            max_pi = tmp;
            max_keys = it->first;
        }        
    }
    if (_keys_answers[max_keys] == "") {
        std::cout << "请输入更为详细的问题" << std::endl;
    }
    std::cout << (clock() - start)/CLOCKS_PER_SEC << std::endl;
    std::cout << _keys_answers[max_keys] << std::endl;
}

















/* vim: set ts=4 sw=4 sts=4 tw=100 */
