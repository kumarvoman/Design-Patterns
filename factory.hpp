/**
 * @file factory.hpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-11-02
 * 
 * @copyright Copyright (c) 2025
 * 
 * This class holds the factory pattern implementation in C++.
 * 
 *  Key Components:
 * - Product Interface: An abstract base class with a method for performing an operation.
 * - Concrete Product Classes: Specific implementations of the product interface.
 * - Factory Class: Responsible for creating instances of concrete products based on input parameters.
 * 
 * Features:
 * - Encapsulation of Object Creation: The factory class encapsulates the logic for creating objects.
 * - Flexibility: New product types can be added with minimal changes to the factory.
 * - Adheres to Open/Closed Principle: The factory can be extended without modifying existing code.
 * 
 * Where to use factory pattern:
 * - When the exact types and dependencies of the objects to be created are not known until runtime.
 * - When you want to centralize and manage the creation logic of related objects.
 * - When you want to adhere to the Single Responsibility Principle by separating object creation from business logic.
 * - When you need to provide a library of products and want to expose only their interfaces, not their implementations.
 * 
 * When not to use:
 * - When object creation is straightforward and does not require complex logic.
 * - When the number of product types is small and unlikely to change, making a factory unnecessary.
 * - When performance is critical and the overhead of a factory method is unacceptable.
 *
 * UML Diagram
┌───────────────────────────────┐
│          <<interface>>        │
│           Product             │
├───────────────────────────────┤
│ + operation(): string         │
└───────────────┬───────────────┘
                │       
                │ implements    
                │------------------------------------------|   
┌───────────────▼───────────────┐                  ┌───────▼────────────────────────┐
│                               │                  │                                │
│       ConcreteProductA        │                  │      ConcreteProductB          │
│                               │                  │                                │
│ + operation(): string         │                  │ + operation(): string          │
│                               │                  │                                │  
└───────────────────------------┘                  └───────────────────-------------┘

Sequence Diagram
┌───────────────┐        ┌───────────────┐
│    Client     │        │    Factory    │
└───────────────┘        └───────────────┘
        │                        │
        │   createProduct(type)  │
        │───────────────────────>│
        │                        │
        │    return Product      │
        │<───────────────────────│
        │                        │
        │   use Product          │
        │───────────────────────>│
        │                        │
        │                        │
        │                        │
        │                        │
        │                        │
        │                        │

Explanation:
- The client requests a product from the factory by specifying a type.
- The factory creates and returns an instance of the requested product type.

    The client can then use the product without knowing its concrete class.
    The client interacts with the product through the abstract interface.
    The factory encapsulates the creation logic, allowing for easy extension and maintenance.

 */

#pragma once
#include <iostream>
#include <memory>
#include <string>

// Factory Pattern Implementation
class Product {
public:
    virtual ~Product() = default;
    virtual std::string operation() const = 0;
};  

class ConcreteProductA : public Product {
public:
    std::string operation() const override {
        return "Result of ConcreteProductA";
    }
};

class ConcreteProductB : public Product {
public:
    std::string operation() const override {
        return "Result of ConcreteProductB";
    }
};

class Factory {
public:
    enum class ProductType {
        PRODUCT_A,
        PRODUCT_B
    };

    static std::unique_ptr<Product> createProduct(ProductType type) {
        switch (type) {
            case ProductType::PRODUCT_A:
                return std::make_unique<ConcreteProductA>();
            case ProductType::PRODUCT_B:
                return std::make_unique<ConcreteProductB>();
            default:
                return nullptr;
        }
    }
};

void FactoryMain(Factory::ProductType type) {
    auto product = Factory::createProduct(type);
    if (product) {
        std::cout << product->operation() << std::endl;
    } else {
        std::cout << "Invalid Product Type" << std::endl;
    }
}

