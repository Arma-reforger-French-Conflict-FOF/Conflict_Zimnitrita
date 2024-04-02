modded class SCR_VotingBase
{
	override protected bool EvaluateParticipation(int voteCount)
	{
		return
			/*
				Absolute player limit
				With m_iMinVotes = 3, at least 3 players have to cast a vote. 
				If there are fewer than 3 players, total amount of players will be used instead (which means the vote has to be unanimous)
				Examples:
					Players		Votes needed
					1			1
					2			2
					3			3
					4			3
					5			3
					...			...
			*/
//			voteCount >= Math.Max(m_iMinVotes, GetPlayerCount())
			/*
				Relative player limit
				With m_iMinParticipation = 0.5 (50%), at least half of players need to cast a vote.
				Examples:
					Players		Votes needed
					1			1
					2			1
					3			2
					4			2
					5			3
					...			...
			*/
			/*&&*/ (float)(voteCount / GetPlayerCount()) >= m_iMinParticipation;
	}
};