/*
Decorator.hpp

It defines the Decorator design pattern implementation in C++.
It includes the abstract base class 'Observer', the 'Subject' class that manages observers,
and concrete observer classes that display weather data in different formats.   

Key Components:
- Coffee Interface: An abstract base class with methods for getting the description and cost.
- Concrete Coffee Classes: SimpleCoffee is a basic implementation.
- Decorator Classes: MilkDecorator, SugarDecorator, and WhipDecorator add additional features.

Features:
- Dynamic Behavior: Add or remove responsibilities at runtime
- Transparent to Clients: Decorated objects maintain the same interface as the original
- Combines Multiple Behaviors: Stack multiple decorators to create complex behavior
- Adheres to Open/Closed Principle: New functionality can be added without modifying existing code

UML Design Pattern Diagram:
![UML Diagram](file:///Users/Voman.Kumar/Downloads/decorator.svg)

Where to use decorator pattern:
- When you need to add responsibilities to individual objects dynamically and transparently, without affecting other objects
- When subclassing would lead to an exponential rise in new classes for every combination of features
- When you want to adhere to the Single Responsibility Principle by dividing functionality between classes with unique areas

When not to use:
- When a simpler solution like subclassing suffices
- When performance is critical and the overhead of multiple small objects is unacceptable.

*/

#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <memory>

// Decorator Pattern Implementation

class Coffee {
public:
    virtual ~Coffee() = default;
    virtual std::string getDescription() const = 0;
    virtual double getCost() const = 0;
};

class SimpleCoffee : public Coffee {
public:
    std::string getDescription() const override {
        return "Simple Coffee";
    }

    double getCost() const override {
        return 2.0;
    }
};

class CoffeeDecorator : public Coffee {
protected:
    std::unique_ptr<Coffee> coffee;
public:
    CoffeeDecorator(std::unique_ptr<Coffee> c) : coffee(std::move(c)) {}
    virtual ~CoffeeDecorator() = default;
};

class MilkDecorator : public CoffeeDecorator {
public:
    MilkDecorator(std::unique_ptr<Coffee> c) : CoffeeDecorator(std::move(c)) {}
    std::string getDescription() const override {
        return coffee->getDescription() + ", Milk";
    }   

    double getCost() const override {
        return coffee->getCost() + 0.5;
    }
};

class SugarDecorator : public CoffeeDecorator {
public:
    SugarDecorator(std::unique_ptr<Coffee> c) : CoffeeDecorator(std::move(c)) {}
    std::string getDescription() const override {
        return coffee->getDescription() + ", Sugar";
    }

    double getCost() const override {
        return coffee->getCost() + 0.2;
    }
};  

class WhipDecorator : public CoffeeDecorator {
public:
    WhipDecorator(std::unique_ptr<Coffee> c) : CoffeeDecorator(std::move(c)) {}
    std::string getDescription() const override {
        return coffee->getDescription() + ", Whip";
    }

    double getCost() const override {
        return coffee->getCost() + 0.7;
    }
};  

// Example usage
int Decoratormain() {        
    std::unique_ptr<Coffee> myCoffee = std::make_unique<SimpleCoffee>();
    myCoffee = std::make_unique<MilkDecorator>(std::move(myCoffee));
    myCoffee = std::make_unique<SugarDecorator>(std::move(myCoffee));
    myCoffee = std::make_unique<WhipDecorator>(std::move(myCoffee));

    std::cout << "Description: " << myCoffee->getDescription() << std::endl;
    std::cout << "Cost: $" << myCoffee->getCost() << std::endl;

    return 0;
}

// End of Decorator.hpp
