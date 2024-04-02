modded class SCR_AmbientPatrolSystem : GameSystem
{
	override protected void ProcessSpawnpoint(int spawnpointIndex)
	{
		SCR_AmbientPatrolSpawnPointComponent spawnpoint = m_aPatrols[spawnpointIndex];

		if (!spawnpoint || (spawnpoint.GetMembersAlive() == 0 && !spawnpoint.GetIsSpawned()))
			return;

		ChimeraWorld world = GetWorld();
		WorldTimestamp currentTime = world.GetServerTimestamp();
		if (spawnpoint.GetRespawnTimestamp().Greater(currentTime))
			return;

/*		if (!spawnpoint.GetIsSpawned())
		{
			spawnpoint.SpawnPatrol();
			return;
		}
*/
		bool playersNear;
		bool playersVeryNear;
		bool playersFar = true;
		vector location = spawnpoint.GetOwner().GetOrigin();
		int distance;

		// Define if any player is close enough to spawn or if all players are far enough to despawn
		foreach (IEntity player : m_aPlayers)
		{
			if (!player)
				continue;

			distance = vector.DistanceSq(player.GetOrigin(), location);

			if (distance > m_iDespawnDistanceSq)
				continue;

			playersFar = false;

			if (distance > m_iSpawnDistanceSq)
				continue;

			playersNear = true;

			if (distance > SPAWN_RADIUS_BLOCK_SQ)
				continue;

			playersVeryNear = true;
			break;
		}

		bool isAIOverLimit;
		AIWorld aiWorld = GetGame().GetAIWorld();

		if (aiWorld)
		{
			int maxChars = aiWorld.GetLimitOfActiveAIs();

			if (maxChars <= 0)
				isAIOverLimit = true;
			else
				isAIOverLimit = ((float)aiWorld.GetCurrentNumOfActiveAIs() / (float)maxChars) > spawnpoint.GetAILimitThreshold();
		}

		if (playersNear && !spawnpoint.GetIsSpawned() && !playersVeryNear){
			spawnpoint.SpawnPatrol();
			spawnpoint.SetIsPaused(false);
		}
		
		if (playersNear && !spawnpoint.GetIsPaused() && !spawnpoint.IsGroupActive())
		{
			// Do not spawn the patrol if the AI threshold setting has been reached
			if (isAIOverLimit)
			{
				spawnpoint.SetIsPaused(true);	// Make sure a patrol is not spawned too close to players when AI limit suddenly allows spawning of this group
				return;
			}

			spawnpoint.ActivateGroup();
			return;
		}

		// Delay is used so dying players don't see the despawn happen
		if (spawnpoint.GetIsSpawned() && playersFar && spawnpoint.IsGroupActive())
		{
			WorldTimestamp despawnT = spawnpoint.GetDespawnTimer();

			if (despawnT == 0)
				spawnpoint.SetDespawnTimer(currentTime.PlusMilliseconds(DESPAWN_TIMEOUT));
			else if (currentTime.Greater(despawnT)){
				spawnpoint.DeactivateGroup();
				spawnpoint.DespawnPatrol();
			}
		}
		else
		{
			spawnpoint.SetDespawnTimer(null);
		}
	}
}
