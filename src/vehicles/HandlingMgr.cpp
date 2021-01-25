#include "common.h"

#include "main.h"
#include "FileMgr.h"
#include "Physical.h"
#include "HandlingMgr.h"

cHandlingDataMgr mod_HandlingManager;

const char *HandlingFilename = "HANDLING.CFG";

const char VehicleNames[NUMHANDLINGS][14] = {
	"LANDSTAL",
	"IDAHO",
	"STINGER",
	"LINERUN",
	"PEREN",
	"SENTINEL",
	"PATRIOT",
	"FIRETRUK",
	"TRASH",
	"STRETCH",
	"MANANA",
	"INFERNUS",
	"PONY",
	"MULE",
	"CHEETAH",
	"AMBULAN",
	"FBICAR",
	"MOONBEAM",
	"ESPERANT",
	"TAXI",
	"KURUMA",
	"BOBCAT",
	"MRWHOOP",
	"BFINJECT",
	"POLICE",
	"ENFORCER",
	"SECURICA",
	"BANSHEE",
	"BUS",
	"RHINO",
	"BARRACKS",
	"TRAIN",
	"FERRY",
	"HELI",
	"DODO",
	"COACH",
	"CABBIE",
	"STALLION",
	"RUMPO",
	"RCBANDIT",
	"MAFIA",
	"AIRTRAIN",
	"DEADDODO",
	"FLATBED",
	"YANKEE",
	"BLISTA",
	"BELLYUP",
	"MRWONGS",
	"YARDIE",
	"YAKUZA",
	"DIABLOS",
	"COLUMB",
	"HOODS",
	"PANLANT",
	"BORGNINE",
	"CAMPVAN",
	"BALLOT",
	"SPIDER",
	"SHELBY",
	"PONTIAC",
	"ESPRIT",
	"MINI",
	"HOTROD",
	"SINDACCO",
	"FORELLI",
	"BIKE",
	"MOPED",
	"DIRTBIKE",
	"ANGEL",
	"DIRTBIK2",
	"ANGE2",
	"FREEWAY",
	"PREDATOR",
	"SPEEDER",
	"REEFER",
	"MAVERICK",
	"COASTMAV",
	"POLMAV",
	"HUNTER",
	"RCGOBLIN",
	"RCCOPTER"
};

cHandlingDataMgr::cHandlingDataMgr(void)
{
	memset(this, 0, sizeof(*this));
}

void
cHandlingDataMgr::Initialise(void)
{
	LoadHandlingData();
	field_0 = 0.1f;
	fWheelFriction = 0.9f;
	field_8 = 1.0f;
	field_C = 0.8f;
	field_10 = 0.98f;
}

