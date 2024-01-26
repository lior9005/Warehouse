#include "Action.h"

BaseAction::BaseAction() : errorMsg(""), status(ActionStatus::ERROR) {};

ActionStatus BaseAction::getStatus() const {
    return status;
}

void BaseAction::complete() {
    status = ActionStatus::COMPLETED;
}
void BaseAction::error(std::string errorMsg) {
    status = ActionStatus::ERROR;
    cout << "Error: " << errorMsg << endl;
}
string BaseAction::getErrorMsg() const {
    return errorMsg;
}

SimulateStep::SimulateStep(int numOfSteps) : numOfSteps(numOfSteps) {}

void SimulateStep::act(WareHouse &wareHouse) {
    int stepsToPerform = numOfSteps;
    while (stepsToPerform > 0) {
    
        //phase 1 - iterate over all pending orders and check if there is a volunteer that can take the order
        for (Order *order : wareHouse.getPendingOrdersList()){
            if (order->getStatus() == OrderStatus::PENDING){
                for (Volunteer *volunteer : wareHouse.getVolunteersList()){
                    if (typeid(*volunteer) == typeid(CollectorVolunteer) && volunteer->canTakeOrder(*order)){
                        volunteer->acceptOrder(*order);
                        order->setStatus(OrderStatus::COLLECTING);
                        order->setCollectorId(volunteer->getId());
                                 
                        break;
                    }
                }
            }
            else if (order->getStatus() == OrderStatus::COLLECTING){
                for (Volunteer *volunteer : wareHouse.getVolunteersList()){
                    if (typeid(*volunteer) == typeid(DriverVolunteer) && volunteer->canTakeOrder(*order)){
                        volunteer->acceptOrder(*order);
                        order->setStatus(OrderStatus::DELIVERING);
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
            if (!(volunteer->isBusy())){
                Order order = wareHouse.getOrder(volunteer->getCompletedOrderId());
                wareHouse.advanceOrder(&order);
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
    complete();
}

    std::string SimulateStep::toString() const {
        return "Simulate " + std::to_string(numOfSteps) + " steps";
    }

SimulateStep *SimulateStep::clone() const {
    return new SimulateStep(*this);
}

AddOrder::AddOrder(int id) : customerId(id) {}

void AddOrder::act(WareHouse &wareHouse){
    if (wareHouse.getCustomerCounter() < customerId || wareHouse.getCustomer(customerId).canMakeOrder() == false){
        error("ERROR: Cannot place this order");
    }
    else {
        Order* newOrder = new Order((wareHouse.getOrdersCounter()+1),customerId, wareHouse.getCustomer(customerId).getCustomerDistance());
        wareHouse.addOrder(newOrder);
        complete();
    }
}

AddOrder *AddOrder::clone() const {
    return new AddOrder(*this);
}

string AddOrder::toString() const {
    return "Add Order " + std::to_string(customerId);
}

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
    complete();
}

AddCustomer* AddCustomer::clone() const {
    return new AddCustomer(*this);
}

string AddCustomer::toString() const {
    return "Add Customer " + customerName;
}
