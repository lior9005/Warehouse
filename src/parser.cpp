#include "parser.h"

// Function to parse the configuration file
void parse_config_file(const std::string& file_path, std::vector<Customer>& customers, std::vector<Volunteer>& volunteers) {

    // Open the file for reading
    std::ifstream file(file_path);
    
    // Check if the file is successfully opened
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << file_path << std::endl;
        return;
    }

    std::string line;

    // Read each line from the file
    while (std::getline(file, line)) {
        // Tokenize the line
        std::istringstream iss(line);
        std::vector<std::string> tokens{
            std::istream_iterator<std::string>{iss},
            std::istream_iterator<std::string>{}
        };

        // Check the type of entry (customer or volunteer)
        if (tokens[0] == "customer") {
            // Parse customer information
            Customer customer_info {
                tokens[1],                    // name
                tokens[2],                    // type
                std::stoi(tokens[3]),         // distance
                std::stoi(tokens[4])          // max_orders
            };
            
            // Add customer to the vector
            customers.push_back(customer_info);
        } else if (tokens[0] == "volunteer") {
            // Parse volunteer information
            Volunteer volunteer_info {
                tokens[1],                    // name
                tokens[2],                    // role
                std::stoi(tokens[3])          // cooldown_or_max_distance
            };

            // Check if the volunteer is a driver
            if (tokens[2] == "driver") {
                volunteer_info.max_distance = std::stoi(tokens[4]);
                volunteer_info.distance_per_step = std::stoi(tokens[5]);

                // Check if max_orders is provided
                if (tokens.size() > 6) {
                    volunteer_info.max_orders = std::stoi(tokens[6]);
                }
            } else {
                // Check if max_orders is provided
                if (tokens.size() > 4) {
                    volunteer_info.max_orders = std::stoi(tokens[4]);
                }
            }

            // Add volunteer to the vector
            volunteers.push_back(volunteer_info);
        }
    }
    
    // Close the file
    file.close();
}