void
cHandlingDataMgr::LoadHandlingData(void)
{
	char *start, *end;
	char line[300];
	char delim[4];	// not sure
	char *word;
	int field, handlingId;
	tHandlingData *handling;
	tFlyingHandlingData *flyingHandling;
	tBoatHandlingData *boatHandling;
	tBikeHandlingData *bikeHandling;

	CFileMgr::SetDir("DATA");
	ssize_t filesz = CFileMgr::LoadFile(HandlingFilename, work_buff, sizeof(work_buff), "r");
	CFileMgr::SetDir("");

	start = (char*)work_buff;
	end = start+1;
	handling = nil;
	flyingHandling = nil;
	boatHandling = nil;
	bikeHandling = nil;

	while(start < (char*)&work_buff[filesz]){
		// find end of line
		while(*end != '\n') end++;

		// get line
		strncpy(line, start, end - start);
		line[end - start] = '\0';

		// yeah, this is kinda crappy
		if(strcmp(line, ";the end") == 0)
			break;
		else if(line[0] != ';'){
			if(line[0] == '!'){
				// Bike data
				field = 0;
				strcpy(delim, " \t");
				// FIX: game seems to use a do-while loop here
				for(word = strtok(line, delim); word; word = strtok(nil, delim)){
					switch(field){
					case  0: break;
					case  1:
						handlingId = FindExactWord(word, (const char*)VehicleNames, 14, NUMHANDLINGS);
						assert(handlingId >= 0 && handlingId < NUMHANDLINGS);
						bikeHandling = GetBikePointer(handlingId);
						bikeHandling->nIdentifier = (tVehicleType)handlingId;
						break;
					case  2: bikeHandling->fLeanFwdCOM = atof(word); break;
					case  3: bikeHandling->fLeanFwdForce = atof(word); break;
					case  4: bikeHandling->fLeanBakCOM = atof(word); break;
					case  5: bikeHandling->fLeanBackForce = atof(word); break;
					case  6: bikeHandling->fMaxLean = atof(word); break;
					case  7: bikeHandling->fFullAnimLean = atof(word); break;
					case  8: bikeHandling->fDesLean = atof(word); break;
					case  9: bikeHandling->fSpeedSteer = atof(word); break;
					case 10: bikeHandling->fSlipSteer = atof(word); break;
					case 11: bikeHandling->fNoPlayerCOMz = atof(word); break;
					case 12: bikeHandling->fWheelieAng = atof(word); break;
					case 13: bikeHandling->fStoppieAng = atof(word); break;
					case 14: bikeHandling->fWheelieSteer = atof(word); break;
					case 15: bikeHandling->fWheelieStabMult = atof(word); break;
					case 16: bikeHandling->fStoppieStabMult = atof(word); break;
					}
					field++;
				}
				ConvertBikeDataToGameUnits(bikeHandling);
			}else if(line[0] == '$'){
				// Flying data
				field = 0;
				strcpy(delim, " \t");
				// FIX: game seems to use a do-while loop here
				for(word = strtok(line, delim); word; word = strtok(nil, delim)){
					switch(field){
					case  0: break;
					case  1:
						handlingId = FindExactWord(word, (const char*)VehicleNames, 14, NUMHANDLINGS);
						assert(handlingId >= 0 && handlingId < NUMHANDLINGS);
						flyingHandling = GetFlyingPointer(handlingId);
						flyingHandling->nIdentifier = (tVehicleType)handlingId;
						break;
					case  2: flyingHandling->fThrust = atof(word); break;
					case  3: flyingHandling->fThrustFallOff = atof(word); break;
					case  4: flyingHandling->fYaw = atof(word); break;
					case  5: flyingHandling->fYawStab = atof(word); break;
					case  6: flyingHandling->fSideSlip = atof(word); break;
					case  7: flyingHandling->fRoll = atof(word); break;
					case  8: flyingHandling->fRollStab = atof(word); break;
					case  9: flyingHandling->fPitch = atof(word); break;
					case 10: flyingHandling->fPitchStab = atof(word); break;
					case 11: flyingHandling->fFormLift = atof(word); break;
					case 12: flyingHandling->fAttackLift = atof(word); break;
					case 13: flyingHandling->fMoveRes = atof(word); break;
					case 14: flyingHandling->vecTurnRes.x = atof(word); break;
					case 15: flyingHandling->vecTurnRes.y = atof(word); break;
					case 16: flyingHandling->vecTurnRes.z = atof(word); break;
					case 17: flyingHandling->vecSpeedRes.x = atof(word); break;
					case 18: flyingHandling->vecSpeedRes.y = atof(word); break;
					case 19: flyingHandling->vecSpeedRes.z = atof(word); break;
					}
					field++;
				}
			}else if(line[0] == '%'){
				// Boat data
				field = 0;
				strcpy(delim, " \t");
				// FIX: game seems to use a do-while loop here
				for(word = strtok(line, delim); word; word = strtok(nil, delim)){
					switch(field){
					case  0: break;
					case  1:
						handlingId = FindExactWord(word, (const char*)VehicleNames, 14, NUMHANDLINGS);
						assert(handlingId >= 0 && handlingId < NUMHANDLINGS);
						boatHandling = GetBoatPointer(handlingId);
						boatHandling->nIdentifier = (tVehicleType)handlingId;
						break;
					case  2: boatHandling->fThrustY = atof(word); break;
					case  3: boatHandling->fThrustZ = atof(word); break;
					case  4: boatHandling->fThrustAppZ = atof(word); break;
					case  5: boatHandling->fAqPlaneForce = atof(word); break;
					case  6: boatHandling->fAqPlaneLimit = atof(word); break;
					case  7: boatHandling->fAqPlaneOffset = atof(word); break;
					case  8: boatHandling->fWaveAudioMult = atof(word); break;
					case  9: boatHandling->vecMoveRes.x = atof(word); break;
					case 10: boatHandling->vecMoveRes.y = atof(word); break;
					case 11: boatHandling->vecMoveRes.z = atof(word); break;
					case 12: boatHandling->vecTurnRes.x = atof(word); break;
					case 13: boatHandling->vecTurnRes.y = atof(word); break;
					case 14: boatHandling->vecTurnRes.z = atof(word); break;
					case 15: boatHandling->fLook_L_R_BehindCamHeight = atof(word); break;
					}
					field++;
				}
			}else{
				field = 0;
				strcpy(delim, " \t");
				// FIX: game seems to use a do-while loop here
				for(word = strtok(line, delim); word; word = strtok(nil, delim)){
					switch(field){
					case  0:
						handlingId = FindExactWord(word, (const char*)VehicleNames, 14, NUMHANDLINGS);
						assert(handlingId >= 0 && handlingId < NUMHANDLINGS);
						handling = &HandlingData[handlingId];
						handling->nIdentifier = (tVehicleType)handlingId;
						break;
					case  1: handling->fMass = atof(word); break;
					case  2: handling->fTurnMass = atof(word); break;
					case  3: handling->fDragMult = atof(word); break;
					case  4: handling->CentreOfMass.x = atof(word); break;
					case  5: handling->CentreOfMass.y = atof(word); break;
					case  6: handling->CentreOfMass.z = atof(word); break;
					case  7: handling->nPercentSubmerged = atoi(word); break;
					case  8: handling->fTractionMultiplier = atof(word); break;
					case  9: handling->fTractionLoss = atof(word); break;
					case 10: handling->fTractionBias = atof(word); break;
					case 11: handling->Transmission.nNumberOfGears = atoi(word); break;
					case 12: handling->Transmission.fMaxVelocity = atof(word); break;
					case 13: handling->Transmission.fEngineAcceleration = atof(word) * 0.4; break;
					case 14: handling->Transmission.fEngineInertia = atof(word); break;
					case 15: handling->Transmission.nDriveType = word[0]; break;
					case 16: handling->Transmission.nEngineType = word[0]; break;
					case 17: handling->fBrakeDeceleration = atof(word); break;
					case 18: handling->fBrakeBias = atof(word); break;
					case 19: handling->bABS = !!atoi(word); break;
					case 20: handling->fSteeringLock = atof(word); break;
					case 21: handling->fSuspensionForceLevel = atof(word); break;
					case 22: handling->fSuspensionDampingLevel = atof(word); break;
					// case 23:	// fSuspensionHighSpdComDamp unused
					case 24: handling->fSuspensionUpperLimit = atof(word); break;
					case 25: handling->fSuspensionLowerLimit = atof(word); break;
					case 26: handling->fSuspensionBias = atof(word); break;
					case 27: handling->fSuspensionAntidiveMultiplier = atof(word); break;
					case 28: handling->fSeatOffsetDistance = atof(word); break;
					case 29: handling->fCollisionDamageMultiplier = atof(word); break;
					case 30: handling->nMonetaryValue = atoi(word); break;
					case 31:
						sscanf(word, "%x", &handling->Flags);
					//	handling->Transmission.Flags = handling->Flags;
						break;
					case 32: handling->FrontLights = atoi(word); break;
					case 33: handling->RearLights = atoi(word); break;
					}
					field++;
				}
				ConvertDataToGameUnits(handling);
			}
		}
		start = end+1;
		end = start+1;
	}
}

