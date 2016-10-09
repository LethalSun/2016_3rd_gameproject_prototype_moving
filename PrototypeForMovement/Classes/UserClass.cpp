#include "pch.h"
#include "UserClass.h"



UserClass::UserClass()
	:m_checkCurrentDirection(1)
{
	
}


UserClass::~UserClass()
{
}

void UserClass::SetDirection(const unsigned int &keyboardDirection)
{
	m_checkCurrentDirection = keyboardDirection;
}

void UserClass::MoveUserClass()
{
	//m_archBishop;
}


/*
if (keyboardDirection[UP] == true
&& keyboardDirection[DOWN] == false
&& keyboardDirection[LEFT] == false
&& keyboardDirection[RIGHT] == false)
{
m_checkCurrentDirection[] = { true, false, false, false, false, false, false, false };
m_checkCurrentDirection[UP_1200] = true;
}
else if (keyboardDirection[UP] == false
&& keyboardDirection[DOWN] == true
&& keyboardDirection[LEFT] == false
&& keyboardDirection[RIGHT] == false)
{
m_checkCurrentDirection[DOWN_0600] = true;
}
else if (keyboardDirection[UP] == false
&& keyboardDirection[DOWN] == false
&& keyboardDirection[LEFT] == true
&& keyboardDirection[RIGHT] == false)
{
m_checkCurrentDirection[RIGHT_0900] = true;
}
else if (keyboardDirection[UP] == false
&& keyboardDirection[DOWN] == false
&& keyboardDirection[LEFT] == false
&& keyboardDirection[RIGHT] == true)
{
m_checkCurrentDirection[RIGHT_0300] = true;
}
else if (keyboardDirection[UP] == false
&& keyboardDirection[DOWN] == true
&& keyboardDirection[LEFT] == false
&& keyboardDirection[RIGHT] == false)
{
m_checkCurrentDirection[DOWN_0600] = true;
}
else if (keyboardDirection[UP] == false
&& keyboardDirection[DOWN] == true
&& keyboardDirection[LEFT] == false
&& keyboardDirection[RIGHT] == false)
{
m_checkCurrentDirection[DOWN_0600] = true;
}
else if (keyboardDirection[UP] == false
&& keyboardDirection[DOWN] == true
&& keyboardDirection[LEFT] == false
&& keyboardDirection[RIGHT] == false)
{
m_checkCurrentDirection[DOWN_0600] = true;
}
else if (keyboardDirection[UP] == false
&& keyboardDirection[DOWN] == true
&& keyboardDirection[LEFT] == false
&& keyboardDirection[RIGHT] == false)
{
m_checkCurrentDirection[DOWN_0600] = true;
}
*/