#pragma once
#include "Blackboard.h"
#include <functional>
#include "DynamicSteeringOutput.h"
#include "KinematicSteeringOutput.h"
#include "InteractableObject.h"
#include "Trash.h"
#include "ChargingStation.h"
#include <shared_mutex>
#include "Rigidbody.h"
#include <atomic>


class BlackboardJR : public Blackboard
{
public:
	std::atomic<Rigidbody*> character_rb_;

	glm::vec2 character_position_;
	std::shared_mutex mtx_character_position_;

	std::set<Trash*> trashes_;
	std::shared_mutex mtx_trashes_;

	const std::atomic<int> max_trashes_size_;

	std::set<ChargingStation*> charging_stations_;
	std::shared_mutex mtx_charging_stations_;

	const std::atomic<int> min_charging_stations_size_;
	const std::atomic<int> max_charging_stations_size_;

	std::function<DynamicSteeringOutput()> get_dynamic_steering_;

	std::atomic<int> power_;
	const std::atomic<int> max_power_;

	std::atomic<InteractableObject*> target_;

	std::function<KinematicSteeringOutput()> get_kinematic_steering_;

	std::string status_string_;
	std::shared_mutex mtx_status_string_;

	std::atomic<int> notice_time_;
	std::string notice_string_;
	std::shared_mutex mtx_notice_string_;

	BlackboardJR(Rigidbody* character_rb, int power, int max_power, int max_trashes_size, int min_charging_stations_size, int max_charging_stations_size);
	void SafeCleanUp() override;

	void Update();
	void Draw();
	void AddTrash(glm::vec2 position, float radius, ofColor color);
	void AddChargingStation(glm::vec2 position, float size, ofColor color);
	int GetTrashesSize();
	int GetChargingStationsSize();
	DynamicSteeringOutput GetDynamicSteering();
	KinematicSteeringOutput GetKinematicSteering();
};

