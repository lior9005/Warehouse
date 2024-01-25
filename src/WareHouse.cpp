#include "WareHouse.h"

WareHouse::WareHouse(const string &configFilePath) 
    : isOpen(false), customerCounter(0), volunteerCounter(0), orderCounter(0){
    
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

WareHouse::WareHouse(const WareHouse &other) 
    : isOpen(other.isOpen), customerCounter(other.customerCounter), volunteerCounter(other.volunteerCounter), orderCounter(orderCounter){
    for (Order* order : other.pendingOrders) {
        pendingOrders.push_back(order->clone());
    }
    for (Order* order : inProcessOrders) {
        if (order->getId() == orderId) {
            return *order;
        }
    }
    for (Order* order : completedOrders) {
        if (order->getId() == orderId) {
            return *order;
        }
    }
}

void WareHouse::start() {
    open();
}

const vector<BaseAction*> &WareHouse::getActions() const {
    return actionsLog;
}

void WareHouse::addOrder(Order* order) {
    pendingOrders.push_back(order);
    orderCounter++;
}

void WareHouse::addCustomer(Customer* customer) {
    customers.push_back(customer);
    customerCounter++;
}

void WareHouse::addVolunteer(Volunteer* volunteer) {
    volunteers.push_back(volunteer);
    volunteerCounter++;
}

void WareHouse::addAction(BaseAction* action) {
    actionsLog.push_back(action);
}

Customer &WareHouse::getCustomer(int customerId) const {
    for (Customer* customer : customers) {
        if (customer->getId() == customerId) {
            return *customer;
        }
    }
}

Volunteer &WareHouse::getVolunteer(int volunteerId) const {
    for (Volunteer* volunteer : volunteers) {
        if (volunteer->getId() == volunteerId) {
            return *volunteer;
        }
    }
}

Order &WareHouse::getOrder(int orderId) const {
    for (Order* order : pendingOrders) {
        if (order->getId() == orderId) {
            return *order;
        }
    }
    for (Order* order : inProcessOrders) {
        if (order->getId() == orderId) {
            return *order;
        }
    }
    for (Order* order : completedOrders) {
        if (order->getId() == orderId) {
            return *order;
        }
    }
}

void WareHouse::close() {
    isOpen = false;
    delete this;
}

void WareHouse::open() {
    isOpen = true;
    std::cout << "Warehouse is open!" << std::endl;
    while (isOpen) {
        std::string input;
        std::getline(std::cin, input);  // save the string entered in input
        std::istringstream iss(input);  // Split the input string into words
        std::vector<std::string> words;
        std::string word;
        while (iss >> word) {
            words.push_back(word);
        }

        if (words[0] == "step") {
            BaseAction* step = new SimulateStep(std::stoi(words[1]));
            step->act(*this);
        }
        else if (words[0] == "order") {
            BaseAction* addOrder = new AddOrder(std::stoi(words[1]));
            addOrder->act(*this);
        }
        else if (words[0] == "customer") {
            BaseAction* addCustomer = new AddCustomer(words[1], words[2], std::stoi(words[3]), std::stoi(words[4]));
            addCustomer->act(*this);
        }
        else if (words[0] == "orderStatus") {
            BaseAction* orderStatus = new PrintOrderStatus(std::stoi(words[1]));
            orderStatus->act(*this);            
        }
        else if (words[0] == "customerStatus") {
            BaseAction* customerStatus = new PrintCustomerStatus(std::stoi(words[1]));
            customerStatus->act(*this);            
        }
        else if (words[0] == "volunteerStatus") {
            BaseAction* volunteerStatus = new PrintVolunteerStatus(std::stoi(words[1]));
            volunteerStatus->act(*this);            
        }
        else if (words[0] == "log") {
            BaseAction* log = new PrintActionsLog();
            log->act(*this);            
        }
        else if (words[0] == "close") {
            BaseAction* close = new Close();
            close->act(*this);            
        }
        else if (words[0] == "backup") {
            BaseAction* backup = new BackupWareHouse();
            backup->act(*this);            
        }
        else if (words[0] == "restore") {
            BaseAction* restore = new RestoreWareHouse();
            restore->act(*this);            
        }
        else {
            std::cout << "Incorrect Input" << std::endl;
        }
    }
}

WareHouse::~WareHouse() {
    for (BaseAction* action : actionsLog) {
        delete(action);
    }
    for (Volunteer* volunteer : volunteers) {
        delete(volunteer);
    }    
    for (Order* order : pendingOrders) {
        delete(order);
    }
    for (Order* order : inProcessOrders) {
        delete(order);
    }
    for (Order* order : completedOrders) {
        delete(order);
    }
    for (Customer* customer : customers) {
        delete(customer);
    }
}

void WareHouse:: printAllCustomers(){
    for (Customer* customer : customers) {
        cout << customer->toString() << endl;
    }
}
void WareHouse:: printAllVolunteers(){
    for (Volunteer* volunteer : volunteers) {
        cout << volunteer->toString() << endl;
    }
}
