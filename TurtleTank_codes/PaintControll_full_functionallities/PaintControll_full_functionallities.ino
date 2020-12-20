//paintcontroll with ros and the functions
// version 2.1

// ros lib
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int8.h>
//servo lib
#include <Servo.h>

// pin
int valve_pin = 4;
int pump_pin = 3;

//variables
bool paint_guard_state = false;
bool valve_state = false;
bool pump_state = false;

// servo current possition and delay be tween every possition when moving
Servo pg_servo;
int pg_pos = 180;
int servo_delay = 6;


// delays in micro seconds, we also tried it with nano seconds both didnt work as wanted.
int guard2pump_delay = 650000;// 650;
int pump2valve_delay = 250000; //250;               //delay from the pump opening until the valve opening
int valve2pump_delay = 500000;// 500;
int pump2guard_delay = 2000000;  //2000;
// * we should to it different use tyiming instead.


//variables for the Main
int led = 13;                   //  status led
bool led_state = true;
char input_string;
String start_str, input_str, variable_str;



//ros
ros::NodeHandle node_handle;

//publisher
std_msgs::String valve_status_msg;
std_msgs::String pump_status_msg;
std_msgs::String paint_guard_status_msg;

//subs
std_msgs::Int8 valve_msg;
std_msgs::Int8 pump_msg;
std_msgs::Int8 paint_guard_msg;
std_msgs::Int8 paint_action_msg;
std_msgs::Int8 turtleTank_msg;

// ------------------------ Functions for controlling the pump, valve and paint_guard ------------------------
void servo_func(bool pos_bool) {
  int pos;
  if (pos_bool == true) {
    Serial.println("s-HIGH");
    //add error handeling
    for (pos = pg_pos; pos > 0; pos -= 1) {       // goes from 180 degrees to 0 degrees
      pg_servo.write(pos);                      // tell servo to go to position in variable 'pos'
      delay(servo_delay);                       // waits 15ms for the servo to reach the position
      Serial.print(pos);
      Serial.print(" ,");
    }
  }

  else {
    Serial.println("s-low");
    //add error handeling
    for (pos = pg_pos; pos < 180; pos += 1) {       // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      pg_servo.write(pos);                      // tell servo to go to position in variable 'pos'
      delay(servo_delay);                       // waits 15ms for the servo to reach the position
      Serial.print(pos);
      Serial.print(" ,");
    }
  }

  pg_pos = pos;
  Serial.print(" : ");
  Serial.println(pg_pos);

  paint_guard_state == pos_bool;
}

void set_pump_state(bool state) {                   // start(true)/stop(false the pump
  if (pump_state == state) {
    Serial.print("Error: 01 [Pump state was already set to: ");
    Serial.println(state);
    return;
  }
  else {
    if (state == true) {
      Serial.println("true");
      // digitalWrite(8, HIGH);
      digitalWrite(pump_pin, HIGH);
    }
    else {
      // digitalWrite(8, LOW);
      digitalWrite(pump_pin, LOW);
      Serial.println("false");
    }
    pump_state = state;
    Serial.print("Pump is now set to: " );
    Serial.println(state);
  }
}

bool get_pump_state() {                             // read the state of the pump
  Serial.print("pump is: ");
  Serial.println(pump_state);
  return pump_state;
}

void set_valve_state(bool state) {                  // open(true)/close(false) valve
  if (valve_state == state) {
    Serial.print("Error: 02 [Valve state was already set to: " );
    Serial.println(state);
    return;
  }
  if (state == true) {
    digitalWrite(valve_pin, HIGH);
  }
  else {
    digitalWrite(valve_pin, LOW);
  }
  valve_state = state;
  Serial.print("Valve is now set to: ");
  Serial.println(state);
}

bool get_valve_state() {                            // read the state of the valve
  Serial.print("valve is: ");
  Serial.println(valve_state);
  return valve_state;
}

void set_paint_guard_state(bool state) {            // move paint gueard up(false)/down(true)
  if (paint_guard_state == state) {
    Serial.print("Error: 03 [Paint_guard state was already set to: ");
    Serial.println(state);
    return;
  }

  servo_func(state);
  paint_guard_state = state;
  Serial.print("Paint_guard is now set to: ");
  Serial.println(state);
}

bool get_paint_guard_state() {                      // read state of paint guard
  Serial.print("paint_guard is: ");
  Serial.println(paint_guard_state);
  return paint_guard_state;
}

void start_painting() {                             // initial start painting frequence
  Serial.println("prepare to start painting");
  set_paint_guard_state(true);
  delayMicroseconds(guard2pump_delay);
  set_pump_state(true);
  delayMicroseconds(pump2valve_delay);
  set_valve_state(true);
  Serial.println("painting is ongoing");
}

