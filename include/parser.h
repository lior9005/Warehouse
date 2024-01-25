#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H
#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Volunteer.h" 
#include <Customer.h> 
#include <string>

// Function to parse the configuration file
void parse_config_file(const std::string& file_path, std::vector<Customer>& customers, std::vector<Volunteer>& volunteers);

#endif // CONFIG_PARSER_H