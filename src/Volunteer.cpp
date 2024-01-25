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
    CollectorVolunteer* clone = new CollectorVolunteer(getId(), getName(), getCoolDown());
    clone->setTimeLeft(getTimeLeft());
    clone->activeOrderId = getActiveOrderId();
    clone->completedOrderId = getCompletedOrderId();
    return clone;
}

void CollectorVolunteer::step() {
    if (decreaseCoolDown()) {
        completedOrderId = activeOrderId;
        activeOrderId = NO_ORDER;
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

void CollectorVolunteer::setTimeLeft(int newTimeLeft) {
    timeLeft = newTimeLeft;
}

string CollectorVolunteer::toString() const {
        return "CollectorVolunteer ID: " + std::to_string(getId()) +
           ", Name: " + getName() +
           ", Cool Down: " + std::to_string(coolDown) +
           ", Time Left: " + std::to_string(timeLeft) +
           ", Active Order ID: " + std::to_string(activeOrderId) +
           ", Completed Order ID: " + std::to_string(completedOrderId);
}



LimitedCollectorVolunteer::LimitedCollectorVolunteer(int id, string name, int coolDown, int maxOrders)
    : CollectorVolunteer(id, name, coolDown), maxOrders(maxOrders), ordersLeft(maxOrders) {}

LimitedCollectorVolunteer *LimitedCollectorVolunteer::clone() const {
    LimitedCollectorVolunteer* clone = new LimitedCollectorVolunteer(getId(), getName(), getCoolDown(), getMaxOrders());
    clone->setTimeLeft(getTimeLeft());
    clone->activeOrderId = getActiveOrderId();
    clone->completedOrderId = getCompletedOrderId();
    clone->setOrdersLeft(getNumOrdersLeft());
    return clone;
}

bool LimitedCollectorVolunteer::hasOrdersLeft() const {
    return getNumOrdersLeft() != 0;
}

bool LimitedCollectorVolunteer::canTakeOrder(const Order &order) const {
    return !(isBusy()) && hasOrdersLeft();
}

void LimitedCollectorVolunteer::acceptOrder(const Order &order) {
    setTimeLeft(getCoolDown());
    activeOrderId = order.getId();
    ordersLeft--;
}

int LimitedCollectorVolunteer::getMaxOrders() const {
    return maxOrders;
}

int LimitedCollectorVolunteer::getNumOrdersLeft() const {
    return ordersLeft;
}

void LimitedCollectorVolunteer::setOrdersLeft(int newOrdersLeft) {
    ordersLeft = newOrdersLeft;
}

string LimitedCollectorVolunteer::toString() const {
    return "LimitedCollectorVolunteer ID: " + std::to_string(getId()) +
        ", Name: " + getName() +
        ", Cool Down: " + std::to_string(getCoolDown()) +
        ", Time Left: " + std::to_string(getTimeLeft()) +
        ", Active Order ID: " + std::to_string(activeOrderId) +
        ", Completed Order ID: " + std::to_string(completedOrderId) +
        ", Max Orders: " + std::to_string(maxOrders) +
        ", Orders Left: " + std::to_string(ordersLeft);
}


DriverVolunteer::DriverVolunteer(int id, string name, int maxDistance, int distancePerStep)
    : Volunteer(id, name), maxDistance(maxDistance), distancePerStep(distancePerStep), distanceLeft(0) {}

DriverVolunteer *DriverVolunteer::clone() const {
    DriverVolunteer* clone = new DriverVolunteer(getId(), getName(), getMaxDistance(), getDistancePerStep());
    clone->setDistanceLeft(getDistanceLeft());
    return clone;
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
    setDistanceLeft(distanceLeft-distancePerStep);
    if(distanceLeft < 0)
        setDistanceLeft(0);
    return true;
}

bool DriverVolunteer::hasOrdersLeft() const {
    return true;
}

bool DriverVolunteer::canTakeOrder(const Order &order) const {
    return (order.getDistance() <= maxDistance) && (distanceLeft == 0);
}

void DriverVolunteer::acceptOrder(const Order &order) {
    setDistanceLeft(order.getDistance());
}

void DriverVolunteer::step() {
    decreaseDistanceLeft();
}

void DriverVolunteer::setDistanceLeft(int newDistanceLeft) {
    distanceLeft = newDistanceLeft;
}

string DriverVolunteer::toString() const {
    return "DriverVolunteer ID: " + std::to_string(getId()) +
        ", Name: " + getName() +
        ", Max Distance: " + std::to_string(maxDistance) +
        ", Distance Per Step: " + std::to_string(distancePerStep) +
        ", Distance Left: " + std::to_string(distanceLeft);
}



LimitedDriverVolunteer::LimitedDriverVolunteer(int id, const string &name, int maxDistance, int distancePerStep, int maxOrders)
    : DriverVolunteer(id, name, maxDistance, distancePerStep), maxOrders(maxOrders), ordersLeft(maxOrders) {}

LimitedDriverVolunteer *LimitedDriverVolunteer::clone() const {
    LimitedDriverVolunteer* clone = new LimitedDriverVolunteer(getId(), getName(), getMaxDistance(), getDistancePerStep(), getMaxOrders());
    clone->setDistanceLeft(getDistanceLeft());
    clone->setOrdersLeft(getNumOrdersLeft());
    return clone;
}

int LimitedDriverVolunteer::getMaxOrders() const {
    return maxOrders;
}

int LimitedDriverVolunteer::getNumOrdersLeft() const {
    return ordersLeft;
}

bool LimitedDriverVolunteer::hasOrdersLeft() const {
    return ordersLeft!=0;
}

bool LimitedDriverVolunteer::canTakeOrder(const Order &order) const {
    return hasOrdersLeft() && (order.getDistance() <= getMaxDistance()) && (getDistanceLeft() == 0);
}

void LimitedDriverVolunteer::acceptOrder(const Order &order) {
    ordersLeft--;
    setDistanceLeft(order.getDistance());
}

void LimitedDriverVolunteer::setOrdersLeft(int newOrdersLeft) {
    ordersLeft = newOrdersLeft;
}

string LimitedDriverVolunteer::toString() const {
    return "LimitedDriverVolunteer ID: " + std::to_string(getId()) +
        ", Name: " + getName() +
        ", Max Distance: " + std::to_string(getMaxDistance()) +
        ", Distance Per Step: " + std::to_string(getDistancePerStep()) +
        ", Distance Left: " + std::to_string(getDistanceLeft()) +
        ", Max Orders: " + std::to_string(getMaxOrders()) +
        ", Orders Left: " + std::to_string(getNumOrdersLeft());
}
