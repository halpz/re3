#include "common.h"

#include "General.h"
#include "FileMgr.h"
#include "PedStats.h"

CPedStats *CPedStats::ms_apPedStats[NUM_PEDSTATS];

void
CPedStats::Initialise(void)
{
	int i;

	debug("Initialising CPedStats...\n");
	for(i = 0; i < NUM_PEDSTATS; i++){
		ms_apPedStats[i] = new CPedStats;
		ms_apPedStats[i]->m_type = PEDSTAT_PLAYER;
		ms_apPedStats[i]->m_name[8] = 'R';	// WHAT?
		ms_apPedStats[i]->m_fleeDistance = 20.0f;
		ms_apPedStats[i]->m_headingChangeRate = 15.0f;
		ms_apPedStats[i]->m_fear = 50;
		ms_apPedStats[i]->m_temper = 50;
		ms_apPedStats[i]->m_lawfulness = 50;
		ms_apPedStats[i]->m_sexiness = 50;
		ms_apPedStats[i]->m_attackStrength = 1.0f;
		ms_apPedStats[i]->m_defendWeakness = 1.0f;
		ms_apPedStats[i]->m_flags = 0;
	}
	debug("Loading pedstats data...\n");
	CPedStats::LoadPedStats();
	debug("CPedStats ready\n");
}

void
CPedStats::Shutdown(void)
{
	int i;
	debug("Shutting down CPedStats...\n");
	for(i = 0; i < NUM_PEDSTATS; i++)
		delete ms_apPedStats[i];
	debug("CPedStats shut down\n");
}

void
CPedStats::LoadPedStats(void)
{
	char *buf;
	char line[256];
	char name[32];
	size_t bp, buflen;
	int lp, linelen;
	int type;
	float fleeDist, headingChangeRate, attackStrength, defendWeakness;
	int fear, temper, lawfullness, sexiness, flags;


	type = 0;
	buf = new char[16 * 1024];

        CFileMgr::SetDir("DATA");
        buflen = CFileMgr::LoadFile("PEDSTATS.DAT", (uint8*)buf, 16 * 1024, "r");
        CFileMgr::SetDir("");

	for(bp = 0; bp < buflen; ){
		// read file line by line
		for(linelen = 0; buf[bp] != '\n' && bp < buflen; bp++){
			if(buf[bp] == '\r' || buf[bp] == ',' || buf[bp] == '\t')
				line[linelen++] = ' ';
			else
				line[linelen++] = buf[bp];
		}
		bp++;
		line[linelen] = '\0';

		// skip white space
		for(lp = 0; line[lp] <= ' '; lp++);

		if(lp >= linelen ||		// FIX: game uses == here, but this is safer if we have empty lines
		   line[lp] == '#')
			continue;

		sscanf(&line[lp], "%s %f %f %d %d %d %d %f %f %d",
			name,
			&fleeDist,
			&headingChangeRate,
			&fear,
			&temper,
			&lawfullness,
			&sexiness,
			&attackStrength,
			&defendWeakness,
			&flags);
		ms_apPedStats[type]->m_type = (ePedStats)type;
		strncpy(ms_apPedStats[type]->m_name, name, 24);	// FIX: game uses strcpy
		ms_apPedStats[type]->m_fleeDistance = fleeDist;
		ms_apPedStats[type]->m_headingChangeRate = headingChangeRate;
		ms_apPedStats[type]->m_fear = fear;
		ms_apPedStats[type]->m_temper = temper;
		ms_apPedStats[type]->m_lawfulness = lawfullness;
		ms_apPedStats[type]->m_sexiness = sexiness;
		ms_apPedStats[type]->m_attackStrength = attackStrength;
		ms_apPedStats[type]->m_defendWeakness = defendWeakness;
		ms_apPedStats[type]->m_flags = flags;
		type++;
	}

	delete[] buf;
}

ePedStats
CPedStats::GetPedStatType(char *name)
{
	for(uint16 type = 0; type < NUM_PEDSTATS; type++)
		if(!CGeneral::faststrcmp(ms_apPedStats[type]->m_name, name))
			return (ePedStats) type;

	return NUM_PEDSTATS;
}
