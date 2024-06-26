#include "audio/audio.h"
#include "gui/gui.h"
#include <iostream>

int main() {
	AudioInput i;
	AudioProcess p;
	GUI g;
	int e;
	g.init();
	e=i.init(Pa_GetDefaultInputDevice());
	if (e!=NOERR) {
		std::cout << "cant init audio you fuk\n";
		switch (e) {
			case NODEVS:
				std::cout << "no devices found\n";
				return 1;
			case NODEV:
				std::cout << "cant open device\n";
				return 1;
			case NOSTART:
				std::cout << "cant start device\n";
				return 1;
			case NOGOOD:
				std::cout << "cant init portaudio\n";
				return 1;
			default:
				std::cout << Pa_GetErrorText(e) << '\n';
				return 1;
		}
	}
	while (g.isRunning()) {
		p.writeDataIn(i.getData());
		// p.integrate();
		g.writeOscData(p.alignWave(g.getTrigger(),g.getTraceSize(),0,0),i.getData(),i.getDataSize());
		// g.writeOscAuxData(p.getDataOut(),i.getDataSize());
		g.doFrame();
	}
	e=i.stop();
	std::cout << Pa_GetErrorText(e) << '\n';
	return ~(e==paNoError);
}