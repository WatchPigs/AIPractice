#include "BlackboardJR.h"


BlackboardJR::BlackboardJR(Rigidbody* character_rb, int power, int max_power, int max_trashes_size, int min_charging_stations_size, int max_charging_stations_size) :
	character_rb_(character_rb), character_position_(character_rb->position_), power_(power), max_power_(max_power), max_trashes_size_(max_trashes_size), min_charging_stations_size_(min_charging_stations_size), max_charging_stations_size_(max_charging_stations_size), get_kinematic_steering_(nullptr), status_string_("")
{
}

void BlackboardJR::SafeCleanUp()
{
	in_cleaning_up_ = true;
	std::unique_lock<std::shared_mutex> lock(mtx_bb_in_use_);

	target_ = nullptr;

	std::unique_lock<std::shared_mutex> lock_trashes(mtx_trashes_);
	for (Trash* trash : trashes_)
	{
		if (trash != nullptr)
		{
			delete trash;
			trash = nullptr;
		}
	}
	trashes_.clear();
	lock_trashes.unlock();

	std::unique_lock<std::shared_mutex> lock_charging_stations(mtx_charging_stations_);
	for (ChargingStation* charging_station : charging_stations_)
	{
		if (charging_station != nullptr)
		{
			delete charging_station;
			charging_station = nullptr;
		}
	}
	charging_stations_.clear();
	lock_charging_stations.unlock();
}

void BlackboardJR::Update()
{
	std::unique_lock<std::shared_mutex> lock_character_position(mtx_character_position_, std::defer_lock);

	if (lock_character_position.try_lock())
	{
		character_position_ = character_rb_.load()->position_;
		lock_character_position.unlock();
	}
}

void BlackboardJR::Draw()
{
	std::shared_lock<std::shared_mutex> lock_trashes(mtx_trashes_, std::defer_lock);
	if (lock_trashes.try_lock())
	{
		for (Trash* trash : trashes_) trash->Draw();
		lock_trashes.unlock();
	}

	std::shared_lock<std::shared_mutex> lock_charging_stations_(mtx_charging_stations_, std::defer_lock);
	if (lock_charging_stations_.try_lock())
	{
		for (ChargingStation* charging_station : charging_stations_) charging_station->Draw();
		lock_charging_stations_.unlock();
	}
}

void BlackboardJR::AddTrash(glm::vec2 position, float radius, ofColor color)
{
	std::unique_lock<std::shared_mutex> lock_trashes(mtx_trashes_);
	Trash* trash = new Trash(position, radius, color);
	trashes_.insert(trash);
}

void BlackboardJR::AddChargingStation(glm::vec2 position, float size, ofColor color)
{
	std::unique_lock<std::shared_mutex> lock_charging_stations_(mtx_charging_stations_);
	ChargingStation* charging_station = new ChargingStation(position, size, color);
	charging_stations_.insert(charging_station);
}

int BlackboardJR::GetTrashesSize()
{
	std::shared_lock<std::shared_mutex> lock_trashes(mtx_trashes_);
	return trashes_.size();
}

int BlackboardJR::GetChargingStationsSize()
{
	std::shared_lock<std::shared_mutex> lock_charging_stations_(mtx_charging_stations_);
	return charging_stations_.size();
}

DynamicSteeringOutput BlackboardJR::GetDynamicSteering()
{
	//std::shared_lock<std::shared_mutex> lock_get_dynamic_steerings_(mtx_get_dynamic_steerings_);
	DynamicSteeringOutput result;
	//for (auto get_dynamic_steering : get_dynamic_steerings_) result += get_dynamic_steering();
	try
	{
		result = get_dynamic_steering_();
	}
	catch (...)
	{
		ofLog(OF_LOG_ERROR, "No Dynamic steering available");
	}
	return result;
}

KinematicSteeringOutput BlackboardJR::GetKinematicSteering()
{
	KinematicSteeringOutput result;
	try
	{
		result = get_kinematic_steering_();
	}
	catch (...)
	{
		ofLog(OF_LOG_ERROR, "No Kinematic steering available");
	}
	return result;
}