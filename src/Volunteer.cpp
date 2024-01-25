#include "Volunteer.h"

Volunteer::Volunteer(int id, const string &name)
    : id(id), name(name), completedOrderId(NO_ORDER), activeOrderId(NO_ORDER) {}

int Volunteer::getId() const {
    return id;
}

const string &Volunteer::getName() const {
    return name;
}

int Volunteer::getActiveOrderId() const {
    return activeOrderId;
}

int Volunteer::getCompletedOrderId() const {
    return completedOrderId;
}

bool Volunteer::isBusy() const {
    return activeOrderId != NO_ORDER;
}



CollectorVolunteer::CollectorVolunteer(int id, string name, int coolDown)
    : Volunteer(id, name), coolDown(coolDown), timeLeft(0) {}

CollectorVolunteer *CollectorVolunteer::clone() const {
    CollectorVolunteer* cVolunteer = new CollectorVolunteer(getId(), getName(), getCoolDown());
    (*cVolunteer).setTimeLeft(getTimeLeft());
    return cVolunteer;
}

void CollectorVolunteer::step() {
    if (decreaseCoolDown()) {
        completedOrderId = activeOrderId;
        activeOrderId = -1;
    }
}

int CollectorVolunteer::getCoolDown() const {
    return coolDown;
}

int CollectorVolunteer::getTimeLeft() const {
    return timeLeft;
}

bool CollectorVolunteer::decreaseCoolDown() {
    if (timeLeft > 0) {
        timeLeft--;
        return timeLeft == 0;
    }
    return false;
}

bool CollectorVolunteer::hasOrdersLeft() const {
    return true;
}

bool CollectorVolunteer::canTakeOrder(const Order &order) const {
    return !(isBusy());
}

void CollectorVolunteer::acceptOrder(const Order &order) {
    timeLeft = getCoolDown();
    activeOrderId = order.getId();
}

string CollectorVolunteer::toString() const {
    string result = "CollectorVolunteer ID: " + to_string(getId()) + "\n";
    result += "Name: " + getName() + "\n";
    result += "Cool Down: " + to_string(coolDown) + "\n";
    result += "Time Left: " + to_string(timeLeft) + "\n";
    result += "Active Order ID: " + to_string(getActiveOrderId()) + "\n";
    result += "Completed Order ID: " + to_string(getCompletedOrderId()) + "\n";
    return result;
}




LimitedCollectorVolunteer::LimitedCollectorVolunteer(int id, string name, int coolDown, int maxOrders)
    : CollectorVolunteer(id, name, coolDown), maxOrders(maxOrders), ordersLeft(maxOrders) {}

LimitedCollectorVolunteer *LimitedCollectorVolunteer::clone() const {
    LimitedCollectorVolunteer* lCVolunteer = new LimitedCollectorVolunteer(getId(), getName(), getCoolDown(), getMaxOrders());
    (*cVolunteer).setTimeLeft(getTimeLeft());
    return cVolunteer;}

bool LimitedCollectorVolunteer::hasOrdersLeft() const {
    return getNumOrdersLeft() != 0;
}

bool LimitedCollectorVolunteer::canTakeOrder(const Order &order) const {
    return !(isBusy()) && hasOrdersLeft();
}

void LimitedCollectorVolunteer::acceptOrder(const Order &order) {
    timeLeft = getCoolDown();
    activeOrderId = order.getId();
    ordersLeft--;
}

int LimitedCollectorVolunteer::getMaxOrders() const {
    return maxOrders;
}

int LimitedCollectorVolunteer::getNumOrdersLeft() const {
    return ordersLeft;
}

string LimitedCollectorVolunteer::toString() const {
    string result = "LimitedCollectorVolunteer ID: " + to_string(getId()) + "\n";
    result += "Name: " + getName() + "\n";
    result += "Cool Down: " + to_string(coolDown) + "\n";
    result += "Time Left: " + to_string(getTimeLeft()) + "\n";
    result += "Active Order ID: " + to_string(getActiveOrderId()) + "\n";
    result += "Completed Order ID: " + to_string(getCompletedOrderId()) + "\n";
    result += "Max Orders: " + to_string(maxOrders) + "\n";
    result += "Orders Left: " + to_string(ordersLeft) + "\n";
    return result;
}




DriverVolunteer::DriverVolunteer(int id, string name, int maxDistance, int distancePerStep)
    : Volunteer(id, name), maxDistance(maxDistance), distancePerStep(distancePerStep), distanceLeft(0) {}

DriverVolunteer *DriverVolunteer::clone() const {
    return new DriverVolunteer(*this);
}

int DriverVolunteer::getDistanceLeft() const {
    return distanceLeft;
}

int DriverVolunteer::getMaxDistance() const {
    return maxDistance;
}

int DriverVolunteer::getDistancePerStep() const {
    return distancePerStep;
}

bool DriverVolunteer::decreaseDistanceLeft() {
    // Implementation for decreasing distanceLeft
}

bool DriverVolunteer::hasOrdersLeft() const {
    // Implementation for DriverVolunteer
}

bool DriverVolunteer::canTakeOrder(const Order &order) const {
    // Implementation for DriverVolunteer
}

void DriverVolunteer::acceptOrder(const Order &order) {
    // Implementation for DriverVolunteer
}

void DriverVolunteer::step() {
    // Implementation for DriverVolunteer
}

string DriverVolunteer::toString() const {
    // Implementation for DriverVolunteer
}




LimitedDriverVolunteer::LimitedDriverVolunteer(int id, const string &name, int maxDistance, int distancePerStep, int maxOrders)
    : DriverVolunteer(id, name, maxDistance, distancePerStep), maxOrders(maxOrders), ordersLeft(maxOrders) {}

LimitedDriverVolunteer *LimitedDriverVolunteer::clone() const {
    return new LimitedDriverVolunteer(*this);
}

int LimitedDriverVolunteer::getMaxOrders() const {
    return maxOrders;
}

int LimitedDriverVolunteer::getNumOrdersLeft() const {
    return ordersLeft;
}

bool LimitedDriverVolunteer::hasOrdersLeft() const {
    // Implementation for LimitedDriverVolunteer
}

bool LimitedDriverVolunteer::canTakeOrder(const Order &order) const {
    // Implementation for LimitedDriverVolunteer
}

void LimitedDriverVolunteer::acceptOrder(const Order &order) {
    // Implementation for LimitedDriverVolunteer
}

string LimitedDriverVolunteer::toString() const {
    // Implementation for LimitedDriverVolunteer
}
