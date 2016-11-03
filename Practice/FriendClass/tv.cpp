#include <iostream>
#include "tv.h"

bool Tv::volup()
{
	if(volume < MaxVal) {
		volume++;
		return true;
	} else {
		return false;
	}
}

bool Tv::voldown()
{
	if(volume > MinVal) {
		volume--;
		return true;
	} else {
		return false;
	}
}

void Tv::chanup()
{
	if(channel < maxchannel) {
		channel++;
	} else {
		channel = maxchannel;
	}
}

void Tv::settings() const
{
	using std::cout;
	using std::endl;

	cout << "TV is " << (state == Off ? "Off" : "On") << endl;
	if(state == On) {
		cout << "Volue setting = " << volume << endl;
		cout << "Channel setting = " << channel << endl;
		cout << "Mode = " << (mode == Antenna ? "antenna" : "cable") << endl;
		cout << "Input = " << (input == TV ? "TV" : "DVD") << endl;
	}
}

void Tv::toggle_control_mode(Remote & r)
{
	if(state == On) {
		r.control_mode = (r.control_mode == Remote::Normal ? Remote::Interactive : Remote::Normal);
	}
}

void Remote::display_control_mode()
{
	using std::cout;
	using std::endl;
	cout << "the control mode is : " << (control_mode == Normal ? "Normal" : "Interactive") << endl;
}
