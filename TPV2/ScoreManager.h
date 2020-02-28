#pragma once

#include "Component.h"

class ScoreManager: public Component {
public:
	ScoreManager();
	virtual ~ScoreManager();

	bool isRunning() const {
		return running_;
	}
	void setRunning(bool running) {
		running_ = running;
	}
	bool isFinished() const {
		return finished_;
	}
	void setFinished(bool fin) {
		finished_ = fin;
	}
	void setScore(int i) {
		score_ = i;
	}
	void addScore(int i) {
		score_ += i;
	}
	int getScore() const {
		return score_;
	}

private:
	bool running_;
	bool finished_;
	int score_;
}