void stop_painting() {                              // inital stop painting frequence

  Serial.println("prepare to stop painting");
  set_valve_state(false);
  delayMicroseconds(valve2pump_delay);
  set_pump_state(false);
  delayMicroseconds(pump2guard_delay);
  set_paint_guard_state(false);
  Serial.println("painting is stopped\n");

}



void paint_cycle(int distance) {                    // start paint frequence, wait for x ms, stop painting
  float distance_sec = distance / 1000;
  Serial.print("Painting for: ");
  Serial.print( distance_sec );
  Serial.println("seconds");
  start_painting();
  Serial.println("painting: ");
  delay(distance * 1000);
  Serial.println("DONE");
  stop_painting();
}
//------------------------------------------------------------------------

//------------------------ subs function ------------------------
void valve_subscriberCallback(const std_msgs::Int8& valve_msg) {
  if (valve_msg.data  == 1) {
    node_handle.loginfo("valve: 1");
    set_valve_state(true);
  }
  else {
    node_handle.loginfo("valve: 0");
    set_valve_state(false);
  }
}
void pump_subscriberCallback(const std_msgs::Int8& pump_msg) {
  if (pump_msg.data  == 1) {
    node_handle.loginfo("pump: 1");
    set_pump_state(true);
  }
  else {
    node_handle.loginfo("pump: 0");
    set_pump_state(false);
  }
}
void paint_guard_subscriberCallback(const std_msgs::Int8& paint_guard_msg) {
  if (paint_guard_msg.data  == 1) {
    node_handle.loginfo("paint_guard: 1");
    set_paint_guard_state(true);
  }
  else {
    node_handle.loginfo("paint_guard: 0");
    set_paint_guard_state(false);
  }
}
void paint_action_subscriberCallback(const std_msgs::Int8&paint_action_msg) {
  if (paint_action_msg.data  == 1) {
    node_handle.loginfo("paint_action: 1");
    start_painting();
  }
  else {
    node_handle.loginfo("paint_action: 0");
    stop_painting();
  }
  
    node_handle.loginfo("done");
}


//------------------------------------------------------------------------

// pubs
ros::Publisher valve_publisher("valve_status", &valve_status_msg);
ros::Publisher pump_publisher("pump_status", &pump_status_msg);
ros::Publisher paint_guard_publisher("paint_guard_status", &paint_guard_status_msg);

// SUBS
ros::Subscriber<std_msgs::Int8> valve_subscriber("valve", &valve_subscriberCallback);
ros::Subscriber<std_msgs::Int8> pump_subscriber("pump", &pump_subscriberCallback);
ros::Subscriber<std_msgs::Int8> paint_guard_subscriber("paint_guard", &paint_guard_subscriberCallback);
ros::Subscriber<std_msgs::Int8> paint_action_subscriber("paint_action", &paint_action_subscriberCallback);



void setup()
{
  Serial.begin(57600);
  Serial.print("Start_setup: ");

  pinMode(valve_pin, OUTPUT);
  pinMode(pump_pin, OUTPUT);
  pg_servo.attach(2);
  pg_servo.write(180);
  pinMode(led, OUTPUT);


  // ros
  node_handle.initNode();
  // pups
  node_handle.advertise(valve_publisher);
  node_handle.advertise(pump_publisher);
  node_handle.advertise(paint_guard_publisher);


  // subs
  node_handle.subscribe(valve_subscriber);
  node_handle.subscribe(pump_subscriber);
  node_handle.subscribe(paint_guard_subscriber);
  node_handle.subscribe(paint_action_subscriber);
  node_handle.loginfo("main");

  Serial.println("DONE");
  digitalWrite(led, HIGH);
}





void loop()
{
  // valve
  if (valve_state == true) {
    valve_status_msg.data = "valve: open";
    Serial.print("valve_open, ");

  }
  else {
    valve_status_msg.data = "valve: closed";
    Serial.print("valve_closed, ");
  }

  // pump
  if (pump_state == true) {
    pump_status_msg.data = "pump: on";
    Serial.print("pump on, ");
  }
  else {
    pump_status_msg.data = "pump: off";
    Serial.print("pump off, ");
  }

  //paint_guard
  if (paint_guard_state == true) {
    paint_guard_status_msg.data = "paint_guard: down";
    Serial.println("pg down, ");
  }
  else {
    paint_guard_status_msg.data = "paint_guard:  up";
    Serial.println("pg up ");
  }


  valve_publisher.publish( &valve_status_msg );
  pump_publisher.publish( &pump_status_msg );
  paint_guard_publisher.publish( &paint_guard_status_msg );

  node_handle.spinOnce();

  delay(10);

}
