modded class SCR_AIWorld : AIWorld
{
	[Attribute("200", UIWidgets.EditBox, "Amount of AIs that can be in simulation", "0 2000 1", NULL, "AILimits")]
	protected int m_iActiveAILimit;
};