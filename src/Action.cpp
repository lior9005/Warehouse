#include "Action.h"
#include "WareHouse.h"

BaseAction::BaseAction() : errorMsg(""), status(ActionStatus::COMPLETED) {};

ActionStatus BaseAction::getStatus() const {
    return status;
}

string BaseAction::statusToString() const{
    if (status == ActionStatus::COMPLETED){
        return "COMPLETED";
    }
    else {
        return "ERROR";
    }
}

void BaseAction::error(std::string errorMsg) {
    status = ActionStatus::ERROR;
    cout << "Error: " << errorMsg << endl;
}
string BaseAction::getErrorMsg() const {
    return errorMsg;
}

//SIMULATE STEP
SimulateStep::SimulateStep(int numOfSteps) : numOfSteps(numOfSteps) {}

void SimulateStep::act(WareHouse &wareHouse) {
    int stepsToPerform = numOfSteps;
    while (stepsToPerform > 0) {
    
        //phase 1 - iterate over all pending orders and check if there is a volunteer that can take the order
        vector<Order*> &pendingOrders = wareHouse.getPendingOrdersList();
        for (Order *order :pendingOrders){

            //who needs to take the order
            if (order->getStatus() == OrderStatus::PENDING){
                for (Volunteer *volunteer : wareHouse.getVolunteersList()){
                    if (((typeid(*volunteer) == typeid(CollectorVolunteer)) || (typeid(*volunteer) == typeid(LimitedCollectorVolunteer)))  && (volunteer->canTakeOrder(*order))){
                        volunteer->acceptOrder(*order);
                        order->setCollectorId(volunteer->getId());
                        wareHouse.advanceOrder(order);
                        break;
                    }
                }
            }
            else if (order->getStatus() == OrderStatus::COLLECTING){
                for (Volunteer *volunteer : wareHouse.getVolunteersList()){
                    if (((typeid(*volunteer) == typeid(DriverVolunteer)) || (typeid(*volunteer) == typeid(LimitedDriverVolunteer)))  && (volunteer->canTakeOrder(*order))){
                        volunteer->acceptOrder(*order);
                        order->setDriverId(volunteer->getId());
                        wareHouse.advanceOrder(order);          
                        break;
                    }
                }
            }
        }

        //phase 2 - perform a step
        for (Volunteer *volunteer : wareHouse.getVolunteersList()){
            volunteer->step();
        }

        //phase 3 - check if there are orders that are completed
        for (Volunteer *volunteer : wareHouse.getVolunteersList()){
            if (!(volunteer->isBusy()) && (volunteer->getCompletedOrderId() != NO_ORDER)){
                int orderId = volunteer->getCompletedOrderId();
                for (Order *order : wareHouse.getInProcessOrdersList()){
                    if (order->getId() == orderId){
                        wareHouse.advanceOrder(order);
                        volunteer->restartCompletedOrderId();
                        break;
                    }
                }
            }
        }

        //phase 4 - delete unnecessary volunteers
        for (Volunteer *volunteer : wareHouse.getVolunteersList()){
            if ((!(volunteer->hasOrdersLeft())) && (!(volunteer->isBusy()))){
                wareHouse.deleteVolunteer(volunteer);
                delete volunteer;
            }
        }    
        stepsToPerform--;
    }
}

string SimulateStep::toString() const {
    return "SimulateStep " + std::to_string(numOfSteps) +" "+ statusToString();
}

SimulateStep *SimulateStep::clone() const {
    return new SimulateStep(*this);
}

//ADD ORDER
AddOrder::AddOrder(int id) : customerId(id) {}

void AddOrder::act(WareHouse &wareHouse){
    if (wareHouse.getCustomerCounter()-1 < customerId || wareHouse.getCustomer(customerId).canMakeOrder() == false){
        error("Cannot place this order");
    }
    else {
        Order* newOrder = new Order((wareHouse.getOrdersCounter()),customerId, wareHouse.getCustomer(customerId).getCustomerDistance());
        wareHouse.addOrder(newOrder);
    }
}

AddOrder *AddOrder::clone() const {
    return new AddOrder(*this);
}

string AddOrder::toString() const {
    return "Order " + std::to_string(customerId) +" "+ statusToString();
}

//ADD CUSTOMER
AddCustomer::AddCustomer(const string &customerName, const string &customerType, int distance, int maxOrders) 
: customerName(customerName), distance(distance), maxOrders(maxOrders), customerType(customerType == "soldier" ? CustomerType::Soldier : CustomerType::Civilian) {}

void AddCustomer::act(WareHouse &wareHouse){
    if (CustomerType::Soldier == customerType){
        Customer* newCustomer = new SoldierCustomer(wareHouse.getCustomerCounter()+1, customerName, distance, maxOrders);
        wareHouse.addCustomer(newCustomer);
    }
    else {
        Customer* newCustomer = new CivilianCustomer(wareHouse.getCustomerCounter()+1, customerName, distance, maxOrders);
        wareHouse.addCustomer(newCustomer);
    }
}

