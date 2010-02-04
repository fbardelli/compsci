/* $Id$ */
// Frank Bardelli
// Advanced C++ Programming (Section WQ6)
// Assignment 2
// September 16, 2009
//---------- SOURCE CODE BEGINS HERE ----------
// include C and C++ headers
#include <iostream>
#include <stdlib.h>
using namespace std;

char * env_debug;
int DEBUG = 0;

class Point {
  public:
    void print() const;
    void set( int p1, int p2 );
    int getX();
    int getY();
    bool equals(Point p);
  private:
    int x, y;
};

/**
 * void Point::print()
 * displays (x,y) coordinates
 * of the point object
 */
void Point::print() const {
  cout << "(" << x << "," << y << ")";
}

/**
 * void Point::set( int xx, int yy )
 * Set the x and y coordinates
 * of the point object
 */
void Point::set( int xx, int yy ){
  x = xx;
  y = yy;
}

/**
 * bool Point::equals(Point p)
 * returns true if the point supplied has the same
 * as the current point object
 */
bool Point::equals(Point p){
  return (x == p.getX() && y == p.getY());
}

/**
 * int Point::getX()
 * returns the x coordinate
 * of the point object
 */
int Point::getX(){
  return x;
}

/**
 * int Point::getY()
 * returns the y coordinate
 * of the point object
 */
int Point::getY(){
  return y;
}
 


class PatrolCar {
  public:
    enum orientation_type{NORTH,EAST,SOUTH,WEST};
    void init();
    void print();
    void setOrientation(orientation_type o);
    bool forward();
    void turnCW();
    void turnAntiCW();
    bool eastEnd();
    bool westEnd();
    bool northEnd();
    bool southEnd();
    bool zag();
    bool zig();
    string orientationToString(int orientation);
    Point getLocation();
  private:
    Point location;
    int orientation;
};

/**
 * void PatrolCar::init()
 * initializes a patrol car object setting
 * location to 0,0 and direction to East
 */
void PatrolCar::init(){
  location.set(0,0);
  setOrientation(EAST);      
}

/**
 * void PatrolCar::print()
 * displays the current location and
 * direction of the patrol car
 */
void PatrolCar::print(){
  cout << "Patrol: I am at ";
  location.print();
  cout << " I am facing " << orientationToString(orientation) <<endl;
}

/**
 * void PatrolCar::setOrientation(orientation_type o)
 * sets the direction of the patrol car
 */
void PatrolCar::setOrientation(orientation_type o){
  orientation = o;
}


/*
 * bool PatrolCar::forward()
 * Attempts to move one unit in the direction
 * the patrol car is facing.  Returns false if the
 * patrol car could not move forward.
 */
bool PatrolCar::forward(){
  switch(orientation){
    case EAST:
      {
         if(! eastEnd()){
           location.set(location.getX()+1, location.getY());
           return true;
         }else{
           if (DEBUG){ cout << "Hit East Wall\n";}
           return false;
         }
      }
      break;
    case WEST:
      {
        if(! westEnd()){
          location.set(location.getX()-1, location.getY());
          return true;
        }else{
          if (DEBUG){ cout << "Hit West Wall\n";}
          return false;
        }
      }
      break;
    case SOUTH:
      {
         if(! southEnd()){
           location.set(location.getX(), location.getY()-1);
           return true;
         }else{
           if (DEBUG){ cout << "Hit South Wall\n";}
           return false;
         }
      }
      break;
    case NORTH:
      {
         if(! northEnd()){
           location.set(location.getX(), location.getY()+1);
           return true;
         }else{
           if (DEBUG){ cout << "Hit North Wall\n";}
           return false;
         }
      }
      break;
  }
}

/*
 * void PatrolCar::turnCW(){
 * Changes orientation of the car turning 90 degrees clockwise
 */
void PatrolCar::turnCW(){
   /*orientation_type is in clockwise order
   / so increment orientation by one       
   / flipping around to 0 after 3*/
   orientation = (orientation + 1) % 4;
}

/*
 * void PatrolCar::turnAntiCW(){
 * Changes orientation of the car turning 90 degrees anti clockwise
 */
void PatrolCar::turnAntiCW(){
   //For our compass, Anti Clockwise is the same as 3 clockwise turns
   orientation = (orientation + 3) % 4;
}

/*
 * bool PatrolCar::eastEnd()
 * returns true if patrol car is at the east edge of the world
 */
bool PatrolCar::eastEnd(){
  return ( location.getX() == 9 );
}


/*
 * bool PatrolCar::westEnd()
 * returns true if patrol car is at the west edge of the world
 */
bool PatrolCar::westEnd(){
  return ( location.getX() == 0 );
}

/*
 * bool PatrolCar::northEnd()
 * returns true if patrol car is at the north edge of the world
 */
bool PatrolCar::northEnd(){
  return ( location.getY() == 9 );
}

