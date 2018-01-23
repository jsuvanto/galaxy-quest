#include "statistics.hh"
#include "stateexception.hh"

#include <QtDebug>


Student::Statistics::Statistics():
    saved_ships_(0), lost_ships_(0), points_(0), credits_(0) {
    invariant();

    // Test that the constructor has initialised the values as intended.
    Q_ASSERT(saved_ships_ == 0 && lost_ships_ == 0 && points_ == 0 && credits_ == 0); // Postcondition
}

void Student::Statistics::addSavedShip() {
    invariant();
    ++saved_ships_;
    invariant();
}

unsigned Student::Statistics::getSavedShips() const {
    invariant();
    return saved_ships_;
}

void Student::Statistics::addLostShip() {
    invariant();
    ++lost_ships_;
    invariant();
}

unsigned Student::Statistics::getLostShips() const {
    invariant();
    return lost_ships_;
}

void Student::Statistics::addPoints(unsigned int amount) {
    invariant();
    points_ = points_ + amount;
    invariant();
}

void Student::Statistics::reducePoints(unsigned int amount) {
    invariant();

    if (amount > points_) {
        throw Common::StateException("Trying to reduce points below zero.");
    } else {
        points_ -= amount; // Reduce points normally.
    }

    invariant();
}

unsigned Student::Statistics::getPoints() const {
    invariant();
    return points_;
}

void Student::Statistics::addCredits(unsigned int amount) {
    invariant();
    credits_ = credits_ + amount;
    invariant();
}

void Student::Statistics::reduceCredits(unsigned int amount) {
    invariant();
    if (amount > credits_) {
        throw Common::StateException("Trying to reduce more money than player has.");
    } else {
        credits_ -= amount;
    }
    invariant();
}

int Student::Statistics::getCreditBalance() const {
    invariant();
    return credits_;
}

void Student::Statistics::invariant() const {
    if (credits_ < MAX_LOAN_ALLOWANCE) {
        throw Common::StateException("Invariant broken.");
    }
}
