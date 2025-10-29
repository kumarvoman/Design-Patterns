/*Strategy.hpp

This implementation includes:
- Strategy design pattern
- Context class
- Concrete strategy classes
- Client code example
Key Components:
- Strategy Interface: Abstract base class with execute() method
- Concrete Strategies: Different implementations of the strategy interface
- Context Class: Uses a strategy to perform an operation
Features:
- Encapsulates algorithms: Different strategies can be swapped at runtime
- Promotes code reusability: New strategies can be added without modifying existing code
- Adheres to Open/Closed Principle: Open for extension, closed for modification

UML Design Pattern Diagram:
![UML Diagram](file:///Users/Voman.Kumar/Downloads/strategy.svg)

/*UML Diagram
┌───────────────────────────────-┐
│          <<interface>>         │
│           Strategy             │
├───────────────────────────────-┤
│ + execute(data: string): string│
└───────────────┬───────────────-┘
                │       
                │ implements
                │---------------------------------------|
┌───────────────▼───────────────-┐              ┌───────▼────────────────────────┐
|                                │              │                                |  
│ ConcreteStrategyA              │              │ ConcreteStrategyB              │
│                                │              │                                │
│ + execute(data: string): string|              │ + execute(data: string): string│
│                                │              │                                │
│                                │              │                                │
│                                │              │                                │
└───────────────────-------------┘              └───────────────────-------------┘
                ▲
                │
                │ uses
                │
┌───────────────┴──────────────--------─┐
│           Context                     │
├───────────────────────────────--------┤
│ - strategy: Strategy*                 │
├──────────────────────────────---------┤
│ + setStrategy(strat: Strategy*): void │
│ + executeStrategy(data: string): void │
└──────────────────────────────--------─┘

Sequence Diagram
┌───────────────┐        ┌───────────────┐        ┌───────────────┐
│    Client     │        │    Context    │        │   Strategy    │
└───────────────┘        └───────────────┘        └───────────────┘
        │                        │                      │
        │   setStrategy(A)       │                      │ 
        │───────────────────────>│                      │
        │                        │   execute(data)      │
        │                        │─────────────────────>│
        │                        │                      │   <execute(data)>     
        │                        │<─────────────────────│
        │                        │                      │
        │   executeStrategy(data)│                      │
        │────────────────────────>│                     │
        │                        │   execute(data)      │
        │                        │─────────────────────>│
        │                        │                      │   <execute(data)>     
        │                        │<─────────────────────│  
        │                        │                      │
└───────────────┘        └───────────────┘      └───────────────┘

Where to use Strategy Pattern :

1. Sorting Algorithms
Different sorting strategies (quick sort, merge sort, bubble sort)
Switching sorting algorithms based on data size or type
2. Compression Algorithms
Different compression strategies (ZIP, RAR, GZIP)
Selecting compression based on file type or user preference
3. Payment Methods
Different payment strategies (credit card, PayPal, cryptocurrency)
Selecting payment method at runtime based on user choice

- When you have multiple algorithms for a specific task and want to switch between them dynamically
- When you want to avoid conditional statements for selecting algorithms
- When you want to encapsulate related algorithms for better organization and maintainability

When not to use:
- When the number of strategies is small and unlikely to change
- When performance is critical and the overhead of strategy objects is unacceptable 
*/

#pragma once
#include <iostream>
#include <memory>
#include <string>

// Strategy Interface
class Strategy {
public:
    virtual ~Strategy() = default;
    virtual std::string execute(const std::string& data) const = 0;
};  

// Concrete Strategy A
class ConcreteStrategyA : public Strategy {
public:
    std::string execute(const std::string& data) const override {
        return "Strategy A processed: " + data;
    }
};

// Concrete Strategy B
class ConcreteStrategyB : public Strategy {
public:
    std::string execute(const std::string& data) const override {
        return "Strategy B processed: " + data;
    }
};

// Context Class
class Context {
private:
    std::unique_ptr<Strategy> strategy;
public:
    Context(std::unique_ptr<Strategy> strat) : strategy(std::move(strat)) {}
    void setStrategy(std::unique_ptr<Strategy> strat) {
        strategy = std::move(strat);
    }

    void executeStrategy(const std::string& data) const {
        if (strategy) {
            std::cout << strategy->execute(data) << std::endl;
        } else {
            std::cout << "No strategy set." << std::endl;
        }
    }
};
// Client code example
int strategyMain() {
    Context context(std::make_unique<ConcreteStrategyA>());
    context.executeStrategy("Input Data 1");
    context.setStrategy(std::make_unique<ConcreteStrategyB>());
    context.executeStrategy("Input Data 2");
    return 0;
}
