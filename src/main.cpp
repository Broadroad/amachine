/***************************************************************************
 * 
 * Copyright (c) 2015 Baidu.com, Inc. All Rights Reserved
 * $Id$ 
 * 
 **************************************************************************/
 
 /**
 * @file main.cc
 * @author zk(zkdnfcf@163.com)
 * @date 2015/04/04 11:20:43
 * @version $Revision$ 
 * @brief 
 *  
 **/

#include <iostream>
#include <vector>
#include <boost/program_options.hpp>
#include "machine.h"
#include "Epoll.h"

namespace po = boost::program_options;
using namespace std;

/*j
int main(int args, char* argv[]) {
    std::string config_file;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "produce help message")
        ("config,c",po::value<string>(&config_file) ,"input which conf file will be loaded");
    po::variables_map vm;
    po::store(po::parse_command_line(args, argv, desc), vm);
    po::notify(vm);
    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 1;
    }
    if (vm.count("config")) {
        config_file = vm["config"].as<string>();
        std::cout << "config file" << config_file << std::endl;
    }
    machine machine;
    bool machine_flag = true;
    while(true) {
        if (machine_flag == true) {
            std::cout << "请输入你要查询的问题或者输入人工服务" << std::endl;
            string query;
            cin >> query;
            if (query == "人工服务") {
                machine_flag = false;
                continue;
            }
            machine.query(query);
            std::vector<std::string> query_words = machine.get_query_words();
            machine.split_sentence(query);
            std::vector<std::string> res;
            machine.get_key_words(res, query_words);
            machine.select_one_answer(res);
        }else {
            cout << "人工" << endl;
        }
    }
}
*/

int main(int args, char* argv[]) {
    
}

/* vim: set ts=4 sw=4 sts=4 tw=100 */
