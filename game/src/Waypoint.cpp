#include "GameCommonIncludes.h"
#include "Waypoint.h"

#include "EditorScreen.h"

Waypoint::Waypoint()
{
	mClassName = "Waypoint";

	CreateVarProperty("connections", mConnectedWaypointsIDs);
}

Waypoint::~Waypoint()
{

}

void Waypoint::Serialize( YAML::Emitter& iEmitter )
{
	//populate IDs vector
	mConnectedWaypointsIDs.clear();
	for(WaypointsVec::const_iterator iter = mConnectedWaypoints.begin(); iter != mConnectedWaypoints.end(); ++iter)
	{
		mConnectedWaypointsIDs.push_back((*iter)->GetUniqueID());
	}

	WorldObject::Serialize(iEmitter);
}

void Waypoint::Fix()
{
	for(IDsVec::iterator iter = mConnectedWaypointsIDs.begin(); iter != mConnectedWaypointsIDs.end(); ++iter)
	{
		WorldObject* worldObject = mWorld->GetObject(mWorld->ResolveID((*iter)));
		if(worldObject)
		{
			mConnectedWaypoints.insert(static_cast<Waypoint*>(worldObject));
		}
	}
}

void Waypoint::Connect( Waypoint* iWaypoint )
{
	if(iWaypoint != this)
	{
		mConnectedWaypoints.insert(iWaypoint);
	}
}

void Waypoint::Disconnect( Waypoint* iWaypoint )
{
	mConnectedWaypoints.erase(iWaypoint);
}

void Waypoint::DisconnectAll()
{
	for(WaypointsVec::const_iterator iter = mConnectedWaypoints.begin(); iter != mConnectedWaypoints.end(); ++iter)
	{
		(*iter)->Disconnect(this);
	}

	mConnectedWaypoints.clear();
}

void Waypoint::FuseConnections( WaypointsVec& iOtherWaypoints )
{
	for(WaypointsVec::iterator iter = iOtherWaypoints.begin(); iter != iOtherWaypoints.end(); ++iter)
	{
		(*iter)->Connect(this);
		this->Connect((*iter));
	}
}