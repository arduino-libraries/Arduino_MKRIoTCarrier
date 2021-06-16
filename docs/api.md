# MKR IoT Carrier library - TEST in-progress

## Class1
    ### `method1()`
    #### Syntax

    ```
    servo.attach(pin) 
    servo.attach(pin, min, max)
    ```

    #### Parameters

    * _servo_: a variable of type `Servo`

    #### Example
    ```
    #include <Servo.h> 
    ```

    #### See also

    * [test1()](#test1)
    * [test2()](#test2)

## Class2

## Class3

## Buttons

### `getTouch()`

Attach the Servo variable to a pin. Note that in Arduino 0016 and earlier, the Servo library supports servos on only two pins: 9 and 10.

#### Syntax

```
servo.attach(pin) 
servo.attach(pin, min, max)
```

#### Parameters

* _servo_: a variable of type `Servo`
* _pin_: the number of the pin that the servo is attached to
* _min_ (optional): the pulse width, in microseconds, corresponding to the minimum (0 degree) angle on the servo (defaults to 544)
* _max_ (optional): the pulse width, in microseconds, corresponding to the maximum (180 degree) angle on the servo (defaults to 2400)

#### Example

```
#include <Servo.h> 

Servo myservo;

void setup() 
{ 
  myservo.attach(9);
} 

void loop() {} 
```

#### See also

* [test1()](#test1)
* [test2()](#test2)

### `Y()`

Writes a value to the servo, controlling the shaft accordingly. On a standard servo, this will set the angle of the shaft (in degrees), moving the shaft to that orientation. On a continuous rotation servo, this will set the speed of the servo (with 0 being full-speed in one direction, 180 being full speed in the other, and a value near 90 being no movement).

#### Syntax

```
servo.write(angle)
```

#### Parameters

* _servo_: a variable of type Servo
* _angle_: the value to write to the servo, from 0 to 180

#### Example

````
#include <Servo.h> 

Servo myservo;

void setup() 
{ 
  myservo.attach(9);
  myservo.write(90);  // set servo to mid-point
} 

void loop() {} 
````
#### See also

* [test1()](#test1)
* [test2()](#test2)

### `test1()`

Writes a value in microseconds (us) to the servo, controlling the shaft accordingly. On a standard servo, this will set the angle of the shaft. On standard servos a parameter value of 1000 is fully counter-clockwise, 2000 is fully clockwise, and 1500 is in the middle.

Note that some manufactures do not follow this standard very closely so that servos often respond to values between 700 and 2300. Feel free to increase these endpoints until the servo no longer continues to increase its range. Note however that attempting to drive a servo past its endpoints (often indicated by a growling sound) is a high-current state, and should be avoided.

Continuous-rotation servos will respond to the writeMicrosecond function in an analogous manner to the write function.

#### Syntax

````
servo.writeMicroseconds(us)
````

#### Parameters

* _servo_: a variable of type Servo
* _us_: the value of the parameter in microseconds (int)

#### Example

````
#include <Servo.h> 

Servo myservo;

void setup() 
{ 
  myservo.attach(9);
  myservo.writeMicroseconds(1500);  // set servo to mid-point
} 

void loop() {} 
````

#### See also

* [test2()](#test2)


### `test2()`

Read the current angle of the servo (the value passed to the last call to [write()](#write)).

#### Syntax

````
servo.read()
````

#### Parameters

* _servo_: a variable of type `Servo`

#### Returns

The angle of the servo, from 0 to 180 degrees.

#### See also

* [test2()](#test2)