/*
 * bool PatrolCar::southEnd()
 * returns true if patrol car is at the south edge of the world
 */
bool PatrolCar::southEnd(){
  return ( location.getY() == 0 );
}

/*
 * bool PatrolCar::zag()
 * turns clockwise moves forward, turns clockwise again
 * returns true if patrol car moved forward
 */
bool PatrolCar::zag(){
   turnCW();
   bool moved_forward = forward();
   turnCW();
   return moved_forward;
}

/*
 * bool PatrolCar::zig()
 * turns anti clockwise moves forward, turns anti clockwise again
 * returns true if patrol car moved forward
 */
bool PatrolCar::zig(){
   turnAntiCW();
   bool moved_forward = forward();
   turnAntiCW();
   return moved_forward;
}

/*
 * string PatrolCar::orientationToString(int orientation)
 * returns human readable orientation
 */
string PatrolCar::orientationToString(int orientation){
   static const string orientationDesc[4] = {"North","East","South","West"};
   return orientationDesc[orientation];
}

/*
 * Point PatrolCar::getLocation()
 * returns point object representing patrol car's location
 */
Point PatrolCar::getLocation(){
  return location;
}
 
class World {
  public:
    void set(int i, int x, int y);
    void print() const; 
    int checkForSuspect(Point p);
  private:
    enum{ NUM_SUSPECTS = 3 };
    Point suspects[NUM_SUSPECTS];

};

/*
 * void World::set(int i, int x, int y)
 * places a suspect at the specified x,y location
 */

void World::set(int i, int x, int y){

  if ( x < 0 || x >9){
    cout << "invalid x coordinate: " << x << " for suspect#" << i << endl;
    exit(1);
  }
  if ( y < 0 || y >9){
    cout << "invalid y coordinate: " << y << " for suspect#" << i << endl;
    exit(1);
  }
  suspects[i];
  suspects[i].set(x,y);
}

/**
 * void World::print()
 * displays the current location of all
 * suspects in the world
 */
void World::print() const {
  for( int i = 0; i < NUM_SUSPECTS; i++){
    cout << "World: Suspect#" << i << " is at ";
    suspects[i].print();
    cout << endl;
  }
}

/**
 * int World::checkForSuspect(Point p)
 * given a point objects prints out a message if there
 * are any suspects at that point in the world
 * returns number of suspects found.
 */
int World::checkForSuspect(Point p){
   int found = 0;
   //loop through suspects to see if any suspect is at the coordinates entered
   for (int i = 0; i < NUM_SUSPECTS; i++){
     if(suspects[i].equals(p)){
        ++found;
        cout << "Found suspect " << i+1 << " at "; 
        suspects[i].print();
        cout << endl;
     }
   }
   return found;
}
 


int main(int argc, char * argv[]){
  //See if global DEBUG variable is set
  env_debug = getenv("DEBUG");
  if(env_debug != NULL){
    DEBUG = atoi(env_debug);
  }
  if (argc != 7){
    cout << "This Program requires exactly 6 coordinates\n";
    exit(1);
  }
  
  // initialize World and place suspects in the world
  World w;
  for (int i = 0; i < 3; i++ ){
    int suspect_x = atoi(argv[(i*2)+1]);
    int suspect_y = atoi(argv[(i*2)+2]);
    w.set(i,suspect_x,suspect_y);
  }
  
  if ( DEBUG ) {
    w.print();
  }
  
  //Initialize patrol car
  PatrolCar pc;
  pc.init();
  pc.print();
  bool went_forward, zigzagged;
  int moves = 0;
  int suspects_found = 0;
  
  //Traverse world
  //at the end of the run we will be on the NW edge
  while (  ! (pc.westEnd() && pc.northEnd()) ) {
    zigzagged = false;
    suspects_found = suspects_found + w.checkForSuspect(pc.getLocation());
    //If we find all 3 suspects we can stop
    if (suspects_found >= 3){
      break;
    }

    if (DEBUG){
      cout << "at: "; 
      pc.getLocation().print(); 
      cout << endl;
    }
    
    went_forward = pc.forward();
    // Check if we hit a wall
    if(! went_forward){
       //Check if it's the east or west wall
       if(pc.eastEnd()){
         zigzagged = pc.zig();
       }else if(pc.westEnd()){
         zigzagged = pc.zag();
       }
    }
    if (went_forward || zigzagged){
       moves++;
    }
  }

  if (DEBUG){
    cout << "at: "; 
    pc.getLocation().print(); 
    cout << endl;
  }
  
  // If we got all the way to the end 
  // see if a suspect is in the final position
  if(pc.westEnd() && pc.northEnd()){
    suspects_found += w.checkForSuspect(pc.getLocation());
  }
  
  //Final Report
  cout << "finished at: ";
  pc.getLocation().print();
  cout << "\nFound " << suspects_found << " suspects in " << moves << " moves.\n";
  return 0;
}
