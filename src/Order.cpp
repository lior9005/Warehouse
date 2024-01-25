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
    std::string orderStatus[] = {"PENDING", "COLLECTING", "DELIVERING", "COMPLETED"};
    return "OrderId: " + std::to_string(id) +
           ", OrderStatus: " + orderStatus[static_cast<int>(status)] +
           ", CustomerID: " + std::to_string(customerId) +
           ", Collector: " + std::to_string(collectorId) +
           ", Driver: " + std::to_string(driverId);
}