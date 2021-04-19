#ifndef G_TIMER
#define G_TIMER

#include <Windows.h>

class G_Timer {
private:
	LARGE_INTEGER timerFreq;
	LARGE_INTEGER timeNow;
	LARGE_INTEGER timePrevious;

	int Requested_FPS, frameToUpdate;
	float intervalsPerFrame, intervalsSinceLastUpdate;

public:
	G_Timer();
	~G_Timer();
	int framesToUpdate();

	void init(int);
};

#endif // !G_TIMER