int
cHandlingDataMgr::FindExactWord(const char *word, const char *words, int wordLen, int numWords)
{
	int i;

	for(i = 0; i < numWords; i++){
		// BUG: the game does something really stupid here, it's fixed here
		if(strncmp(word, words, wordLen) == 0)
			return i;
		words += wordLen;
	}
	return numWords;
}


void
cHandlingDataMgr::ConvertDataToGameUnits(tHandlingData *handling)
{
	// convert distance to m, time to 1/50s
	float velocity, a, b;

	handling->Transmission.fEngineAcceleration *= 1.0f/(50.0f*50.0f);
	handling->Transmission.fMaxVelocity *= 1000.0f/(60.0f*60.0f * 50.0f);
	handling->fBrakeDeceleration *= 1.0f/(50.0f*50.0f);
	handling->fInvMass = 1.0f/handling->GetMass();
	handling->fCollisionDamageMultiplier = handling->GetCollisionDamageMultiplier() * 2000.0f/handling->GetMass();
	handling->fBuoyancy = 100.0f/handling->nPercentSubmerged * GRAVITY*handling->GetMass();

	// Don't quite understand this. What seems to be going on is that
	// we calculate a drag (air resistance) deceleration for a given velocity and
	// find the intersection between that and the max engine acceleration.
	// at that point the car cannot accelerate any further and we've found the max velocity.
	a = 0.0f;
	b = 100.0f;
	velocity = handling->Transmission.fMaxVelocity;
	while(a < b && velocity > 0.0f){
		velocity -= 0.01f;
		// what's the 1/6?
		a = handling->Transmission.fEngineAcceleration/6.0f;
		// no idea what's happening here
		float drag;
		if(handling->fDragMult < 0.01f)
			drag = 1.0f - 1.0f/(SQR(velocity)*handling->fDragMult + 1.0f);
		else
			drag = 0.0005f*handling->fDragMult * velocity;
		b = velocity * drag;
	}

	if(handling->nIdentifier == HANDLING_RCBANDIT){
		handling->Transmission.fMaxCruiseVelocity = handling->Transmission.fMaxVelocity;
		handling->Transmission.fMaxReverseVelocity = -handling->Transmission.fMaxVelocity;
	}else if(handling->nIdentifier >= HANDLING_BIKE && handling->nIdentifier <= HANDLING_FREEWAY){
		handling->Transmission.fMaxCruiseVelocity = velocity;
		handling->Transmission.fMaxVelocity = velocity * 1.2f;
		handling->Transmission.fMaxReverseVelocity = -0.05f;
	}else{
		handling->Transmission.fMaxCruiseVelocity = velocity;
		handling->Transmission.fMaxVelocity = velocity * 1.2f;
		handling->Transmission.fMaxReverseVelocity = -0.2f;
	}

	if(handling->Transmission.nDriveType == '4')
		handling->Transmission.fEngineAcceleration /= 4.0f;
	else
		handling->Transmission.fEngineAcceleration /= 2.0f;

	handling->Transmission.InitGearRatios();
}

