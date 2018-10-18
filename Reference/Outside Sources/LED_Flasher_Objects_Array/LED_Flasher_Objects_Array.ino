/******************************************
	PURPOSE:	C++ Class example  for Arduino
	Created by      Rudy Schlaf
	DATE:		12/2013
*******************************************/
//classes are 'blueprints' that can be used to define a number of identical 'objects'
//here we define a class for Arduino digital pins
//classes have 'members' which are the variables and functions that make up a class
//these members can be 'public' (i.e. accessible from outside the class), or 'private' (i.e. only accessible from the inside of the class)
//it is best practice to make all variables 'private' and only make functions 'public', with which we can access the variables from the outside. This guarantees that the variables are always accessed in a way that is intended.

//******************************************************************************************************************************************************
//class definition (this is a 'pre-declaration'. It tells the compiler about the existence of the 'members' (i.e. functions ('methods') and variables ('properties')) of the class
//******************************************************************************************************************************************************

class DigitalPin
{
  public://access specifier - this tells whether the 'members' are visible from the outside ('public") or only from the inside ('private')
    /*
    This is the 'constructor', which is automatically called whenever a new object of this class is created, allowing the class to initialize member variables or allocate storage.
    This constructor function is declared just like a regular member function, but with a name that matches the class name and without any return type; not even void.
    */
    DigitalPin(int pin);
    //these are the public class 'members'. The actual code for these members is given below...here we just tell the compiler about their existence, and what values are being returned
    void begin();
    void on();
    void off();
    bool status();
  private://these class members can only be used from within the class, i.e. they cannot be directly accessed from the outside. It is good practice to make all variables ('properties') private
          //and access them via public functions. That way they cannot be accidentally be changed via buggy code. This example only shows 'properties', but there could also be private 'methods'
    int _pin;
    bool _status;
};


//******************************************************************************************************************************************************
//'member' definitions: (here we define the actual c++ code and memory allocation of the members)
//******************************************************************************************************************************************************

DigitalPin::DigitalPin(int pin) //this is the constructor
{
  _pin = pin; //here we store the pin number in the private variable _pin.
}

void DigitalPin::begin() //this initializes the pin
{
  pinMode(_pin, OUTPUT);
}

void DigitalPin::on() //this turns the pin on
{
  digitalWrite(_pin, HIGH);
  _status=1; //set the status property
}

void DigitalPin::off() //this turns the pin off
{
  digitalWrite(_pin, LOW);
  _status=0; //set the status property
}

bool DigitalPin::status() //this returns the current status of the pin.
//It could be used by some other component of the sketch that needs to know whether the pin is on or off.
//This is an example for a method for 'communication' between or with objects.
{
    return _status;
}

//******************************************************************************************************************************************************
//Main Arduino sketch
//******************************************************************************************************************************************************

DigitalPin LED1(10); //create ('instantiate') a DigitalPin object called "LED1" that uses pin 10.
DigitalPin LED2(11); //create ('instantiate') a DigitalPin object called "LED2" that uses pin 11.
DigitalPin array[2] = {LED1, LED2};//define an array containing the objects. This enables accessing the objects with a variable in a loop
void setup() 
{                
 array[0].begin(); //call the begin 'method' to define the pinmode 
//notice the name of the function: "LED1" is the DigitalPin object name, and "begin()" refers to the 'class member' named "DigitalPin.begin()" as defined above.
 array[1].begin(); //do the same for LED2
}

void loop() 
{
  
  for (int i = 0; i<2; i++){
  array[i].on();
  delay(500);
  array[i].off();
  delay(500);
  }
}


