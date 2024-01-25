#include "Action.h"

BaseAction::BaseAction() : errorMsg(""), status(ERROR) {};

ActionStatus BaseAction::getStatus() const {
    return status;
}

void BaseAction::complete() {
    status = COMPLETED;
}
void BaseAction::error(std::string errorMsg) {
    status = ERROR;
    cout << "Error: " << errorMsg << endl;
}
string BaseAction::getErrorMsg() const {
    return errorMsg;
}

SimulateStep::SimulateStep(int numOfSteps) : numOfSteps(numOfSteps) {}

void SimulateStep::act(WareHouse &wareHouse) {
    while (numOfSteps > 0) {
    
        //phase 1 - iterate over all pending orders and check if there is a volunteer that can take the order
        for (order *order : wareHouse.pendingOrders){
            if (order->getStatus() == OrderStatus::PENDING){
                for (Volunteer *volunteer : wareHouse.volunteers){
                    if (typeid(*volunteer) == typeid(CollectorVolunteer) && volunteer->canTakeOrder(*order)){
                        volunteer->acceptOrder(*order);
                        order->setStatus(OrderStatus::COLLECTING);
                        order->setCollectorId(volunteer->getId());
                        pendingOrders.erase(order);
                        inProcessOrders.push_back(order);           
                        break;
                    }
                }
            }
            else if (order->getStatus() == OrderStatus::COLLECTING){
                for (Volunteer *volunteer : wareHouse.volunteers){
                    if (typeid(*volunteer) == typeid(DriverVolunteer) && volunteer->canTakeOrder(*order)){
                        volunteer->acceptOrder(*order);
                        order->setStatus(OrderStatus::DELIVERING);
                        order->setDriverId(volunteer->getId());
                        pendingOrders.erase(order);
                        inProcessOrders.push_back(order);           
                        break;
                    }
                }
            }
        }

        //phase 2 - perform a step
        for (Volunteer *volunteer : wareHouse.volunteers){
            volunteer->step();
        }

        //phase 3 - check if there are orders that are completed
        for (Volunteer *volunteer : wareHouse.volunteers){
            if (!(volunteer->isBusy())){
                Order order = volunteer->getCompletedOrder();
                if (order.getStatus == OrderStatus::COLLECTING){
                    inProcessOrders.erase(order);
                    pendingOrders.push_back(order);
                }
                else {
                    inProcessOrders.erase(order);
                    completeOrders.push_back(order);
                    order.setStatus(OrderStatus::COMPLETED);
                }
            }
        }

        //phase 4 - delete unnecessary volunteers
        for (Volunteer *volunteer : wareHouse.volunteers){
            if ((!(volunteer->hasOrdersLeft())) && (!(volunteer.isBusy()))){
                wareHouse.volunteers.erase(volunteer);
                delete volunteer;
            }
        }    
        numOfSteps--;
    }
    complete();
}

std::string SimulateStep::toString() const {
    return "Simulate " + std::to_string(numOfSteps) + " steps";
}

SimulateStep *SimulateStep::clone() const {
    return new SimulateStep(*this);
}

AddOrder::AddOrder(int id) : cutomerId(id) {
    errorMsg = "ERROR: Cannot place this order";
}

void AddOrder::act(WareHouse &wareHouse){
    if (getCustomerCounter < customerId || getCustomer(customerId).canMakeOrder() == false){
        error();
    }
    else {
        Order *order = new Order(getOrderCounter(), customerId, getCustomerDistance());
        pendingOrders.push_back(order);
        complete();
    }
}

AddOrder *AddOrder::clone() const {
    return new AddOrder(*this);
}

string AddOrder::toString() const {
    return "Add Order " + std::to_string(customerId);
}

AddCustomer::AddCustomer(const string &customerName, const string &customerType, int distance, int maxOrders) : customerName(customerName), customerType(customerType), distance(distance), maxOrders(maxOrders) {
    if (customerType == "soldier"){
        CustomerType = CustomerType::Soldier;
    }
    else {
        CustomerType = CustomerType::Civilian;
    }
    
}
