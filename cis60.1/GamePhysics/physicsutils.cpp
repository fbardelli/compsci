#include "physicsutils.h"


/**
  Given two rectangles returns true if they intersect

  @param p QRectF representing first Rectangle
  @param o QRectF representing second Rectangle

*/
bool PhysicsUtils::objectsCollide(QRectF p, QRectF o){
    int pLeft = p.x();
    int oLeft = o.x();
    int pRight = p.x() + p.width();
    int oRight = o.x() + o.width();
    int pTop   = p.y();
    int oTop   = o.y();
    int pBottom = p.y() + p.height();
    int oBottom = o.y() + o.height();
    // is player fully above obstacle?
    if (pBottom < oTop) return false;
    // is player fully below obstacle?
    if (pTop > oBottom) return false;
    //Is player to the right of obstacle?
    if (pRight < oLeft) return false;
    //Is player to the left of obstacle?
    if (pLeft > oRight) return false;
    //otherwise player collides with obstacle.
    return true;
}

/**
  Given two rectangles moves the first to the edge of the second based on the direction of movement

  @param p QRectF representing first Rectangle
  @param o QRectF representing second Rectangle
  @param dir Direction the first rectangle is moving in

*/
void PhysicsUtils::moveToEdge(QRectF &p, QRectF o, Direction dir){
    int pHeight = p.height();
    int pWidth = p.width();
    if(dir == Right){
        p.moveTo( (o.x()-pWidth-1),p.y());
    }else if (dir == Left){
        p.moveTo(o.x()+pWidth+1,p.y());
    }else if (dir == Down){
        p.moveTo(p.x(), (o.y()-pHeight-1) );
    }else if (dir == Up){
        p.moveTo(p.x(),o.y()+pHeight+1);
    }
}

/**
  Given a direction returns the opposite direction

  @param dir original Direction
  @returns new Direction

*/
Direction PhysicsUtils::reverseDirection(Direction dir){
    Direction newDirection;
    if(dir == Right){
        newDirection = Left;
    }else if (dir == Left){
        newDirection = Right;
    }else if (dir == Down){
        newDirection = Up;
    }else if (dir == Up){
        newDirection = Down;
    }
    return newDirection;
}

/**
  Given a 2D Vector returns the Vector perpendicular to it

  @param vector Original Vector
  @returns Normal Vector

*/
QVector2D PhysicsUtils::normalVector (QVector2D vector){
   return QVector2D(-vector.y(),vector.x());
}

/**
  Determine projection of initial vector along the direction vector

  @param vector Initial Vector
  @param directionVector
  @returns New component vector
*/
QVector2D PhysicsUtils::componentVector(QVector2D vector, QVector2D directionVector){
    QVector2D v  = directionVector.normalized();
    return ( v * component(vector, directionVector));
}

/**
  Determine component value of initial vector along the direction vector

  @param vector Initial Vector
  @param directionVector
  @returns component
*/
double PhysicsUtils::component (QVector2D vector, QVector2D directionVector){
    double alpha = atan2(directionVector.y(), directionVector.x());
    double theta = atan2(vector.y(),vector.x());
    double mag   = magnitude(vector);
    double a     = mag*cos(theta-alpha);
    return a;
}

/**
  Determine magnitude of given vector.  Equivlent to the hypotenuse of a triangle made up of the x and y components

  @param vector a 2D Vector
  @returns magnitude of the vector
*/
double PhysicsUtils::magnitude(QVector2D v){
  double s = 0;
  s+= v.x()*v.x();
  s+= v.y()*v.y();
  return sqrt(s);
}

/**
  Returns new direction of an object impacting another object at a given tangental vector

  @param direction directional velocity of the original object
  @param normal normal vector of the impact point
  @returns new direction of the original object
*/
QVector2D PhysicsUtils::resolveFixedCollision(QVector2D direction, QVector2D normal){
    QVector2D c  = componentVector(direction,normal);
    return QVector2D(direction - 2*c);
}

