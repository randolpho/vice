OMGWTF Contest Submission by Randolpho St. John
randolpho@gmail.com


Title:
VICE, the Virtual Integrated Circuit Engine


Build Instructions:
Building my submission should be fairly straightforward. Simply load "OMGWTF Contest.sln", build it, and execute the SkeletonSolution executable. The VICE project should be compiled as in Release configuration; this property should already be set in the project configuration. A complete unit test suite of the VICE engine is included in the solution, but the VICE project will need to be changed to Debug rather than Release configuration in order to execute it -- specifically, _DEBUG must be set as a preprocessor value. 

My submission uses the Win32 skeleton solution provided from the website, implementing the four function stubs. 


Contest Introduction:
I was a little slow to start this contest, because I hate buggy or poorly though-out code. I decided to take the "Clever" (or perhaps "Insane") route and forego the "Buggy" route altogether. At least that was the goal.

After some initial false starts and unsatisfactory ideas, I decided to approach the contest from the right frame of mind, or rather an altered one: I tossed back a bottle of NyQuil and sat down at my desk with a pad and pen. 

I awoke two days later in danger of drowning in my own drool and glanced over my notes. There was much that was irrelevant and some that was downright frightening, but one curious sentence piqued my interest: “virtual machines need virtual transistors”. That got me thinking… what if somebody took the concept of a virtual machine too far, and rather than translating one bytecode into another attempted instead to simulate the flow of electricity through transistors and logic gates that typically takes place in a CPU? 

An hour later the first VirtualTransistor came into being. It was simple: a class with a single bool that determined whether the transistor “switch” was on or off. Unfortunately, the moment I tried to build an AND gate from it, I realized the flaw -- I needed some way to simulate the wiring between transistors and other digital components, or they would need to know too much about the inner workings of the components they used. What was the VirtualTransistor became the VirtualConnection, which either has electricity flowing through it or doesn’t, happily abstracting away current, voltage, power drain and propagation delay. Armed with the VirtualConnection, I needed a way to tell the transistor that “electricity” was flowing through it, and the VirtualComponent interface/abstract class, with its Update method came into being. By the end of that first day, I had a new working and exhaustively tested transistor, an AND gate, an OR gate, and a backronym: VICE, the Virtual Integrated Circuit Engine. 

I was happily consumed with VICE. I dusted off my old digital electronics and CPU organization textbooks and spent every spare moment coding or reviewing schematics and function. My goal was to build a Turing complete VirtualCPU, complete with instruction set, ALU, FPU, and VirtualRAM, entirely from VirtualConnections and (ultimately, through Composition) VirtualTransistors. Unfortunately, time constraints made that impossible. I did manage to get full 32-bit integer addition, subtraction, and multiplication, all in 15 days. All things considered, I’m rather proud of how far I got. 

Ultimately, I am most proud of the fact that VICE is, if I do say so myself, rather elegantly architected. Every class is very well documented, explaining the purpose and in most cases providing links to online example schematics that explain how the component it simulates is wired. I am also quite amused by how wasteful VICE is: what would take only one line of code and in most cases a single CPU cycle, takes hundreds to thousands of times more time. And yet, the result is fairly performant. 

Finally, I am saddened by the fact that I never managed to get around to floating point calculations. As a result, the division function of the calculator does not utilize VICE, and the inputs for all operations are cast from a float to an int before being fed into the VICE. The calculator passes the unit tests, however, and is always correct if it operates on whole number inputs. I hope that you will look past this glowing error when judging my submission. 
