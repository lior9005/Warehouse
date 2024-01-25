#include "WareHouse.h"

WareHouse::WareHouse(const string &configFilePath) 
    : isOpen(false), customerCounter(0), volunteerCounter(0), orderCount(0){
    
    // Open the file for reading
        std::ifstream file(configFilePath);

    // Check if the file is successfully opened
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << configFilePath << ". " << std::strerror(errno) << std::endl;
        return;
    }

    std::string line;
    // Read each line from the file
    while (std::getline(file, line)) {
    // If the line starts with '#' or empty, ignore it
        if (line.empty()) {
        continue;
        }
        if (line[0] == '#') {
        continue;
        }
        // Tokenize the line
        std::istringstream iss(line);
        std::vector<std::string> tokens{
            std::istream_iterator<std::string>{iss},
            std::istream_iterator<std::string>{}
        };

        // Check the type of entry (customer or volunteer)
        if (tokens[0] == "customer") {
            customerCounter++;

            // Check if the customer is a soldier
            if (tokens[2] == "soldier") {
                SoldierCustomer *newCustomer = new SoldierCustomer{
                    customerCounter,                // id
                    tokens[1],                     // name
                    std::stoi(tokens[3]),          // distance
                    std::stoi(tokens[4])           // max_orders
                };
                customers.push_back(newCustomer);
            }
            else {
                CivilianCustomer *newCustomer = new CivilianCustomer{
                    customerCounter,                // id
                    tokens[1],                     // name
                    std::stoi(tokens[3]),          // distance
                    std::stoi(tokens[4])           // max_orders
                };
                customers.push_back(newCustomer);
            }

        }

        else {
            volunteerCounter++;
            // Parse volunteer information

            if (tokens[2] == "collector") {
                CollectorVolunteer *newVolunteer = new CollectorVolunteer {
                    volunteerCounter,               // id
                    tokens[1],                     // name
                    std::stoi(tokens[3])           // cool_down
                };
                volunteers.push_back(newVolunteer);
            }
            else if (tokens[2] == "limited_collector") {
                LimitedCollectorVolunteer *newVolunteer = new LimitedCollectorVolunteer{
                    volunteerCounter,               // id
                    tokens[1],                     // name
                    std::stoi(tokens[3]),          // cool_down
                    std::stoi(tokens[4])           // max_orders
                };
                volunteers.push_back(newVolunteer);
            }
            else if (tokens[2] == "driver") {
                DriverVolunteer *newVolunteer = new DriverVolunteer{
                    volunteerCounter,               // id
                    tokens[1],                     // name
                    std::stoi(tokens[3]),          // max_distance                   
                    std::stoi(tokens[4])           // distance per step
                };
                volunteers.push_back(newVolunteer);
            }
            else{
                LimitedDriverVolunteer *newVolunteer = new LimitedDriverVolunteer{
                    volunteerCounter,               // id
                    tokens[1],                     // name
                    std::stoi(tokens[3]),          // max_distance
                    std::stoi(tokens[4]),          // distance per step
                    std::stoi(tokens[5])           // max_orders
                };
                volunteers.push_back(newVolunteer);
            }
        }
    }
    // Close the file
    file.close();

}

void WareHouse::start() {
    // TODO: Start the warehouse operations
}

const vector<BaseAction*> &WareHouse::getActionsLog() const {
    return actionsLog;
}

void WareHouse::addOrder(Order* order) {
    // TODO: Add an order to the warehouse
}

void WareHouse::addAction(BaseAction* action) {
    // TODO: Add an action to the warehouse
}

void WareHouse::printActionsLogs() {
    // TODO: Print the action logs
}

Customer &WareHouse::getCustomer(int customerId) const {
    // TODO: Return the customer with the given ID
}

Volunteer &WareHouse::getVolunteer(int volunteerId) const {
    // TODO: Return the volunteer with the given ID
}

Order &WareHouse::getOrder(int orderId) const {
    // TODO: Return the order with the given ID
}

void WareHouse::close() {
    // TODO: Close the warehouse
}

void WareHouse::open() {
    // TODO: Open the warehouse
}
void WareHouse:: printAllCustomers(){
    for (int i = 0; i < customers.size(); ++i) {
        cout << customers[i]->toString() << endl;
    }
}
void WareHouse:: printAllVolunteers(){
    for (int i = 0; i < volunteers.size(); ++i) {
        cout << volunteers[i]->toString() << endl;
    }
}
