#include <iostream>
#include "tv.h"

int main(void)
{
	using std::cout;
	using std::endl;
	Tv s42;
	cout << "Initial settings for 42\" TV:\n";
	s42.settings();
	s42.onoff();
	s42.chanup();
	cout << "\nAdjusted settings for 42\" TV:\n";
	s42.settings();

	Remote grey;
	grey.set_chan(s42, 10);
	grey.volup(s42);
	grey.volup(s42);
	cout << "\n42\" settings after using remote:\n";
	s42.settings();

	Tv s58(Tv::On);
	s58.set_mode();
	grey.set_chan(s58, 28);
	cout << "\n58\" settings: \n";
	s58.settings();

	cout << "\nthe remote control mode is: "; 		
	grey.display_control_mode();
	s58.toggle_control_mode(grey);
	cout << "after toggle, the remote control mode is: ";
	grey.display_control_mode();

	return 0;
}
