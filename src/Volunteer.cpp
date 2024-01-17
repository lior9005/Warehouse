#include "Volunteer.h"

Volunteer::Volunteer(int id, const string &name)
    : id(id), name(name), completedOrderId(-1), activeOrderId(-1) {}

Volunteer::Volunteer(const Volunteer &origin)
    : id(origin.getId()), name(origin.getName()), completedOrderId(origin.getCompletedOrderId()), activeOrderId(origin.getActiveOrderId()) {}

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
    return activeOrderId != -1;
}



CollectorVolunteer::CollectorVolunteer(int id, string name, int coolDown)
    : Volunteer(id, name), coolDown(coolDown), timeLeft(0) {}

CollectorVolunteer::CollectorVolunteer(const CollectorVolunteer &origin)
    : Volunteer(origin), coolDown(origin.getCoolDown()), timeLeft(origin.getTimeLeft()) {}       

CollectorVolunteer *CollectorVolunteer::clone() const {
    return &CollectorVolunteer(this);
}

void CollectorVolunteer::step() {
    if (timeLeft > 0) {
        timeLeft--;
        if (timeLeft == 0) {
            completedOrderId = activeOrderId;
            activeOrderId = NO_ORDER;
        }
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
    // Implementation for CollectorVolunteer
}

bool CollectorVolunteer::canTakeOrder(const Order &order) const {
    // Implementation for CollectorVolunteer
}

void CollectorVolunteer::acceptOrder(const Order &order) {
    // Implementation for CollectorVolunteer
}

string CollectorVolunteer::toString() const {
    // Implementation for CollectorVolunteer
}




LimitedCollectorVolunteer::LimitedCollectorVolunteer(int id, string name, int coolDown, int maxOrders)
    : CollectorVolunteer(id, name, coolDown), maxOrders(maxOrders), ordersLeft(maxOrders) {}

LimitedCollectorVolunteer *LimitedCollectorVolunteer::clone() const {
    return new LimitedCollectorVolunteer(*this);
}

bool LimitedCollectorVolunteer::hasOrdersLeft() const {
    // Implementation for LimitedCollectorVolunteer
}

bool LimitedCollectorVolunteer::canTakeOrder(const Order &order) const {
    // Implementation for LimitedCollectorVolunteer
}

void LimitedCollectorVolunteer::acceptOrder(const Order &order) {
    // Implementation for LimitedCollectorVolunteer
}

int LimitedCollectorVolunteer::getMaxOrders() const {
    return maxOrders;
}

int LimitedCollectorVolunteer::getNumOrdersLeft() const {
    return ordersLeft;
}

string LimitedCollectorVolunteer::toString() const {
    // Implementation for LimitedCollectorVolunteer
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
