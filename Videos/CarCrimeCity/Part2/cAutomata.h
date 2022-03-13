


#pragma once

#include "olcPixelGameEngine.h"

class cAuto_Track;
class cAuto_Node;
class cAuto_Body;
class cCell;

class cAuto_Node
{
public:
	cAuto_Node();
	cAuto_Node(const olc::vf2d &worldpos);
	olc::vf2d pos;
	bool bBlock = false;
	std::list<cAuto_Track*> listTracks;
};

class cAuto_Track
{
public:
	cAuto_Node* node[2]; // Two end nodes
	cCell* cell; // Pointer to host cell
	olc::vf2d GetPostion(float t, cAuto_Node *pstart);
	std::list<cAuto_Body*> listAutos;
	float fTrackLength = 1.0f;
};

class cAuto_Body
{
public:
	cAuto_Body();
	~cAuto_Body();

public:
	void UpdateAuto(float fElapsedTime);

public:
	olc::vf2d vAutoPos = { 0.0f, 0.0f };
	float fAutoPos = 0.0f; // Location of automata along track
	float fAutoLength = 0.0f; // Physical length of automata
	cAuto_Track *pCurrentTrack = nullptr;
	cAuto_Node *pTrackOriginNode = nullptr;

};
