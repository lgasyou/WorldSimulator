#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H


class TimeManager {
public:
	static TimeManager &instance();

    void setDeltaTime(double deltaTime) { deltaTime_ = deltaTime; }
    const double deltaTime() { return deltaTime_; }

	void increaseTime() { currentTime_ += frequence_; }
    const double currentTime() { return currentTime_; }

	void setFrequence(double frequence) { frequence_ = frequence; }
	const double frequence() { return frequence_; }

private:
	TimeManager() { }
	~TimeManager() { }
	TimeManager(const TimeManager &) = delete;
	TimeManager &operator=(const TimeManager &) = delete;

    static double deltaTime_;
    static double currentTime_;
	static double frequence_;
};

#endif // TIMEMANAGER_H