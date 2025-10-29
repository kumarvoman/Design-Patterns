# Design-Patterns
How to code each design pattern in C++ language.

Creational Design Pattern - 
1. <a href="https://github.com/kumarvoman/Design-Patterns/blob/main/Singleton.hpp">Singleton</a>
2. Builder
3. Prototype
4. Factory
5. Abstract Factory
6. Dependency Injection Pattern.

Structural Design Patterns
1. Adapter
2. Bridge
3. Composite
4. <a href="https://github.com/kumarvoman/Design-Patterns/blob/main/Decorator.hpp">Decorator</a>
5. Facade
6. Proxy
7. Flyweight

Behavioral Design Pattern
1. Chain of Reponsibility
2. Command
3. Iterator
4. Mediator
5. Memento
6. <a href="https://github.com/kumarvoman/Design-Patterns/blob/main/Observer.hpp">Observer</a>
7. State
8. <a href="https://github.com/kumarvoman/Design-Patterns/blob/main/Strategy.hpp">Strategy</a>
9. Visitor
--------------------------------------------------------------

<h2>When to Pick which design pattern</h2>
<h3>Creational Patterns</h3>
<b>Singleton</b>: Use when you need to ensure that only one instance of a class exists throughout the system.

<b>Factory</b>: Use when you want to create objects but defer the instantiation to subclasses, which helps encapsulate creation logic.

<b>Prototype</b>: Use when object creation is complex or costly, as it allows you to create new objects by copying an existing one.

<h3>Structural Patterns</h3>
<b>Decorator</b>: for dynamically adding responsibilities to objects without altering their original interface.

<b>Adapter</b>: for adapting an object's interface to be compatible with a client that expects a different one.

<b>Composite</b>: for representing a part-whole hierarchy where you need to treat individual objects and compositions of objects uniformly.

<b>Strategy</b>: when you want to swap out an algorithm at runtime, which is a different concept than adding behavior to an object.

<b>Facade</b>: to provide a simpler, single-point entry into a complex subsystem.

<h3>Behavioral Patterns</h3>
<b>Strategy</b>: Use when you have multiple algorithms that can perform the same task and you want to allow the client to choose one at runtime.

<b>Observer</b>: Use to establish a one-to-many dependency between objects so that when one object changes state, all its dependents are notified and updated automatically.

<b>State</b>: Use when an object's behavior needs to change based on its internal state, allowing the object to change its behavior without altering its class.
