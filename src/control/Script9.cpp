#include "common.h"

#include "Script.h"
#include "ScriptCommands.h"

int8 CRunningScript::ProcessCommands1500To1599(int32 command)
{
	switch (command) {
	case COMMAND_1497:
		script_assert(false);
		return 0;
	case COMMAND_1498:
		script_assert(false);
		return 0;
	case COMMAND_1499:
		script_assert(false);
		return 0;
	case COMMAND_1500:
		script_assert(false);
		return 0;
	case COMMAND_1501:
		script_assert(false);
		return 0;
	case COMMAND_1502:
		script_assert(false);
		return 0;
	case COMMAND_1503:
		script_assert(false);
		return 0;
	case COMMAND_1504:
		script_assert(false);
		return 0;
	case COMMAND_1505:
		script_assert(false);
		return 0;
	case COMMAND_1506:
		script_assert(false);
		return 0;
	case COMMAND_1507:
		script_assert(false);
		return 0;
	case COMMAND_1508:
		script_assert(false);
		return 0;
	case COMMAND_1509:
		script_assert(false);
		return 0;
	case COMMAND_1510:
		script_assert(false);
		return 0;
	case COMMAND_1511:
		script_assert(false);
		return 0;
	case COMMAND_1512:
		script_assert(false);
		return 0;
	case COMMAND_1513:
		script_assert(false);
		return 0;
	case COMMAND_1514:
		script_assert(false);
		return 0;
	case COMMAND_1515:
		script_assert(false);
		return 0;
	case COMMAND_1516:
		script_assert(false);
		return 0;
	case COMMAND_1517:
		script_assert(false);
		return 0;
	case COMMAND_1518:
		// TODO (?)
		UpdateCompareFlag(true);
		return 0;
	case COMMAND_1519:
		CollectParameters(&m_nIp, 1);
		// TODO (SET_NUMBER_USJ_FOUND?)
		return 0;
	case COMMAND_1520:
		CollectParameters(&m_nIp, 1);
		// TODO (SET_TOTAL_HIDDEN_PACKAGES?)
		return 0;
	case COMMAND_1521:
		script_assert(false);
		return 0;
	case COMMAND_1522:
		script_assert(false);
		return 0;
	case COMMAND_1523:
		script_assert(false);
		return 0;
	case COMMAND_1524:
		script_assert(false);
		return 0;
	case COMMAND_1525:
		script_assert(false);
		return 0;
	case COMMAND_1526:
		script_assert(false);
		return 0;
	case COMMAND_1527:
		script_assert(false);
		return 0;
	case COMMAND_1528:
		script_assert(false);
		return 0;
	case COMMAND_1529:
		script_assert(false);
		return 0;
	case COMMAND_1530:
		script_assert(false);
		return 0;
	case COMMAND_1531:
		script_assert(false);
		return 0;
	case COMMAND_1532:
		script_assert(false);
		return 0;
	case COMMAND_1533:
		script_assert(false);
		return 0;
	case COMMAND_1534:
		script_assert(false);
		return 0;
	case COMMAND_1535:
		script_assert(false);
		return 0;
	case COMMAND_1536:
		script_assert(false);
		return 0;
	case COMMAND_1537:
		script_assert(false);
		return 0;
	case COMMAND_1538:
		script_assert(false);
		return 0;
	case COMMAND_1539:
		//TODO (REGISTER_OUTFIT_CHANGE)
		return 0;
	case COMMAND_1540:
		script_assert(false);
		return 0;
	case COMMAND_1541:
		script_assert(false);
		return 0;
	case COMMAND_1542:
		script_assert(false);
		return 0;
	case COMMAND_1543:
		script_assert(false);
		return 0;
	case COMMAND_1544:
		script_assert(false);
		return 0;
	case COMMAND_1545:
		script_assert(false);
		return 0;
	case COMMAND_1546:
		script_assert(false);
		return 0;
	case COMMAND_1547:
		script_assert(false);
		return 0;
	case COMMAND_1548:
		// TODO (GET_ONFOOT_CAMERA_MODE)
		ScriptParams[0] = 0;
		StoreParameters(&m_nIp, 1);
		return 0;
	case COMMAND_1549:
		CollectParameters(&m_nIp, 1);
		// TODO (SET_ONFOOT_CAMERA_MODE?)
		return 0;
	case COMMAND_1550:
		script_assert(false);
		return 0;
	case COMMAND_1551:
		script_assert(false);
		return 0;
	case COMMAND_1552:
		script_assert(false);
		return 0;
	case COMMAND_1553:
		script_assert(false);
		return 0;
	case COMMAND_1554:
		script_assert(false);
		return 0;
	case COMMAND_1555:
		CollectParameters(&m_nIp, 1);
		// TODO (FREEZE_ONFOOT_CAMERA_MODE?)
		return 0;
	case COMMAND_1556:
		script_assert(false);
		return 0;
	case COMMAND_1557:
		script_assert(false);
		return 0;
	case COMMAND_1558:
		UpdateCompareFlag(false);
		// TODO
		return 0;
	case COMMAND_1559:
		script_assert(false);
		return 0;
	case COMMAND_1560:
		// TODO (IS_E3_BUILD?)
		UpdateCompareFlag(false);
		return 0;
	case COMMAND_1561:
		// TODO (check, SET_FS_DESTROYED_FLAG)
		CTheScripts::FSDestroyedFlag = GetPointerToScriptVariable(&m_nIp, VAR_GLOBAL) - (int32*)CTheScripts::ScriptSpace;
		return 0;
	case COMMAND_1562:
		script_assert(false);
		return 0;
	case COMMAND_1563:
		script_assert(false);
		return 0;
	case COMMAND_1564:
		script_assert(false);
		return 0;
	case COMMAND_1565:
		script_assert(false);
		return 0;
	case COMMAND_1566:
		script_assert(false);
		return 0;
	case COMMAND_1567:
		CollectParameters(&m_nIp, 1);
		// TODO (BUILD_WORLD_GEOMETRY)
		return 0;
	case COMMAND_1568:
		script_assert(false);
		return 0;
	case COMMAND_1569:
		// TODO (IS_MULTIPLAYER_ACTIVE?)
		UpdateCompareFlag(false);
		return 0;
	case COMMAND_1570:
		script_assert(false);
		return 0;
	case COMMAND_1571:
		script_assert(false);
		return 0;
	case COMMAND_1572:
		script_assert(false);
		return 0;
	case COMMAND_1573:
		script_assert(false);
		return 0;
	case COMMAND_1574:
		script_assert(false);
		return 0;
	case COMMAND_1575:
		script_assert(false);
		return 0;
	case COMMAND_1576:
		script_assert(false);
		return 0;
	case COMMAND_1577:
		script_assert(false);
		return 0;
	case COMMAND_1578:
		script_assert(false);
		return 0;
	case COMMAND_1579:
		script_assert(false);
		return 0;
	case COMMAND_1580:
		script_assert(false);
		return 0;
	case COMMAND_1581:
	{
		// TODO (SET_HELP_MESSAGE?)
		wchar* key = CTheScripts::GetTextByKeyFromScript(&m_nIp);
		return 0;
	}
	case COMMAND_1582:
		script_assert(false);
		return 0;
	case COMMAND_1583:
		script_assert(false);
		return 0;
	case COMMAND_1584:
		script_assert(false);
		return 0;
	case COMMAND_1585:
		script_assert(false);
		return 0;
	case COMMAND_1586:
		script_assert(false);
		return 0;
	case COMMAND_1587:
		script_assert(false);
		return 0;
	case COMMAND_1588:
		script_assert(false);
		return 0;
	case COMMAND_1589:
		CollectParameters(&m_nIp, 2);
		// TODO (SWAP_BUILDING?)
		return 0;
	case COMMAND_1590:
		script_assert(false);
		return 0;
	case COMMAND_1591:
		script_assert(false);
		return 0;
	case COMMAND_1592:
		script_assert(false);
		return 0;
	case COMMAND_1593:
		script_assert(false);
		return 0;
	case COMMAND_1594:
		script_assert(false);
		return 0;
	case COMMAND_1595:
		script_assert(false);
		return 0;
	case COMMAND_1596:
		script_assert(false);
		return 0;
	case COMMAND_1597:
		script_assert(false);
		return 0;
	case COMMAND_1598:
		script_assert(false);
		return 0;
	case COMMAND_1599:
		script_assert(false);
		return 0;
	default:
		script_assert(0);
	}
	return -1;
}