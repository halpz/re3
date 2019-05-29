#include "common.h"
#include "patcher.h"
#include "FileMgr.h"
#include "ParticleMgr.h"

_TODO("work_buff");
UInt8 work_buff[55000];

cParticleSystemMgr mod_ParticleSystemManager;

const Char *ParticleFilename = "PARTICLE.CFG";

//cParticleSystemMgr::cParticleSystemMgr()
void cParticleSystemMgr::ctor()
{
	memset(this, 0, sizeof(*this));
}

void cParticleSystemMgr::Initialise()
{
	LoadParticleData();
	
	for ( Int32 i = 0; i < MAX_PARTICLES; i++ )
		m_aParticles[i].m_pParticles = NULL;
}

void cParticleSystemMgr::LoadParticleData()
{
	CFileMgr::SetDir("DATA");
	CFileMgr::LoadFile(ParticleFilename, work_buff, ARRAY_SIZE(work_buff), "r");
	CFileMgr::SetDir("");
	
	tParticleSystemData *entry = NULL;
	Int32 type = PARTICLE_FIRST;
	
	Char *lineStart = (Char *)work_buff;
	Char *lineEnd = lineStart + 1;
	
	Char line[500];
	Char delims[4];

	while ( true )
	{
		ASSERT(lineStart != NULL);
		ASSERT(lineEnd != NULL);
		
		while ( *lineEnd != '\n' )
			++lineEnd;
		
		Int32 lineLength = lineEnd - lineStart;
		
		ASSERT(lineLength < 500);

		strncpy(line, lineStart, lineLength);
		
		line[lineLength] = '\0';
		
		if ( !strcmp(line, ";the end") )
			break;
		
		if ( *line != ';' )
		{
			Int32 param = CFG_PARAM_FIRST;

			strcpy(delims, " \t");
			
			Char *value = strtok(line, delims);
			
			ASSERT(value != NULL);
			
			do
			{	
				switch ( param )
				{
					case CFG_PARAM_PARTICLE_TYPE_NAME:
						ASSERT(type < MAX_PARTICLES);
						entry = &m_aParticles[type];
						ASSERT(entry != NULL);
						entry->m_Type = (tParticleType)type++;
						strcpy(entry->m_aName, value);
						break;

					case CFG_PARAM_RENDER_COLOURING_R:
						entry->m_RenderColouring.red = atoi(value);
						break;

					case CFG_PARAM_RENDER_COLOURING_G:
						entry->m_RenderColouring.green = atoi(value);
						break;

					case CFG_PARAM_RENDER_COLOURING_B:
						entry->m_RenderColouring.blue = atoi(value);
						break;

					case CFG_PARAM_INITIAL_COLOR_VARIATION:
						entry->m_InitialColorVariation = min(atoi(value), 100);
						break;

					case CFG_PARAM_FADE_DESTINATION_COLOR_R:
						entry->m_FadeDestinationColor.red = atoi(value);
						break;

					case CFG_PARAM_FADE_DESTINATION_COLOR_G:
						entry->m_FadeDestinationColor.green = atoi(value);
						break;

					case CFG_PARAM_FADE_DESTINATION_COLOR_B:
						entry->m_FadeDestinationColor.blue = atoi(value);
						break;

					case CFG_PARAM_COLOR_FADE_TIME:
						entry->m_ColorFadeTime = atoi(value);
						break;

					case CFG_PARAM_DEFAULT_INITIAL_RADIUS:
						entry->m_fDefaultInitialRadius = atof(value);
						break;

					case CFG_PARAM_EXPANSION_RATE:
						entry->m_fExpansionRate = atof(value);
						break;

					case CFG_PARAM_INITIAL_INTENSITY:
						entry->m_nFadeToBlackInitialIntensity = atoi(value);
						break;

					case CFG_PARAM_FADE_TIME:
						entry->m_nFadeToBlackTime = atoi(value);
						break;

					case CFG_PARAM_FADE_AMOUNT:
						entry->m_nFadeToBlackAmount = atoi(value);
						break;

					case CFG_PARAM_INITIAL_ALPHA_INTENSITY:
						entry->m_nFadeAlphaInitialIntensity = atoi(value);
						break;

					case CFG_PARAM_FADE_ALPHA_TIME:
						entry->m_nFadeAlphaTime = atoi(value);
						break;

					case CFG_PARAM_FADE_ALPHA_AMOUNT:
						entry->m_nFadeAlphaAmount = atoi(value);
						break;

					case CFG_PARAM_INITIAL_ANGLE:
						entry->m_nZRotationInitialAngle = atoi(value);
						break;

					case CFG_PARAM_CHANGE_TIME:
						entry->m_nZRotationChangeTime = atoi(value);
						break;

					case CFG_PARAM_ANGLE_CHANGE_AMOUNT:
						entry->m_nZRotationAngleChangeAmount = atoi(value);
						break;

					case CFG_PARAM_INITIAL_Z_RADIUS:
						entry->m_fInitialZRadius = atof(value);
						break;

					case CFG_PARAM_Z_RADIUS_CHANGE_TIME:
						entry->m_nZRadiusChangeTime = atoi(value);
						break;

					case CFG_PARAM_Z_RADIUS_CHANGE_AMOUNT:
						entry->m_fZRadiusChangeAmount = atof(value);
						break;

					case CFG_PARAM_ANIMATION_SPEED:
						entry->m_nAnimationSpeed = atoi(value);
						break;

					case CFG_PARAM_START_ANIMATION_FRAME:
						entry->m_nStartAnimationFrame = atoi(value);
						break;

					case CFG_PARAM_FINAL_ANIMATION_FRAME:
						entry->m_nFinalAnimationFrame = atoi(value);
						break;

					case CFG_PARAM_ROTATION_SPEED:
						entry->m_nRotationSpeed = atoi(value);
						break;

					case CFG_PARAM_GRAVITATIONAL_ACCELERATION:
						entry->m_fGravitationalAcceleration = atof(value);
						break;

					case CFG_PARAM_FRICTION_DECCELERATION:
						entry->m_nFrictionDecceleration = atoi(value);
						break;

					case CFG_PARAM_LIFE_SPAN:
						entry->m_nLifeSpan = atoi(value);
						break;

					case CFG_PARAM_POSITION_RANDOM_ERROR:
						entry->m_fPositionRandomError = atof(value);
						break;

					case CFG_PARAM_VELOCITY_RANDOM_ERROR:
						entry->m_fVelocityRandomError = atof(value);
						break;

					case CFG_PARAM_EXPANSION_RATE_ERROR:
						entry->m_fExpansionRateError = atof(value);
						break;

					case CFG_PARAM_ROTATION_RATE_ERROR:
						entry->m_nRotationRateError = atoi(value);
						break;

					case CFG_PARAM_LIFE_SPAN_ERROR_SHAPE:
						entry->m_nLifeSpanErrorShape = atoi(value);
						break;

					case CFG_PARAM_TRAIL_LENGTH_MULTIPLIER:
						entry->m_fTrailLengthMultiplier = atof(value);
						break;

					case CFG_PARAM_PARTICLE_CREATE_RANGE:
						entry->m_fCreateRange = SQR(atof(value));
						break;

					case CFG_PARAM_FLAGS:
						entry->Flags = atoi(value);
						break;
				}
				
				value = strtok(NULL, delims);

				param++;

				if ( param > CFG_PARAM_LAST )
					param = CFG_PARAM_FIRST;
		
			} while ( value != NULL );
		}
		
		lineEnd++;
		lineStart = lineEnd;
		lineEnd++;
	}
}

STARTPATCHES
	InjectHook(0x50FCB0, &cParticleSystemMgr::ctor, PATCH_JUMP);
	InjectHook(0x50FCD0, &cParticleSystemMgr::Initialise, PATCH_JUMP);
	InjectHook(0x50FDF0, &cParticleSystemMgr::LoadParticleData, PATCH_JUMP);
ENDPATCHES