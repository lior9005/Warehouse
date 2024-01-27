#include "Order.h"

Order::Order(int id, int customerId, int distance)
    : id(id), customerId(customerId), distance(distance), status(OrderStatus::PENDING), collectorId(NO_VOLUNTEER), driverId(NO_VOLUNTEER) {}

Order* Order::clone() const {
    return new Order(*this);
}

int Order::getId() const {
    return id;
}

int Order::getCustomerId() const {
    return customerId;
}

void Order::setStatus(OrderStatus newStatus) {
    status = newStatus;
}

void Order::setCollectorId(int newCollectorId) {
    collectorId = newCollectorId;
}

void Order::setDriverId(int newDriverId) {
    driverId = newDriverId;
}

int Order::getCollectorId() const {
    return collectorId;
}

int Order::getDriverId() const {
    return driverId;
}

OrderStatus Order::getStatus() const {
    return status;
}

int Order::getDistance() const {
    return distance;
}

const std::string Order::toString() const {
    return "OrderId: " + std::to_string(id) + "\n" +
           "OrderStatus: " + getStatusString() + "\n" +
           "CustomerID: " + std::to_string(customerId) + "\n" +
           "Collector: " + (collectorId == -1 ? "None" : std::to_string(collectorId)) + "\n" +
           "Driver: " + (driverId == -1 ? "None" : std::to_string(driverId));
}

const std::string Order::getStatusString() const {
    std::string orderStatus[] = {"PENDING", "COLLECTING", "DELIVERING", "COMPLETED"};
    return orderStatus[static_cast<int>(getStatus())];
}