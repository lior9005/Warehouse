#pragma once
#include <string>
#include <vector>
using namespace std;
#include "Order.h"
#include "Customer.h"
#include "Volunteer.h"
#include "Action.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <cstring>
#include <algorithm>
class BaseAction;
class Volunteer;

// Warehouse responsible for Volunteers, Customers and Actions.


class WareHouse {

    public:
        WareHouse(const string &configFilePath);
        WareHouse(const WareHouse &other);
        WareHouse(WareHouse&& other);
        void start();
        const vector<BaseAction*> &getActions() const;
        void addOrder(Order* order);
        void addCustomer(Customer* customer);
        void addVolunteer(Volunteer* volunteer);
        void addAction(BaseAction* action);
        const Customer& getCustomer(int customerId) const;
        const Volunteer& getVolunteer(int volunteerId) const;
        const Order &getOrder(int orderId) const;
        void close();
        void open();
        ~WareHouse();
        void advanceOrder(Order* order);
        void deleteVolunteer(Volunteer* volunteer);
        WareHouse& operator=(const WareHouse& other);
        WareHouse& operator=(WareHouse&& other);
        vector<Volunteer*> &getVolunteersList();
        vector<Order*> &getPendingOrdersList();
        int getCustomerCounter() const;
        int getOrdersCounter() const;
        //My functions
        void printAllCustomers();
        void printAllVolunteers();

    private:
        bool isOpen;
        vector<BaseAction*> actionsLog;
        vector<Volunteer*> volunteers;
        vector<Order*> pendingOrders;
        vector<Order*> inProcessOrders ;
        vector<Order*> completedOrders;
        vector<Customer*> customers;
        int customerCounter; //For assigning unique customer IDs
        int volunteerCounter; //For assigning unique volunteer IDs
        int orderCounter; //For assigning unique order IDs
};