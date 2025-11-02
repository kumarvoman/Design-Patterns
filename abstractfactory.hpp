// Abstract Factory Pattern
// Product families: GUI elements for different operating systems
/*
Key differences illustrated in the example:

Scope:
Factory Pattern creates a single type of object (Animal)
Abstract Factory creates families of related objects (GUI elements: buttons and checkboxes)

Methods:
Factory Pattern has one creation method (createAnimal)
Abstract Factory has multiple creation methods (createButton, createCheckbox)

Abstraction Level:
Factory Pattern works at product level
Abstract Factory works at family level (entire GUI theme)

Use Case:
Factory Pattern: When you need different variations of a single object
Abstract Factory: When you need consistent families of related objects (like UI components that match a specific operating system's style)

Flexibility:
Factory Pattern is simpler and easier to modify for a single product line
Abstract Factory provides consistency across multiple related product lines but is more complex to modify

key components:
- Abstract Products: Interfaces for a family of related products (e.g., Button, Checkbox).
- Concrete Products: Implementations of the abstract products for different variants (e.g., WindowsButton and MacButton, WindowsCheckbox and MacCheckbox).
- Abstract Factory: An interface declaring creation methods for each abstract product (e.g., GUIFactory).
- Concrete Factories: Implementations of the abstract factory that create concrete products (e.g., WindowsFactory and MacFactory).      

Features:
- Consistency: Ensures that products from the same family are used together.
- Flexibility: New product families can be added without changing existing code.
- Adheres to Open/Closed Principle: New product variants can be introduced by adding new factories

When to use abstract factory pattern:
    * - When you need to ensure that related products are used together and want to enforce this at the creation level.
    * - When your system needs to be independent of how its products are created, composed, and represented.
    * - When you want to provide a library of products and want to expose only their interfaces, not their implementations.
    * 
When not to use:
    * - When there is only one product family and no need for multiple variants.
    * - When the complexity of multiple factories outweighs the benefits of consistency.
    * - When performance is critical and the overhead of multiple factory methods is unacceptable.
    *
    * UML Diagram
    * ┌───────────────────────────────┐
    * │     <<interface>>             │
    * |    GUIFactory                 │
    * ├───────────────────────────────┤
    * │ + createButton(): Button      │  
    * │ + createCheckbox(): Checkbox  │
    * └───────────────┬───────────────┘
    *                 │
    *                 │ implements
    *                 │------------------------------------------|
    * ┌───────────────▼───────────────┐                  ┌───────▼────────────────────────┐
    * │                               │                  │                                │
    * │       WindowsFactory          │                  │      MacFactory                │
    * │                               │                  │                                │
    * │ + createButton(): Button      │                  │ + createButton(): Button       │
    * │ + createCheckbox(): Checkbox  │                  │ + createCheckbox(): Checkbox   │
    * └───────────────────------------┘                  └───────────────────-------------┘
    *                 ▲                                    ▲
    *                 │                                    │
    *                 │                                    │
    * ┌───────────────┴───────────────┐        ┌───────────┴───────────────┐
    * │         WindowsButton         │        │      MacButton            │
    * ├───────────────────────────────┤        ├───────────────────────────┤
    * │ + render(): void              │        │ + render(): void          │
    * └───────────────────-----------─┘        └───────────────────────────┘
    *                 ▲                                ▲
    *                 │                                │
    *                 │                                │
    * ┌───────────────┴───────────────┐    ┌───────────┴───────────────┐
    * │       WindowsCheckbox         │    │      MacCheckbox          │
    * ├───────────────────────────────┤    ├───────────────────────────┤
    * │ + render(): void              │    │ + render(): void          │
    * └───────────────────-----------─┘    └───────────────────────────┘
    *                 ▲                                ▲
    *                 │                                │
    *                 │                                │
    * ┌───────────────┴───────────────┐    ┌───────────┴───────────────┐
    * │       WindowsCheckbox         │    │      MacCheckbox          │
    * ├───────────────────────────────┤    ├───────────────────────────┤
    * │ + render(): void              │    │ + render(): void          │
    * └───────────────────-----------─┘    └───────────────────────────┘
    *                 ▲                                ▲
    *                 │                                │
    *                 │                                │
    * ┌───────────────┴───────────────┐    ┌───────────┴───────────────┐    
    * │       WindowsCheckbox         │    │      MacCheckbox          │
    * ├───────────────────────────────┤    ├───────────────────────────┤
    * │ + render(): void              │    │ + render(): void          │
    * └───────────────────-----------─┘    └───────────────────────────┘
    *                 ▲                                    ▲
    *                 │                                    │
    *                 │                                    │
    * ┌───────────────┴───────────────┐        ┌───────────┴───────────────┐
    * │         Client                │        │    Abstract Factory       │
    * └───────────────┬───────────────┘        └───────────────┬───────────┘
    *                 │                                        │
    *     createButton()                                       │
    *   ────────────────────────────────────────────>          │
    *                 │                                        │
    *     createCheckbox()                                     │
    *   ────────────────────────────────────────────>          │
    *                 │                                        │    
    *     return Button                                        │
    *   <────────────────────────────────────────────          │
    *                 │                                        │
    *     return Checkbox                                      │
    *   <────────────────────────────────────────────          │
    *                 │                                        │
    *     use Button                                           │
    *   ───────────>                                           │
    *                 │                                        │
    *     use Checkbox                                         │
    *   ────────────────────────────────────────────>          │
    * 
*/
#include <iostream>
#include <memory>

class Button {
public:
    virtual void render() = 0;
};

class Checkbox {
public:
    virtual void render() = 0;
};

// Concrete Products for Windows
class WindowsButton : public Button {
public:
    void render() { std::cout << "Render Windows button"; }
};

class WindowsCheckbox : public Checkbox {
public:
    void render() { std::cout << "Render Windows checkbox"; }
};

// Concrete Products for MacOS
class MacButton : public Button {
public:
    void render() { std::cout << "Render MacOS button"; }
};

class MacCheckbox : public Checkbox {
public:
    void render() { std::cout << "Render MacOS checkbox"; }
};

// Abstract Factory
class GUIFactory {
public:
    virtual Button* createButton() = 0;
    virtual Checkbox* createCheckbox() = 0;
};

// Concrete Factories
class WindowsFactory : public GUIFactory {
public:
    Button* createButton() { return new WindowsButton(); }
    Checkbox* createCheckbox() { return new WindowsCheckbox(); }
};

class MacFactory : public GUIFactory {
public:
    Button* createButton() { return new MacButton(); }
    Checkbox* createCheckbox() { return new MacCheckbox(); }
};

void AbstractFactoryMain(GUIFactory& factory) {
    std::unique_ptr<Button> button(factory.createButton());
    std::unique_ptr<Checkbox> checkbox(factory.createCheckbox());
    button->render();
    std::cout << std::endl;
    checkbox->render();
    std::cout << std::endl;
}