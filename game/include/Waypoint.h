#ifndef __Waypoint_H__
#define __Waypoint_H__

class Waypoint : public rt::WorldObject
{
public:
	typedef std::set<Waypoint*>		WaypointsVec;
	typedef std::vector<rt::RTID>	IDsVec;

	Waypoint();
	virtual ~Waypoint();

	virtual void Serialize(YAML::Emitter& iEmitter);

	virtual void Fix();

	void Connect(Waypoint* iWaypoint);
	void Disconnect(Waypoint* iWaypoint);

	void DisconnectAll();

	void FuseConnections(WaypointsVec& iOtherWaypoints);

protected:
	WaypointsVec		mConnectedWaypoints;
	IDsVec				mConnectedWaypointsIDs;
};

#endif