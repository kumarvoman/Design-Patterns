/*
------------------------------
Decorator pattern : Structural
------------------------------

Open for extension, closed for modification
Here, the Extended class has IS-A & Has-A (both) the relationship with parent class.

E.g. BasePizza & CheeseBurstPizza

CheeseBurstPizza will extend the BasePizza class but also have an object of BasePizza.
Declaration will look smthing like below -

Class CheeseBurstPizza : private BasePizza {
	BasePizza _pizza;
	//other data members
}

When to Use:
Dynamically add behaviour - Adding toppings on pizza
Avoid class explosion
Extend functionality without modification
Implement the open close principle
Avoid multiple Inheritance
Handle objects with Chained or  accumulative modifications

When Not to Use:
Fixed and Limited functionality
Performance critical sections
Excessive complexity and readability issues
When Identity of object is crucial
When a simpler alternative exists
Hidden logic and refactoring risks
When IS-A Relationship is violated

*/
