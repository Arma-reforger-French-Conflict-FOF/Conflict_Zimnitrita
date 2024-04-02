modded class SCR_CampaignMilitaryBaseManager
{
	//------------------------------------------------------------------------------------------------
	//! Picks Main Operating Bases from a list of candidates by checking average distance to active control points
	override void SelectHQs(notnull array<SCR_CampaignMilitaryBaseComponent> candidates, notnull array<SCR_CampaignMilitaryBaseComponent> controlPoints, out notnull array<SCR_CampaignMilitaryBaseComponent> selectedHQs)
	{
		int candidatesCount = candidates.Count();

		// If only two HQs are set up, don't waste time with processing
		if (candidatesCount == 2)
		{
			SelectHQsSimple(candidates, selectedHQs);
			return;
		}

		int iterations;
		SCR_CampaignMilitaryBaseComponent bluforHQ;
		SCR_CampaignMilitaryBaseComponent opforHQ;
		array<SCR_CampaignMilitaryBaseComponent> eligibleForHQ;
		vector bluforHQPos;
		
		SCR_CampaignFaction factionBLUFOR = m_Campaign.GetFactionByEnum(SCR_ECampaignFaction.BLUFOR);
		SCR_CampaignFaction factionOPFOR = m_Campaign.GetFactionByEnum(SCR_ECampaignFaction.OPFOR);

		while (!opforHQ && iterations < MAX_HQ_SELECTION_ITERATIONS)
		{
			iterations++;
			eligibleForHQ = {};

			// Pick the blufor HQ at random
			Math.Randomize(-1);
			bluforHQ = candidates.GetRandomElement();
			bluforHQPos = bluforHQ.GetOwner().GetOrigin();

			foreach (SCR_CampaignMilitaryBaseComponent candidate : candidates)
			{
				if (candidate == bluforHQ)
					continue;
				
				if (candidate.GetFaction() == factionBLUFOR)
					continue;

				eligibleForHQ.Insert(candidate);
			}

			Math.Randomize(-1);
			opforHQ = eligibleForHQ.GetRandomElement();
		}
		selectedHQs = {bluforHQ, opforHQ};
	}
}