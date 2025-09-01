/*
Singleton Design Pattern
This pattern ensures that a class has only one instance and provides a global point of access to it.

Usage:
Real-World Examples:
    Operating Systems:
    File system managers
    Device drivers
    System registries
Web Applications:
    Session managers
    Authentication services
    Application context
Desktop Applications:
    Application controllers
    Plugin managers
    Clipboard managers
Mobile Development: 
    Location services
    Network managers
    Data persistence layers

When NOT to use Singleton:
❌ Avoid when:
    You need multiple instances
    Testing becomes difficult
    It creates tight coupling
    Simple dependency injection would work better

Alternative:  Dependency Injection

┌─────────────────────────────────────────────────────────────────────────────┐
│                               <<singleton>>                                 │
│                                Singleton                                    │
├─────────────────────────────────────────────────────────────────────────────┤
│ - instance: Singleton* {static}                                             │
│ - initFlag: once_flag {static}                                              │
├─────────────────────────────────────────────────────────────────────────────┤
│ - Singleton()                                                               │
│ - ~Singleton()                                                              │
│ - Singleton(other: Singleton&) {deleted}                                    │
│ - operator=(other: Singleton&): Singleton& {deleted}                        │
│ + getInstance(): Singleton& {static}                                        │
│ + doSomething(): void                                                       │
└─────────────────────────────────────────────────────────────────────────────┘
                                        ▲
                                        │
                                        │ creates/manages
                                        │
                                        ● (self-reference)


┌─────────────────────────────────────────────────────────────────────────────┐
│                            Sequence Diagram                                 │
├─────────────────────────────────────────────────────────────────────────────┤
│                                                                             │
│ Client          Singleton Class                                             │
│   │                   │                                                     │
│   │ getInstance()     │                                                     │
│   ├──────────────────►│                                                     │
│   │                   │ std::call_once(initFlag, lambda)                    │
│   │                   │ [if first call]                                     │
│   │                   │ ├─ new Singleton()                                  │
│   │                   │ └─ assign to instance                               │
│   │ return instance&  │                                                     │
│   │◄──────────────────┤                                                     │
│   │                   │                                                     │
│   │ doSomething()     │                                                     │
│   ├──────────────────►│                                                     │
│   │                   │                                                     │
└─────────────────────────────────────────────────────────────────────────────┘


┌─────────────────────────────────────────────────────────────────────────────┐
│                        Pattern Structure                                    │
├─────────────────────────────────────────────────────────────────────────────┤
│                                                                             │
│  ┌─────────────────┐                                                        │
│  │     Client      │                                                        │
│  └─────────────────┘                                                        │
│           │                                                                 │
│           │ getInstance()                                                   │
│           ▼                                                                 │
│  ┌─────────────────┐     ┌─────────────────┐                                │
│  │   Singleton     │────►│   Singleton     │                                │
│  │    (Class)      │     │   (Instance)    │                                │
│  └─────────────────┘     └─────────────────┘                                │
│           │                       ▲                                         │
│           └───────────────────────┘                                         │
│              manages single instance                                        │ 
│                                                                             │
└─────────────────────────────────────────────────────────────────────────────┘


┌─────────────────────────────────────────────────────────────────────────────┐
│                         Key UML Elements                                    │
├─────────────────────────────────────────────────────────────────────────────┤
│                                                                             │
│ Stereotypes:                                                                │
│ • <<singleton>> - Indicates singleton pattern                               │
│ • {static} - Static members                                                 │
│ • {deleted} - Deleted functions (C++11)                                     │
│                                                                             │
│ Visibility:                                                                 │
│ • - (private) - Constructor, destructor, copy operations                    │
│ • + (public) - getInstance() and business methods                           │
│                                                                             │
│ Relationships:                                                              │
│ • Self-reference with filled diamond (composition)                          │
│ • The class manages its own single instance                                 │
│                                                                             │
│ Thread Safety Features:                                                     │
│ • std::once_flag ensures thread-safe initialization                         │
│ • std::call_once guarantees single execution                                │
│                                                                             │
└─────────────────────────────────────────────────────────────────────────────┘

Key UML Design Elements:
1. Class Structure:
    Private constructor prevents direct instantiation
    Deleted copy constructor/assignment prevents copying
    Static getInstance() provides global access point
    Static members maintain single instance
2. Relationships:
    Self-composition: Class manages its own instance
    No inheritance: Singleton is typically a leaf class
    Client dependency: Clients depend on Singleton class
3. Stereotypes & Constraints:
    <<singleton>>: UML stereotype indicating pattern
    {static}: Static member notation
    {deleted}: C++11 deleted function notation
4. Thread Safety (Your Implementation):
    std::call_once(initFlag, []() {
        instance = new Singleton();
    });
5. Pattern Participants:
    Singleton Class: Defines getInstance() and maintains instance
    Client: Uses getInstance() to access the singleton
    Instance: The single object managed by the class

*/


#include <mutex>

class Singleton {
public:
    static Singleton& getInstance() {
        std::call_once(initFlag, []() {
            instance = new Singleton();
        });
        return *instance;
    }

    // Example method
    void doSomething() {}

private:
    Singleton() = default;
    ~Singleton() = default;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    static Singleton* instance;
    static std::once_flag initFlag;
};

Singleton* Singleton::instance = nullptr;
std::once_flag Singleton::initFlag;

void singletonrunner() {
    Singleton& instance = Singleton::getInstance();
    instance.doSomething();
}
