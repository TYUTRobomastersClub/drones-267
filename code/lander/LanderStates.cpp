#include "Controller.h"
#include "LanderStates.h"
#include "QuadcopterState.h"

#include "roscopter/RC.h"

namespace LanderStates {

	bool landerActive = false;

	bool isLanderActive() {
		return landerActive;
	}

	bool updateLanderActive(int controlChannelValue) {
		bool oldLanderActive = false;
		if (controlChannelValue >= 1000 && controlChannelValue <= 2000) //CHECK ME
			landerActive = true;
		else 
			landerActive = false;

		return (oldLanderActive == landerActive);
	}

	States currentState;

	States getState () {
		return currentState;
	}

	bool setState (States newState) {
		bool changed = true;
		if (newState == currentState) {
			changed = false;
		} 
		else {
			currentState = newState;
		}
		return changed;
	}

	roscopter::RC performStateAction() {
		switch (currentState)
		case (States.FLYING):
			return Controller::getManualControlMsg();
		case (States.SEEK_HOME):
			return Controller::getRTLControlMsg()
		case (States.LAND_HIGH):
			return Controller::getTranslateAndDescendControlMsg()
		case (States.LAND_LOW):
			return Controller::getDescentOnlyControlMsg();
		case (States.POWER_OFF):
			if (QuadcopterState::onGround()) {
				return Controller::getPowerOffControlMsg(); 
			}
	}

}
