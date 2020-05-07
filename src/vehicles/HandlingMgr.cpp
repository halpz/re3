#include "common.h"

#include "main.h"
#include "FileMgr.h"
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
	"GOLFCART",
	"VOODOO",
	"WASHING",
	"CUBAN",
	"ROMERO",
	"PACKER",
	"ADMIRAL",
	"GANGBUR",
	"ZEBRA",
	"TOPFUN",
	"GLENDALE",
	"OCEANIC",
	"HERMES",
	"SABRE1",
	"SABRETUR",
	"PHEONIX",
	"WALTON",
	"REGINA",
	"COMET",
	"DELUXO",
	"BURRITO",
	"SPAND",
	"BAGGAGE",
	"KAUFMAN",
	"RANCHER",
	"FBIRANCH",
	"VIRGO",
	"GREENWOO",
	"HOTRING",
	"SANDKING",
	"BLISTAC",
	"BOXVILLE",
	"BENSON",
	"DESPERAD",
	"LOVEFIST",
	"BLOODRA",
	"BLOODRB",
	"BIKE",
	"MOPED",
	"DIRTBIKE",
	"ANGEL",
	"FREEWAY",
	"PREDATOR",
	"SPEEDER",
	"REEFER",
	"RIO",
	"SQUALO",
	"TROPIC",
	"COASTGRD",
	"DINGHY",
	"MARQUIS",
	"CUPBOAT",
	"SEAPLANE",
	"SPARROW",
	"SEASPAR",
	"MAVERICK",
	"COASTMAV",
	"POLMAV",
	"HUNTER",
	"RCBARON",
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
	field_4 = 0.9f;
	field_8 = 1.0f;
	field_C = 0.8f;
	field_10 = 0.98f;
}

void
cHandlingDataMgr::LoadHandlingData(void)
{
	char *start, *end;
	char line[201];	// weird value
	char delim[4];	// not sure
	char *word;
	int field, handlingId;
	int keepGoing;
	tHandlingData *handling;

	CFileMgr::SetDir("DATA");
	CFileMgr::LoadFile(HandlingFilename, work_buff, sizeof(work_buff), "r");
	CFileMgr::SetDir("");

	start = (char*)work_buff;
	end = start+1;
	handling = nil;
	keepGoing = 1;

	while(keepGoing){
		// find end of line
		while(*end != '\n') end++;

		// get line
		strncpy(line, start, end - start);
		line[end - start] = '\0';
		start = end+1;
		end = start+1;

		// yeah, this is kinda crappy
		if(strncmp(line, ";the end", 9) == 0)
			keepGoing = 0;
//		else if(line[0] != ';'){
// TODO(MIAMI): read boat, bike, flying values
		else if(line[0] != ';' && line[0] != '%' && line[0] != '!' && line[0] != '$'){
			field = 0;
			strcpy(delim, " \t");
			// FIX: game seems to use a do-while loop here
			for(word = strtok(line, delim); word; word = strtok(nil, delim)){
				switch(field){
				case  0:
					handlingId = FindExactWord(word, (const char*)VehicleNames, 14, NUMHANDLINGS);
					assert(handlingId >= 0 && handlingId < NUMHANDLINGS);
					handling = &HandlingData[handlingId];
					handling->nIdentifier = (eHandlingId)handlingId;
					break;
				case  1: handling->fMass = strtod(word, nil); break;
				case  2: handling->Dimension.x = strtod(word, nil); break;
				case  3: handling->Dimension.y = strtod(word, nil); break;
				case  4: handling->Dimension.z = strtod(word, nil); break;
				case  5: handling->CentreOfMass.x = strtod(word, nil); break;
				case  6: handling->CentreOfMass.y = strtod(word, nil); break;
				case  7: handling->CentreOfMass.z = strtod(word, nil); break;
				case  8: handling->nPercentSubmerged = atoi(word); break;
				case  9: handling->fTractionMultiplier = strtod(word, nil); break;
				case 10: handling->fTractionLoss = strtod(word, nil); break;
				case 11: handling->fTractionBias = strtod(word, nil); break;
				case 12: handling->Transmission.nNumberOfGears = atoi(word); break;
				case 13: handling->Transmission.fMaxVelocity = strtod(word, nil); break;
				case 14: handling->Transmission.fEngineAcceleration = strtod(word, nil) * 0.4f; break;
				case 15: handling->Transmission.nDriveType = word[0]; break;
				case 16: handling->Transmission.nEngineType = word[0]; break;
				case 17: handling->fBrakeDeceleration = strtod(word, nil); break;
				case 18: handling->fBrakeBias = strtod(word, nil); break;
				case 19: handling->bABS = !!atoi(word); break;
				case 20: handling->fSteeringLock = strtod(word, nil); break;
				case 21: handling->fSuspensionForceLevel = strtod(word, nil); break;
				case 22: handling->fSuspensionDampingLevel = strtod(word, nil); break;
				case 23: handling->fSeatOffsetDistance = strtod(word, nil); break;
				case 24: handling->fCollisionDamageMultiplier = strtod(word, nil); break;
				case 25: handling->nMonetaryValue = atoi(word); break;
				case 26: handling->fSuspensionUpperLimit = strtod(word, nil); break;
				case 27: handling->fSuspensionLowerLimit = strtod(word, nil); break;
				case 28: handling->fSuspensionBias = strtod(word, nil); break;
				case 29:
					// TODO(MIAMI): suspension anti-dive multiplier
					break;
				case 30:
					sscanf(word, "%x", &handling->Flags);
					handling->Transmission.Flags = handling->Flags;
					break;
				case 31: handling->FrontLights = atoi(word); break;
				case 32: handling->RearLights = atoi(word); break;
				}
				field++;
			}
			ConvertDataToGameUnits(handling);
		}
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
	// TODO: figure out what exactly is being converted here
	float velocity, a, b, specificVolume;

	handling->Transmission.fEngineAcceleration /= 2500.0f;
	handling->Transmission.fMaxVelocity /= 180.0f;
	handling->fBrakeDeceleration /= 2500.0f;
	handling->fTurnMass = (sq(handling->Dimension.x) + sq(handling->Dimension.y)) * handling->fMass / 12.0f;
	if(handling->fTurnMass < 10.0f)
		handling->fTurnMass *= 5.0f;
	handling->fInvMass = 1.0f/handling->fMass;
	handling->fBuoyancy = 100.0f/handling->nPercentSubmerged * 0.008f*handling->fMass;

	// What the hell is going on here?
	specificVolume = handling->Dimension.x*handling->Dimension.z*0.5f / handling->fMass;	// ?
	a = 0.0f;
	b = 100.0f;
	velocity = handling->Transmission.fMaxVelocity;
	while(a < b && velocity > 0.0f){
		velocity -= 0.01f;
		a = handling->Transmission.fEngineAcceleration/6.0f;
		b = -velocity * (1.0f/(specificVolume * sq(velocity) + 1.0f) - 1.0f);
	}

	if(handling->nIdentifier == HANDLING_RCBANDIT){
		handling->Transmission.fUnkMaxVelocity = handling->Transmission.fMaxVelocity;
	}else{
		handling->Transmission.fUnkMaxVelocity = velocity;
		handling->Transmission.fMaxVelocity = velocity * 1.2f;
	}
	handling->Transmission.fMaxReverseVelocity = -0.2f;

	if(handling->Transmission.nDriveType == '4')
		handling->Transmission.fEngineAcceleration /= 4.0f;
	else
		handling->Transmission.fEngineAcceleration /= 2.0f;

	handling->Transmission.InitGearRatios();
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
