# circuits_project

## Next Steps
- [X] ~~*ADD the --- stuff you have done*~~
- [ ] Increase customization of GPIO interfacing components
- [ ] Add time/tick control
- [ ] Add more components (clock, delay, LED)
- [ ] Add custom component saving and placing
- [ ] Add save file system
- [ ] Add support for analog input and ADC/DAC components

# Examples/Gallery type thing

# Design Decisions
Below is a more comprehensive description of some of the more complex or significant parts of the code.
## Project Architecture
To add: 
- Picture of/some basic guidance of OOP and inheritances/containments architecture
- Maybe turn the flow of a bit from input to output into a flowchart as well and make it horizontally progressing flowchart to make it look nicer on the screen

#### Example: The flow of a bit from input to output
1. The bit is taken from an input source and is stored as a state on an input component
2. The bit is moved into each wire connected to each pin-out
3. The bit is moved from each wire to the pin-in of any component they are connected to
4. The component runs any necessary computation on the bit and sets it to each pin-out's state
5. The bit is moved from each pin-out to any wire connected to them
6. Repeat steps 3 - 5 until an output component is reached
7. The bit is moved from the wire to the output component
8. The bit is moved from the output component to an output source

#### Maintaining simultaneity
Simultaneity is maintained throughout the circuit by enacting every step to each component before moving on to the next step. These steps are:
1. Move state from the pin-in wires to each pin-in's state
2. Run necessary computation on the pin-in states and set each pin-out's state
3. Move state from the pin-outs to the wires connected to them

## Memory and Pointer Management

#### Component creation
The frontend objects have a reference to them stored in the scene object. The scene object has two lists, one only for components that I maintain, and one for adding objects for the Qt framework to display on the scene. Before a frontend object is deleted, it is removed from these two lists to avoid dangling pointers. In most cases the frontend component is responsible for creating the backend component. In some more complex cases such as the creation and connection of frontend and backend pins an approach similar to the one outlined in the flowchart below is taken. This allows the backend component to be responsible for creating the backend pins while still creating a connection between the frontend and backend pins.

<img src="https://user-images.githubusercontent.com/35043400/224468664-ab5f7433-6c5c-41c6-a5bf-71fd1d1164d3.png" width="650" height="550">

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
