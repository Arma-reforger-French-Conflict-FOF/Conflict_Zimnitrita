modded class SCR_AIGroup : ChimeraAIGroup
{
	//------------------------------------------------------------------------------------------------
	/*
	Returns false when member couldn't be spawned but we should try again
	True otherwise
	*/
	override bool SpawnDelayedGroupMember(int spawnIndex)
	{
		return SpawnGroupMember(
			m_delayedSpawnList.Get(spawnIndex).snapToTerrain,
			m_delayedSpawnList.Get(spawnIndex).index,
			m_delayedSpawnList.Get(spawnIndex).resourceName,
			m_delayedSpawnList.Get(spawnIndex).editMode,
			spawnIndex == -1 // isLast - Gramps changed to -1 from 0
		);
	}
};
