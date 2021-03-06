#ifndef __SIMULATION__H_
#define __SIMULATION__H_

#include "RobotInformation.h"
#include "AbstractAlgorithm.h"
#include "House.h"
#include "Sensor.h"
#include "Configuration.h"

#include <memory>

class Simulation
{
	AbstractAlgorithm*	_algo = nullptr;
	string				_algoName;
	House				_house;
	Sensor				_sensor;
	RobotInformation	_robot;
	Configuration		_config;
	Direction			_prevStep = Direction::Stay;
	
	int					_montageCounter = 0;
	int					_montageFailedCounter = 0;
	vector<string>		_montageErrors;

public:

	Simulation() = delete;
	Simulation(const Configuration& config_, const House& house_, unique_ptr<AbstractAlgorithm>& algo_, string algoName_);
	virtual ~Simulation();

	bool step();
	int getStepsCount() const { return _robot.totalSteps; }
	int getTotalDirtCount() const { return _house.getTotalDirtAmount(); }
	int getCleanedDirtCount() const { return _robot.cleanedDirt; }
	string getAlgoName() const { return _algoName; }
	bool isRobotDocked() const { return (_robot.location == _house.getDocking()); }
	bool isRobotOutOfBattery() const { return _robot.stuck; }
	bool didRobotMisbehave() const { return !_robot.goodBehavior; }
	bool isDone() const;
	void printStatus();
	void CallAboutToFinish(int stepsTillFinishing);
	void createMontage();
	void createMontageVideo();
	vector<string> getMontageErrors() const { return _montageErrors; }

	static int calc_score(const map<string, int>& score_params_);


	RobotInformation getRobotInfo() const { return _robot; }

	// smaller = done with less steps
	bool operator<(const Simulation& other) const;
	bool operator>(const Simulation& other) const;
	static bool Compare(const Simulation* simu, const Simulation* other);

private:
	void updateSensor();


#ifdef _DEBUG_
	int _undisiciplenedRate = 0;
	void makeHimUndisciplened(Direction& direction);
#endif
};


#endif //__SIMULATION__H_