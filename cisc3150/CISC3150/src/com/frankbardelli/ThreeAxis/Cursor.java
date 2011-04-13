package com.frankbardelli.ThreeAxis;

public class Cursor{
	int x, y, z;
	
	public Cursor(int x, int y, int z){
		this.x = x;
		this.y = y;
		this.z = z;
	}
	
	public void moveRight(){
		this.x += 5;
	}
	
	public void moveLeft(){
		this.x -= 5;
	}

	public void moveUp(){
		this.y -= 5;
	}
	
	public void moveDown(){
		this.y += 5;
	}
	
	public void moveOut(){
		this.z += 5;
	}
	
	public void moveIn(){
		this.z -= 5;
	}

	public int getX() {
		return x;
	}
	public void setX(int x) {
		this.x = x;
	}
	public int getY() {
		return y;
	}
	public void setY(int y) {
		this.y = y;
	}
	public int getZ() {
		return z;
	}
	public void setZ(int z) {
		this.z = z;
	}
}
