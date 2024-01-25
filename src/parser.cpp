#include "parser.h"
#include "iterator"

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
    int numOfCustomers = 0;
    int numOfVolunteers = 0;
    // Read each line from the file
    while (std::getline(file, line)) {
        // Tokenize the line
        std::istringstream iss(line);
        #include <iterator>

        std::vector<std::string> tokens{
            std::istream_iterator<std::string>{iss},
            std::istream_iterator<std::string>{}
        };

        // Check the type of entry (customer or volunteer)
        if (tokens[0] == "customer") {
            numOfCustomers++;

            // Check if the customer is a soldier
            if (tokens[2] == "soldier") {
                SoldierCustomer newCustomer {
                    numOfCustomers,                // id
                    tokens[1],                     // name
                    std::stoi(tokens[3]),          // distance
                    std::stoi(tokens[4])           // max_orders
                };
                customers.push_back(newCustomer);
            }
            else {
                CivilianCustomer newCustomer {
                    numOfCustomers,                // id
                    tokens[1],                     // name
                    std::stoi(tokens[3]),          // distance
                    std::stoi(tokens[4])           // max_orders
                };
                customers.push_back(newCustomer);
            }

        }

        else {
            numOfVolunteers++;
            // Parse volunteer information

            if (tokens[2] == "collector") {
                CollectorVolunteer newVolunteer {
                    numOfVolunteers,               // id
                    tokens[1],                     // name
                    std::stoi(tokens[3])           // cool_down
                };
                volunteers.push_back(newVolunteer);
            }
            else if (tokens[2] == "limited_collector") {
                LimitedCollectorVolunteer newVolunteer {
                    numOfVolunteers,               // id
                    tokens[1],                     // name
                    std::stoi(tokens[3]),          // cool_down
                    std::stoi(tokens[4])           // max_orders
                };
                volunteers.push_back(newVolunteer);
            }
            else if (tokens[2] == "driver") {
                DriverVolunteer newVolunteer {
                    numOfVolunteers,               // id
                    tokens[1],                     // name
                    std::stoi(tokens[3]),          // max_distance                   
                    std::stoi(tokens[4])           // distance per step
                };
                volunteers.push_back(newVolunteer);
            }
            else{
                LimitedDriverVolunteer newVolunteer {
                    numOfVolunteers,               // id
                    tokens[1],                     // name
                    std::stoi(tokens[3]),          // max_distance
                    std::stoi(tokens[4]),          // distance per step
                    std::stoi(tokens[5])           // max_orders
                };
                volunteers.push_back(newVolunteer);
            }
        }
    
    // Close the file
    file.close();
}