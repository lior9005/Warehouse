#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H
#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

// Structure to store customer information
struct Customer {
    std::string name;
    std::string type;
    int distance;
    int max_orders;
};

// Structure to store volunteer information
struct Volunteer {
    std::string name;
    std::string role;
    int cooldown_or_max_distance;
    int max_distance;
    int distance_per_step;
    int max_orders;
};

// Function to parse the configuration file
void parse_config_file(const std::string& file_path, std::vector<Customer>& customers, std::vector<Volunteer>& volunteers);

#endif // CONFIG_PARSER_H