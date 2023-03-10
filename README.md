# circuits_project

# Examples/Gallery type thing

# Explanation of Design Decisions
As there are many classes that contain and call the functions of each other throughout the code, it might be hard to follow how I approached certain problems even with comments. Below I included a more comprehensive description of some of the more complex or significant parts of the code.
## Project Architecture
To add: 
- Picture of/some basic guidance of OOP and inheritances/containments architecture
- one example of the flow of a bit from entrance to exit

## Memory Management
There are a lot of moving parts and object instances being created both on the frontend and the backend of this program. 
So, I had to pay extra care to how I structure my pointers, deletion algorithms, and destructors such that there are no memory leaks or dangling pointers. 

// POSSIBLY reduce this area because I don't want to sound cocky, I just want to explain my reasoning behind creating this description, maybe just say I thought it would be insighftul to add this description as its not easy to get it from just a read through of the code

#### Component creation/deletion
The frontend objects have a reference to them stored in the scene object. The scene object has two lists, one only for components that I maintain, and one for adding objects for the Qt framework to display on the scene. Furthermore, the frontend objects create their backend counterparts as a part of their constructor. Before an object is deleted from the screen, it is removed from these two lists to avoid dangling pointers.

#### Component frontend/backend relationship
The frontend objects (often labeled with the prefix "graphics") all contain a pointer to their backend counterparts. 
The frontend components' destructors are responsible for calling delete on the backend components. 
Then the pointer pointing to those backend components are set to nullptr and the frontend component is destructed as well. 
All other objects that hold a reference to the deleted backend or frontend components (such as the pins) are also deleted in the destructor of either the frontend or backend component respectively.
Through this system, most of the projects' memory management can be handled in a fairly straight forward manner. 

#### Managing wires
However, there are some complications that appear due to the existence of wires. This is because both objects that the wire is connected to hold a pointer to the wire.
In order to prevent wild pointers I handle the deletion of wires or the deletion of components that cause wires to be deleted as follows: 
1. When a wire's destructor is called through the delete keyword, the wire "disconnects" itself from any pins by removing any references of itself from those pins
2. When a component's destructor is called through the delete keyword, the component calls delete on each one of it's pins, and then clears all reference to the pins.
When the delete keyword is called on a pin, the pin calles the delete keyword on each one of it's wires, and then clears all reference to the wires. The destructor of wires is as outlined above.
3. When both wires and components are selected to be deleted at once, I go through the selected items and delete the wires first so that the components deleting any other wires connected to them does not cause dangling pointers.

These actions that are applied to a frontend component or wire are also propogated to their backend counterparts in a similar fashion.
