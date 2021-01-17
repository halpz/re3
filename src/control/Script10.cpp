#include "common.h"

#include "Script.h"
#include "ScriptCommands.h"

#include "PlayerPed.h"
#include "World.h"

int8 CRunningScript::ProcessCommands1600To1699(int32 command)
{
	switch (command) {
	case COMMAND_1600:
		script_assert(false);
		return 0;
	case COMMAND_1601:
		script_assert(false);
		return 0;
	case COMMAND_1602:
		script_assert(false);
		return 0;
	case COMMAND_1603:
		script_assert(false);
		return 0;
	case COMMAND_1604:
		script_assert(false);
		return 0;
	case COMMAND_1605:
		script_assert(false);
		return 0;
	case COMMAND_1606:
		script_assert(false);
		return 0;
	case COMMAND_1607:
		CollectParameters(&m_nIp, 1);
		// TODO (SET_TOTAL_CARS_FOR_EXPORT)
		return 0;
	case COMMAND_1608:
		script_assert(false);
		return 0;
	case COMMAND_1609:
		script_assert(false);
		return 0;
	case COMMAND_1610:
		script_assert(false);
		return 0;
	case COMMAND_1611:
		script_assert(false);
		return 0;
	case COMMAND_1612:
		script_assert(false);
		return 0;
	case COMMAND_1613:
		script_assert(false);
		return 0;
	case COMMAND_1614:
		script_assert(false);
		return 0;
	case COMMAND_1615:
		// TODO (GET_DEVELOPER_FLAG?)
		UpdateCompareFlag(false);
		return 0;
	case COMMAND_1616:
		// TODO (SET_DEVELOPER_FLAG)
		return 0;
	case COMMAND_1617:
		script_assert(false);
		return 0;
	case COMMAND_1618:
		script_assert(false);
		return 0;
	case COMMAND_1619:
		script_assert(false);
		return 0;
	case COMMAND_1620:
		script_assert(false);
		return 0;
	case COMMAND_1621:
	{
		wchar* key = CTheScripts::GetTextByKeyFromScript(&m_nIp);
		CollectParameters(&m_nIp, 2);
		// TODO (SET_SUBTITLE_TEXT)
		return 0;
	}
	case COMMAND_1622:
		script_assert(false);
		return 0;
	case COMMAND_1623:
		script_assert(false);
		return 0;
	case COMMAND_1624:
		script_assert(false);
		return 0;
	case COMMAND_1625:
		script_assert(false);
		return 0;
	case COMMAND_1626:
		script_assert(false);
		return 0;
	case COMMAND_1627:
		script_assert(false);
		return 0;
	case COMMAND_1628:
		script_assert(false);
		return 0;
	case COMMAND_1629:
		script_assert(false);
		return 0;
	case COMMAND_1630:
		script_assert(false);
		return 0;
	case COMMAND_1631:
		script_assert(false);
		return 0;
	case COMMAND_1632:
		script_assert(false);
		return 0;
	case COMMAND_1633:
		script_assert(false);
		return 0;
	case COMMAND_1634:
		script_assert(false);
		return 0;
	case COMMAND_1635:
	{
		char tmp[12]; // TODO
		CTheScripts::ReadTextLabelFromScript(&m_nIp, tmp);
		m_nIp += KEY_LENGTH_IN_SCRIPT;
		// TODO (CHANGE_STORED_PLAYER_OUTFIT?)
		return 0;
	}
	case COMMAND_1636:
		script_assert(false);
		return 0;
	case COMMAND_1637:
		script_assert(false);
		return 0;
	case COMMAND_1638:
		script_assert(false);
		return 0;
	case COMMAND_1639:
		script_assert(false);
		return 0;
	case COMMAND_1640:
		CollectParameters(&m_nIp, 2);
		// TODO (LOCK_GARAGE?)
		return 0;
	case COMMAND_1641:
		// TODO
		UpdateCompareFlag(true);
		return 0;
	case COMMAND_1642:
		script_assert(false);
		return 0;
	case COMMAND_1643:
		script_assert(false);
		return 0;
	case COMMAND_1644:
		script_assert(false);
		return 0;
	case COMMAND_1645:
	{
		CollectParameters(&m_nIp, 1);
		// TODO (GET_STORED_WEAPON?)
		CPed* pPed = CWorld::Players[ScriptParams[0]].m_pPed;
		script_assert(pPed);
		ScriptParams[0] = pPed->m_storedWeapon;
		StoreParameters(&m_nIp, 1);
		return 0;
	}
	case COMMAND_1646:
		CollectParameters(&m_nIp, 1);
		// TODO (DISABLE_PAUSE_MENU?)
		return 0;
	case COMMAND_1647:
		CollectParameters(&m_nIp, 1);
		// TODO (IS_CHANNEL_PLAYING?)
		UpdateCompareFlag(false);
		return 0;
	case COMMAND_1648:
		CollectParameters(&m_nIp, 3);
		// TODO (SET_CLOCK_EVENT_WARNING);
		return 0;
	case COMMAND_1649:
		CollectParameters(&m_nIp, 3);
		// TODO (SET_EXTRA_COLOUR_DIRECTION)
		return 0;
	case COMMAND_1650:
		script_assert(false);
		return 0;
	case COMMAND_1651:
		script_assert(false);
		return 0;
	case COMMAND_1652:
		script_assert(false);
		return 0;
	case COMMAND_1653:
		script_assert(false);
		return 0;
	case COMMAND_1654:
		script_assert(false);
		return 0;
	case COMMAND_1655:
		script_assert(false);
		return 0;
	case COMMAND_1656:
		CollectParameters(&m_nIp, 2);
		// TODO (?)
		return 0;
	default:
		script_assert(0);
	}
	return -1;
}