AddCustomer* AddCustomer::clone() const {
    return new AddCustomer(*this);
}

string AddCustomer::toString() const {
    return "Customer " + customerName +" "+ typeToString() +" "+ std::to_string(distance) +" "+ std::to_string(maxOrders) +" "+ statusToString();
}

string AddCustomer::typeToString() const {
    if (customerType == CustomerType::Soldier){
        return "Soldier";
    }
    else {
        return "Civilian";
    }
}

//PrintOrdersStatus
PrintOrderStatus::PrintOrderStatus(int id) : orderId(id) {}

void PrintOrderStatus::act(WareHouse &wareHouse){
    if (wareHouse.getOrdersCounter() < orderId){
        error("Order does not exist");
    }
    else {
        const Order &order = wareHouse.getOrder(orderId);
        cout << order.toString() << endl;
    }
}

PrintOrderStatus* PrintOrderStatus ::clone() const {
    return new PrintOrderStatus(*this);
}

string PrintOrderStatus::toString() const {
    return "OrderStatus " + std::to_string(orderId) +" "+ statusToString();
}

//PrintCustomerStatus
PrintCustomerStatus::PrintCustomerStatus(int customerId) : customerId(customerId) {}

void PrintCustomerStatus::act(WareHouse &wareHouse){
    if (wareHouse.getCustomerCounter() < customerId){
        error("Customer doesn't exist");
    }
    else {
        const Customer &customer = wareHouse.getCustomer(customerId);
        string customerStatus = "CustomerID: " + std::to_string(customerId) + "\n";
        for (int orderId : customer.getOrdersIds()) {
          customerStatus += "OrderID: " + std::to_string(orderId) + "\n";
          const Order &order = wareHouse.getOrder(orderId);
          customerStatus += "OrderStatus: " + order.getStatusString() + "\n";
        }
        customerStatus += "numOrdersLeft: " + std::to_string(customer.getMaxOrders()-customer.getOrdersIds().size());
        cout << customerStatus << endl; 
    }
}

PrintCustomerStatus *PrintCustomerStatus::clone() const {
    return new PrintCustomerStatus(*this);
}

string PrintCustomerStatus::toString() const{
    return "customerStatus " + std::to_string(customerId) +" "+ statusToString();
}

//PrintVolunteerStatus
PrintVolunteerStatus::PrintVolunteerStatus(int id) :volunteerId(id){}

void PrintVolunteerStatus::act(WareHouse &wareHouse){
    for (Volunteer *volunteer : wareHouse.getVolunteersList()){
        if (volunteer->getId() == volunteerId){
            cout << volunteer->toString() << endl;
            return;
        }
    }
     error("Volunteer doesn't exist");
}

PrintVolunteerStatus *PrintVolunteerStatus::clone() const {
    return new PrintVolunteerStatus(*this);
}

string PrintVolunteerStatus::toString() const {
    return "VolunteerStatus " + std::to_string(volunteerId) +" "+ statusToString();
}

PrintActionsLog::PrintActionsLog() {}

void PrintActionsLog::act(WareHouse &wareHouse) {
    vector<BaseAction*> actions = wareHouse.getActions();
    for(BaseAction* action : actions){
        cout << action->toString() << endl;
    }
}

PrintActionsLog* PrintActionsLog::clone() const{
    return new PrintActionsLog(*this);
}

string PrintActionsLog::toString() const{
    return "log " + statusToString();
}

Close::Close() {}

void Close::act(WareHouse &wareHouse) {
    wareHouse.printAllOrders();
    wareHouse.close();
}

Close* Close::clone() const {
    return new Close(*this);
}

string Close::toString() const {
    return "Close " + statusToString();
}

BackupWareHouse::BackupWareHouse() {}

void BackupWareHouse::act(WareHouse &wareHouse) {
    if(backup == nullptr)
        backup =  new WareHouse(wareHouse);
    else
        *backup = wareHouse;
}

BackupWareHouse* BackupWareHouse::clone() const {
    return new BackupWareHouse(*this);
}

string BackupWareHouse::toString() const {
    return "BackupWareHouse " + statusToString();
}

//RestoreWareHouse
RestoreWareHouse::RestoreWareHouse() {}

void RestoreWareHouse::act(WareHouse &wareHouse){
    if (backup == nullptr){
        error("No backup available");
    }
    else {
        wareHouse = *backup;
    }
}

string RestoreWareHouse::toString() const {
    return "RestoreWareHouse " + statusToString();
}

RestoreWareHouse* RestoreWareHouse::clone() const {
    return new RestoreWareHouse(*this);
}
