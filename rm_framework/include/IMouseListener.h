#pragma once

//this is an abstract class - due to the =0 on the MouseMoved function
//the compiler will not allow you to create an instance of it
//this class acts as an Interface, defining the set of functions that all
//mouseListener sub classes must implement

class IMouseListener
{
public:
	IMouseListener(void);
	~IMouseListener(void);
	virtual void MouseMoved(float x_, float y_)=0;
};