/*
function component ( vector, directionVector)
  set alpha to atan(directionVector [2] , directionVector [1 ] )
  set theta to atan(vector[ 2] ,vector[1 ] )
  set mag to magnitude( vector)
  set a to mag*cos( theta-alpha)
  return a
end function

function componentVector( vector, directionVector)
  set v to norm(directionVector)
  return component( vector, directionVector) *v
end function

function normalVector (vector)
return vector(- vector[ 2] , vector[ 1 ])
end function

function resolveFixedCollision(obj , n)
  set c to componentVector(obj. velocity, n)
  set obj. velocity to v- 2*c
end function

function intersectionPoint(a, b, c, d)
    set tc1 to b[1 ] - a[1 ]
    set tc2 to b[2] - a[2]
    set sc1 to c[1 ] - d[1 ]
    set sc2 to c[2] - s[2]
    set con1 to c[ 1 ] - a[1 ]
    set con2 to c[ 2] - a[2]
    set det to (tc2*sc1 -tc1*sc2)
    if det=0 then return " no unique solution"
    set con to tc2*con1 -tc1*con2
    set s to con/det
    return c+s*(d-c)
end function

function resolveCollisionFree1 (obj 1 , obj 2, n)
    set r to obj1 . mass/obj 2. mass
    set un to componentVector(obj1 . velocity, n)
    set ut to obj1 . velocity-un
    set vn to un*(r- 1 )/(r+1)
    set wn to un*2*r/ (r+1 )
    set obj1 . velocity to ut+vn
    set obj2. velocity to wn
end function

function resolveCollisionFree (obj 1 , obj 2, n)
    set r to obj1 . mass/obj 2. mass
    set u to obj1 . velocity-obj 2.velocity
    set un to componentVector(u,n)
    set ut to u-un
    set vn to un*(r- 1 )/(r+1)
    set wn to un*2*r/ (r+1 )
    set obj1 . velocity to ut+vn+u2
    set obj2. velocity to wn+u2
end function

function resolveCollisionEqualMass ( obj 1 , obj 2, n)
    set u to obj1 . velocity-obj 2.velocity
    set un to componentVector(u,n)
    set ut to u-un
    set obj1 . velocity to ut+obj 2. velocity
    set obj2. velocity to un+obj 2. velocity
end function

function resolveInelasticCollisionFree (obj 1 , obj 2, n)
    set r to obj1 . mass/obj 2. mass
    set u to obj1 . velocity-obj 2.velocity
    set e to obj1 . efficiency*obj2. efficiency
    set un to component ( u,n)
    set ut to mag(u- un*n)
    set sq to r*r*un*un-( r+1 ) *( (r-e) *un*un+(1 - e) *ut*ut))
    set vn to n*(sqrt(sq) - r*un) /(r+1 )
    set wn to r*(n*un-vn)
    set obj1 . velocity to ut+vn+ obj 2. velocity
    set obj2. velocity to wn+ obj2. velocity
end function

function resolveInelasticCollisionFixed ( obj 1 , obj 2, n)
    set e to obj1 . efficiency*obj2. efficiency
    set un to component ( obj 1 . velocity, n)
    set ut to mag(obj 1. velocity -un*n)
    set sq to  (e*un*un+( e-1 ) *ut*ut) )
    set vn to n*sqrt( sq)
    set obj1 . velocity to ut+vn
end function

function addVectors (v1, v2)
   // assume v1 and v2 are arrays of the same length
   set newVector to an empty array
   repeat for i=1 to the length of v1
      append v1[i]+v2[i] to newVector
   end repeat
   return newVector
end function

function scaleVector (v, s)
   repeat for i=1 to the length of v
      multiply v[i] by s
   end repeat
   return v
end function

function magnitude (v)
   set s to 0
   repeat with i=1 to the length of v
      add v[i]*v[i] to s
   end repeat
   return sqrt(s)
end function

function norm (v)
   set m to magnitude(v)
   if m=0 then return "error" // you can't normalize a zero vector
   return scaleVector(v,1/m)
end function

*/