void
cHandlingDataMgr::ConvertBikeDataToGameUnits(tBikeHandlingData *handling)
{
	handling->fMaxLean = Sin(DEGTORAD(handling->fMaxLean));
	handling->fFullAnimLean = DEGTORAD(handling->fFullAnimLean);
	handling->fWheelieAng = Sin(DEGTORAD(handling->fWheelieAng));
	handling->fStoppieAng = Sin(DEGTORAD(handling->fStoppieAng));
}

int32
cHandlingDataMgr::GetHandlingId(const char *name)
{
	int i;
	for(i = 0; i < NUMHANDLINGS; i++)
		if(strncmp(VehicleNames[i], name, 14) == 0)
			break;
	return i;
}

tFlyingHandlingData*
cHandlingDataMgr::GetFlyingPointer(uint8 id)
{
	if(id >= HANDLING_MAVERICK && id <= HANDLING_RCCOPTER)
		return &FlyingHandlingData[id-HANDLING_MAVERICK];
	return &FlyingHandlingData[0];
}

tBoatHandlingData*
cHandlingDataMgr::GetBoatPointer(uint8 id)
{
	if(id >= HANDLING_PREDATOR && id <= HANDLING_MAVERICK)
		return &BoatHandlingData[id-HANDLING_PREDATOR];
	return &BoatHandlingData[0];
}
