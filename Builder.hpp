/**
 * Builder Pattern Implementation
 *  The Builder Pattern is a creational design pattern that allows for the step-by-step construction of complex objects.
 *  It separates the construction of an object from its representation, enabling the same construction process to
 *  create different representations.
   
 * /*UML Diagram
┌───────────────────────────────-┐
│          <<interface>>         │
│          Builder               │
├───────────────────────────────-┤
│ + reset(): void                │
│ + setPartA(): void             │
│ + setPartB(): void             │
│ + setPartC(): void             │
│ + getResult(): Product*        │
└───────────────┬───────────────-┘
                │       
                │ implements    
                │---------------------------------------|
┌───────────────▼───────────────-┐              ┌───────▼────────────────────────┐
│                                │              │                                |  
│      ConcreteBuilder           │              │         Product                │
│                                │              │                                │
│ + reset(): void                │              │ - parts: vector<string>        │
│ + setPartA(): void             │              │                                │
│ + setPartB(): void             │              │ + addPart(part: string): void  │
│ + setPartC(): void             │              │ + showParts(): void            │
│ + getResult(): Product*        │              │                                │
└───────────────────-------------┘              └───────────────────-------------┘      

Sequence Diagram
┌───────────────┐        ┌───────────────┐        ┌───────────────┐
│    Client     │        │    Director   │        │    Builder    │
└───────────────┘        └───────────────┘        └───────────────┘
        │                        │                      │
        │   construct()          │                      │
        │───────────────────────>│                      │
        │                        │   reset()            │
        │                        │─────────────────────>│
        │                        │                      │
        │                        │   setPartA()         │
        │                        │─────────────────────>│
        │                        │                      │
        │                        │   setPartB()         │
        │                        │─────────────────────>│
        │                        │                      │
        │                        │   setPartC()         │
        │                        │─────────────────────>│
        │                        │                      │
        │   getResult()          │                      │
        │<───────────────────────│                      │
        │                        │   getResult()        │
        │                        │─────────────────────>│
        │                        │                      │
└───────────────┘        └───────────────┘      └───────────────┘       │   getResult()                 

Where to use builder pattern:
- When the construction process of an object is complex and involves multiple steps.
- When you want to create different representations of an object using the same construction process.       
- When you want to isolate the construction logic from the object's representation.
- When you want to enforce immutability by constructing objects in a controlled manner.
When not to use:
- When the object being constructed is simple and can be created in a single step.
- When there is no need for different representations of the object.
- When the construction process does not involve multiple steps or configurations.

 */
#pragma once
#include <iostream>
#include <vector>
#include <string>
// Product class
class Product {
private:
    std::vector<std::string> parts;
public:
    void addPart(const std::string& part) {
        parts.push_back(part);
    }
    void showParts() const {
        std::cout << "Product parts: ";
        for (const auto& part : parts) {
            std::cout << part << " ";
        }
        std::cout << std::endl;
    }
};

// Builder interface
class Builder {
public:
    virtual ~Builder() = default;
    virtual void reset() = 0;
    virtual void setPartA() = 0;
    virtual void setPartB() = 0;
    virtual void setPartC() = 0;
    virtual Product* getResult() = 0;
};
// Concrete Builder
class ConcreteBuilder : public Builder {
private:
    Product* product;
public:
    ConcreteBuilder() {
        product = new Product();
    }
    ~ConcreteBuilder() {
        delete product;
    }
    void reset() override {
        delete product;
        product = new Product();
    }
    void setPartA() override {
        product->addPart("PartA");
    }
    void setPartB() override {
        product->addPart("PartB");
    }
    void setPartC() override {
        product->addPart("PartC");  
    }   
    Product* getResult() override {
        return product;
    }
};
// Director class
class Director {
private:
    Builder* builder;
public:
    void setBuilder(Builder* b) {
        builder = b;
    }
    void construct() {
        builder->reset();
        builder->setPartA();
        builder->setPartB();
        builder->setPartC();
    }
};
// Client code example
int builderMain() {
    Director director;
    ConcreteBuilder builder;
    director.setBuilder(&builder);
    director.construct();
    Product* product = builder.getResult();
    product->showParts();
    return 0;
}       

