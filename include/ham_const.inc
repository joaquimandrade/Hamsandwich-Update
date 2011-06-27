#if defined _ham_const_included
	#endinput
#endif
#define _ham_const_included

/**
 * Ham return types.
 * -
 * Return these from hooks to disable calling the target function.
 * Numbers match up with fakemeta's FMRES_* for clarity.  They are interchangable.
 * 0 (or no return) is also interpretted as HAM_IGNORED.
 */
#define HAM_IGNORED		1	/**< Calls target function, returns normal value */
#define HAM_HANDLED		2	/**< Tells the module you did something, still calls target function and returns normal value */
#define HAM_OVERRIDE	3	/**< Still calls the target function, but returns whatever is set with SetHamReturn*() */
#define HAM_SUPERCEDE	4	/**< Block the target call, and use your return value (if applicable) (Set with SetHamReturn*()) */

/**
 * A few notes about all of the following functions:
 *   - Not all functions will do as you expect on all mods.
 *     If a function does not do what you would believe it should
 *     DO NOT file a bug report, you will be ignored.
 *
 *   - Passing invalid parameters has potential to crash the server
 *     So be careful, and adequately test!
 *
 *   - All functions take (and pass) a "this" index as the first param.
 *     This is the entity from which the function is being executed on.
 *
 *   - All functions and forwards (eg: {Register,Execute}Ham[B]) require
 *     the mod to have the pev and base keys in addition to the function
 *     keys for the corresponding mod/operating system in hamdata.ini
 *
 *   - Some functions that return booleans may need to be logically ANDed
 *     to get the results desired.  e.g: if (ExecuteHam(Ham_TS_IsObjective, this) & 0x0000FFFF != 0) { // true.. }
 *     because the module will return the full integer value.
 */

enum Ham
{
	/**
	 * Description: 	This is typically called whenever an entity is created. 
	 *					It is the virtual equivilent of spawn from the engine.
	 *					Some mods call this on player spawns too.
	 * Forward params:	function(this)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_Spawn, this);
	 */
	Ham_Spawn = 0, 
	
	/**
	 * Description: 	This is typically called on map change.
	 *					This will typically precache all assets required by the entity.
	 * Forward params:	function(this)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_Precache, this);
	 */
	Ham_Precache,
	
	/**
	 * Description:		Typically this is similar to an engine keyvalue call.
	 *					Use the kvd natives from fakemeta to handle the kvd_handle passed.
	 *					NOTE: Do not pass handle 0 to this! Use get_kvd_handle(0) from fakemeta instead!
	 * Forward params:	function(this, kvd_handle);
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_Keyvalue, this, kvd_handle);
	 */
	Ham_Keyvalue,
	
	/**
	 * Description:		Returns flags for how an entity can be used (FCAP_* constants in hlsdk_const.inc)
	 * Forward params:	function(this)
	 * Return type:		Integer.
	 * Execute params:	ExecuteHam(Ham_ObjectCaps, this);
	 */
	Ham_ObjectCaps,
	
	/**
	 * Description:		Usually called to activate some objects.
	 * Forward params:	function(this)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_Activate, this);
	 */
	Ham_Activate,
	
	/**
	 * Description:		Usually called after the engine call with the same name.
	 * Forward params:	function(this)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_SetObjectCollisionBox, this);
	 */
	Ham_SetObjectCollisionBox,
	
	/**
	 * Description:		Returns an integer number that corresponds with what type of entity this is.
	 * Forward params:	function(this)
	 * Return type:		Integer.
	 * Execute params:	ExecuteHam(Ham_Classify, this);
	 */
	Ham_Classify,
	
	/**
	 * Description:		Typically called when an entity dies to notify any children entities about the death.
	 * Forward params:	function(this, idchild)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_DeathNotice, this, idchild)
	 */
	Ham_DeathNotice,
	
	/**
	 * Description:		Usually called whenever an entity gets attacked by a hitscan (such as a gun) weapon.
	 *					Use the get/set tr2 natives in fakemeta to handle the traceresult data.
	 *					Do not use a handle of 0 as a traceresult in execution, use create_tr2() from Fakemeta
	 *					to pass a custom handle instead.  (Don't forget to free the handle when you're done.)
	 * Forward params:	function(this, idattacker, Float:damage, Float:direction[3], traceresult, damagebits)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_TraceAttack, this, idattacker, Float:damage, Float:direction[3], tracehandle, damagebits);
	 */
	Ham_TraceAttack,
	
	/**
	 * Description:		Usually called whenever an entity takes any kind of damage.
	 *					Inflictor is the entity that caused the damage (such as a gun).
	 *					Attacker is the entity that tirggered the damage (such as the gun's owner).
	 * Forward params:	function(this, idinflictor, idattacker, Float:damage, damagebits);
	 * Return type:		Integer.
	 * Execute params:	ExecuteHam(Ham_TakeDamage, this, idinflictor, idattacker, Float:damage, damagebits);
	 */
	Ham_TakeDamage,
	
	/**
	 * Description:		Usually called whenever an entity gets a form of a heal.
	 * Forward params:	function(this, Float:health, damagebits);
	 * Return type:		Integer.
	 * Execute params:	ExecuteHam(Ham_TakeHealth, this, Float:health, damagebits);
	 */
	Ham_TakeHealth,
	
	/**
	 * Description:		Normally called whenever an entity dies.
	 * Forward params:	function(this, idattacker, shouldgib)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_Killed, this, idattacker, shouldgib);
	 */
	Ham_Killed,
	
	/**
	 * Description:		Normally returns the blood color of the entity.
	 * Forward params:	function(this)
	 * Return type:		Integer.
	 * Execute params:	ExecuteHam(Ham_BloodColor, this)
	 */
	Ham_BloodColor,
	
	/**
	 * Description:		Traces where blood should appear.
	 * Forward params:	function(this, Float:Damage, Float:Direction[3], trace_handle, damagebits);
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_TraceBleed, this, Float:damage, Float:direction[3], trace_handle, damagebits);
	 */
	Ham_TraceBleed,
	
	/**
	 * Description:		Returns whether an entity is activated.
	 * Forward params:	function(this, idActivator);
	 * Return type:		Integer.
	 * Execute params:	ExecuteHam(Ham_IsTriggered, this, idActivator);
	 */
	Ham_IsTriggered,
	
	/**
	 * Description:		Returns the id of the entity if its class is derived off of CBaseMonster, -1 otherwise.
	 * Forward params:	function(this)
	 * Return type:		Entity.
	 * Execute params:	ExecuteHam(Ham_MyMonsterPointer, this);
	 */
	Ham_MyMonsterPointer,
	
	/**
	 * Description:		Returns the id of the entity if its class is derived off of CBaseSquadMonster, -1 otherwise.
	 * Forward params:	function(this)
	 * Return type:		Entity.
	 * Execute params:	ExecuteHam(Ham_MySquadMonsterPointer, this);
	 */
	Ham_MySquadMonsterPointer,
	
	/**
	 * Description:		Returns the toggle state of the entity.
	 * Forward params:	function(this)
	 * Return type:		Integer.
	 * Execute params:	ExecuteHam(Ham_GetToggleState, this);
	 */
	Ham_GetToggleState,
	
	/**
	 * Description:		Typically adds points to the entity.
	 * Forward params:	function(this, points, bool:cangonegative);
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_AddPoints, this, points, bool:cangonegative);
	 */
	Ham_AddPoints,
	
	/**
	 * Description:		Typically adds points to everybody on the entity's team.
	 * Forward params:	function(this, points, bool:cangonegative);
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_AddPointsToTeam, this, points, bool:cangonegative);
	 */
	Ham_AddPointsToTeam,
	
	/**
	 * Description:		Adds an item to the player's inventory.
	 * Forward params:	function(this, idother);
	 * Return type:		Integer.
	 * Execute params:	ExecuteHam(Ham_AddPlayerItem, this, idother);
	 */
	Ham_AddPlayerItem,
	
	/**
	 * Description:		Removes an item to the player's inventory.
	 * Forward params:	function(this, idother);
	 * Return type:		Integer.
	 * Execute params:	ExecuteHam(Ham_RemovePlayerItem, this, idother);
	 */
	Ham_RemovePlayerItem,
	
	/**
	 * Description:		Gives ammo to the entity.
	 * Forward params:	function(this, Amount, const Name[], Max)
	 * Return type:		Integer.
	 * Execute params:	ExecuteHam(Ham_GiveAmmo, this, amount, "type", max);
	 */
	Ham_GiveAmmo,
	
	/**
	 * Description:		Unsure, I believe this is the delay between activation for an entity.
	 * Forward params:	function(this)
	 * Return type:		Float.
	 * Execute params:	ExecuteHam(Ham_GetDelay, this, Float:output)
	 */
	Ham_GetDelay,
	
	/** 
	 * Description:		Whether or not the entity is moving.
	 * Forward params:	function(this);
	 * Return type:		Integer.
	 * Execute params:	ExecuteHam(Ham_IsMoving, this);
	 */
	Ham_IsMoving,
	
	/**
	 * Description:		Unsure.
	 * Forward params:	function(this)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_OverrideReset, this)
	 */
	Ham_OverrideReset,
	
	/**
	 * Description:		Returns the damage decal of the entity for the damage type.
	 * Forward params:	function(this, damagebits)
	 * Return type:		Integer.
	 * Execute params:	ExecuteHam(Ham_DamageDecal, this);
	 */
	Ham_DamageDecal,
	
	/**
	 * Description:		Sets the toggle state of the entity.
	 * Forward params:	function(this, state)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_SetToggleState, this, state);
	 */
	Ham_SetToggleState,
	
	/**
	 * Description:		Not entirely sure what this does.
	 * Forward params:	function(this)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_StartSneaking, this);
	 */
	Ham_StartSneaking,
	
	/**
	 * Description:		Not entirely sure what this does.
	 * Forward params:	function(this)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_StopSneaking, this);
	 */
	Ham_StopSneaking,
	
	/**
	 * Description:		Not entirely sure.
	 * Forward params:	function(this, idOn)
	 * Return type:		Integer (boolean).
	 * Execute params:	ExecuteHam(Ham_OnControls, this, idOn);
	 */
	Ham_OnControls,
	
	/** 
	 * Description:		Whether or not the entity is sneaking.
	 * Forward params:	function(this);
	 * Return type:		Integer (boolean).
	 * Execute params:	ExecuteHam(Ham_IsSneaking, this);
	 */
	Ham_IsSneaking,
	
	/** 
	 * Description:		Whether or not the entity is alive.
	 * Forward params:	function(this);
	 * Return type:		Integer (boolean).
	 * Execute params:	ExecuteHam(Ham_IsAlive, this);
	 */
	Ham_IsAlive,
	
	/** 
	 * Description:		Whether or not the entity uses a BSP model.
	 * Forward params:	function(this);
	 * Return type:		Integer (boolean).
	 * Execute params:	ExecuteHam(Ham_IsBSPModel, this);
	 */
	Ham_IsBSPModel,
	
	/** 
	 * Description:		Whether or not the entity can reflect gauss shots..
	 * Forward params:	function(this);
	 * Return type:		Integer (boolean).
	 * Execute params:	ExecuteHam(Ham_ReflectGauss, this);
	 */
	Ham_ReflectGauss,
	
	/**
	 * Description:		Whether or not the target is the same as the one passed.
	 *					Note the strindex parameter is a string passed that has been allocated by the engine.
	 *					Use fakemeta's EngFunc_SzFromIndex to convert to a normal string, or fakemeta's
	 *					EngFunc_AllocString to create a new string.
	 * Forward params:	function(this, strindex).
	 * Return type:		Integer (boolean).
	 * Execute params:	ExecuteHam(Ham_HasTarget, this, strindex);
	 */
	Ham_HasTarget,
	
	/** 
	 * Description:		Whether or not the entity is in the world.
	 * Forward params:	function(this);
	 * Return type:		Integer (boolean).
	 * Execute params:	ExecuteHam(Ham_IsInWorld, this);
	 */
	Ham_IsInWorld,
	
	/** 
	 * Description:		Whether or not the entity is a player.
	 * Forward params:	function(this);
	 * Return type:		Integer (boolean).
	 * Execute params:	ExecuteHam(Ham_IsPlayer, this);
	 */
	Ham_IsPlayer,
	
	/** 
	 * Description:		Whether or not the entity is a net client.
	 * Forward params:	function(this);
	 * Return type:		Integer (boolean).
	 * Execute params:	ExecuteHam(Ham_IsNetClient, this);
	 */
	Ham_IsNetClient,
	
	/** 
	 * Description:		Get the entity's team id.
	 * Forward params:	function(this);
	 * Return type:		String (string length returned and string byref'd in ExecuteHam).
	 * Execute params:	ExecuteHam(Ham_TeamId, this, buffer[], size);
	 */
	Ham_TeamId,
	
	/**
	 * Description:		Returns the next target of this.
	 * Forward params:	function(this);
	 * Return type:		Entity.
	 * Execute params:	ExecuteHam(Ham_GetNextTarget, this);
	 */
	Ham_GetNextTarget,
	
	/**
	 * Description:		Called whenever an entity thinks.
	 * Forward params:	function(this)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_Think, this);
	 */
	Ham_Think,
	
	/**
	 * Description:		Called whenever two entities touch.
	 * Forward params:	function(this, idother);
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_Touch, this, idother);
	 */
	Ham_Touch,
	
	/**
	 * Description:		Called whenver one entity uses another.
	 * Forward params:	function(this, idcaller, idactivator, use_type, Float:value)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_Use, this, idcaller, idactivator, use_type, Float:value);
	 */
	Ham_Use,
	
	/**
	 * Description:		Normally called whenever one entity blocks another from moving.
	 * Forward params:	function(this, idother);
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_Blocked, this, idother);
	 */
	Ham_Blocked,
	
	/**
	 * Description:		Normally called when a map-based item respawns, such as a health kit or something.
	 * Forward params:	function(this);
	 * Return type:		Entity.
	 * Execute params:	ExecuteHam(Ham_Respawn, this);
	 */
	Ham_Respawn,
	
	/**
	 * Description:		Used in Half-Life to update a monster's owner.
	 * Forward params:	function(this);
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_UpdateOwner, this);
	 */
	Ham_UpdateOwner,
	
	/**
	 * Description:		Normally called whenever a barnacle grabs the entity.
	 * Forward params:	function(this);
	 * Return type:		Integer.
	 * Execute params:	ExecuteHam(Ham_FBecomeProne, this);
	 */
	Ham_FBecomeProne,
	
	/**
	 * Description:		Returns the center of the entity.
	 * Forward params:	function(this);
	 * Return type:		Vector (byref'd in Execute).
	 * Execute params:	ExecuteHam(Ham_Center, this, Float:output[3]);
	 */
	Ham_Center,
	
	/**
	 * Description:		Returns the eye position of the entity.
	 * Forward params:	function(this);
	 * Return type:		Vector (byref'd in Execute).
	 * Execute params:	ExecuteHam(Ham_EyePosition, this, Float:output[3]);
	 */
	Ham_EyePosition,
	
	/**
	 * Description:		Returns the ear position of the entity.
	 * Forward params:	function(this);
	 * Return type:		Vector (byref'd in Execute).
	 * Execute params:	ExecuteHam(Ham_EarPosition, this, Float:output[3]);
	 */
	Ham_EarPosition,
	
	/**
	 * Description:		Position to shoot at.
	 * Forward params:	function(this, Float:srcvector[3]);
	 * Return type:		Vector (byref'd in Execute).
	 * Execute params:	ExecuteHam(Ham_BodyTarget, Float:srcvector[3], Float:returnvector[3])
	 */
	Ham_BodyTarget,
	
	/**
	 * Description:		Returns the illumination of the entity.
	 * Forward params:	function(this)
	 * Return type:		Integer.
	 * Execute params:	ExecuteHam(Ham_Illumination, this);
	 */
	Ham_Illumination,
	
	/**
	 * Description:		Unsure, I assume it is whether or not the other entity is visible to this entity.
	 * Forward params:	function(this, idOther);
	 * Return type:		Integer (boolean).
	 * Execute params:	ExecuteHam(Ham_FVisible, this, idOther);
	 */
	Ham_FVisible,
	
	/**
	 * Description:		Unsure, I assume it is whether or not the target vector is visible to this entity.
	 * Forward params:	function(this, const Float:origin[3]);
	 * Return type:		Integer (boolean).
	 * Execute params:	ExecuteHam(Ham_FVecVisible, this, const Float:origin[3]);
	 */
	Ham_FVecVisible,
	
	Ham_ChangeYaw, /* Need documentation */
	Ham_HasHumanGibs, /* Need documentation */
	Ham_Has_AlienGibs, /* Need documentation */
	Ham_FadeMonster, /* Need documentation */
	Ham_GibMonster, /* Need documentation */
	Ham_BecomeDead, /* Need documentation */
	Ham_IRelationship, /* Need documentation */
	Ham_PainSound, /* Need documentation */
	Ham_ReportAIState, /* Need documentation */
	Ham_MonsterInitDead, /* Need documentation */
	Ham_Look, /* Need documentation */
	Ham_BestVisibleEnemy, /* Need documentation */
	
	/**
	 * Description:		Returns TRUE if the passed ent is in the caller's forward view cone. 
	 *					The dot product is performed in 2d, making the view cone infinitely tall. 
	 * Forward params:	function(this, idOther);
	 * Return type:		Integer (boolean).
	 * Execute params:	ExecuteHam(Ham_FInViewCone, this, idOther);
	 */
	Ham_FInViewCone,

	/**
	 * Description:		Determines the best type of death animation to play.
	 * Forward params:	function(this);
	 * Return type:		Integer (ACT_* constants, see HLDSK. It might different depending the mod).
	 * Execute params:	ExecuteHam(Ham_GetDeathActivity, this);
	 */
	Ham_GetDeathActivity,


	/**
	 * The following functions are not supported by Counter-Strike, The Specialists and Natural Selection mods
	 */

	/**
	 * Description:		-
	 *					This function is not supported by Counter-Strike, The Specialists and Natural Selection mods.
	 * Forward params:	function(this)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_RunAI, this);
	 */
	Ham_RunAI,

	/**
	 * Description:		-
	 *					This function is not supported by Counter-Strike, The Specialists and Natural Selection mods.
	 * Forward params:	function(this)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_MonsterThink, this);
	 */
	Ham_MonsterThink,

	/**
	 * Description:		After a monster is spawned, it needs to be dropped into the world, checked for mobility problems
	 *					and put on the proper path, if any. This function does all of those things after the monster spawns.
	 *					Any initialization that should take place for all monsters goes here.
	 *					This function is not supported by Counter-Strike, The Specialists and Natural Selection mods.
	 * Forward params:	function(this)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_MonsterInit, this);
	 */
	Ham_MonsterInit,

	/**
	 * Description:		Takes a single step towards the next ROUTE location.
	 *					This function is not supported by Counter-Strike, The Specialists and Natural Selection mods.
	 * Forward params:	function(this, Float:interval)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_Move, this, Float:interval);
	 */
	Ham_Move,

	/**
	 * Description:		-
	 *					This function is not supported by Counter-Strike, The Specialists and Natural Selection mods.
	 * Forward params:	function(this, Float:waypointDist)
	 * Return type:		Integer (Boolean).
	 * Execute params:	ExecuteHam(Ham_ShouldAdvanceRoute, this, Float:waypointDist);
	 */
	Ham_ShouldAdvanceRoute,

	/**
	 * Description:		-
	 *					This function is not supported by Counter-Strike, The Specialists and Natural Selection mods.
	 * Forward params:	function(this)
	 * Return type:		Integer (ACT_* constants, see HLDSK. It might different depending the mod).
	 * Execute params:	ExecuteHam(Ham_GetStoppedActivity, this);
	 */
	Ham_GetStoppedActivity,

	/**
	 * Description:		-
	 *					This function is not supported by Counter-Strike, The Specialists and Natural Selection mods.
	 * Forward params:	function(this)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_Stop, this);
	 */
	Ham_Stop,		
		
	/**
	 * Description:		-
	 *					This function is not supported by Counter-Strike, The Specialists and Natural Selection mods.
	 * Forward params:	function(this, Float:dot, Float:dist)
	 * Return type:		Integer (Boolean).
	 * Execute params:	ExecuteHam(Ham_CheckRangeAttack1, this, Float:dot, Float:dist);
	 */
	Ham_CheckRangeAttack1,

	/**
	 * Description:		-
	 *					This function is not supported by Counter-Strike, The Specialists and Natural Selection mods.
	 * Forward params:	function(this, Float:dot, Float:dist)
	 * Return type:		Integer (Boolean).
	 * Execute params:	ExecuteHam(Ham_CheckRangeAttack2, this, Float:dot, Float:dist);
	 */
	Ham_CheckRangeAttack2,

	/**
	 * Description:		-
	 *					This function is not supported by Counter-Strike, The Specialists and Natural Selection mods.
	 * Forward params:	function(this, Float:dot, Float:dist)
	 * Return type:		Integer (Boolean).
	 * Execute params:	ExecuteHam(Ham_CheckMeleeAttack1, this, Float:dot, Float:dist);
	 */
	Ham_CheckMeleeAttack1,

	/**
	 * Description:		-
	 *					This function is not supported by Counter-Strike, The Specialists and Natural Selection mods.
	 * Forward params:	function(this, Float:dot, Float:dist)
	 * Return type:		Integer (Boolean).
	 * Execute params:	ExecuteHam(Ham_CheckMeleeAttack2, this, Float:dot, Float:dist);
	 */
	Ham_CheckMeleeAttack2, 

	/**
	 * Description:		-
	 *					This function is not supported by Counter-Strike, The Specialists and Natural Selection mods.
	 * Forward params:	function(this, Float:dot, Float:dist)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_ScheduleChange, this, Float:dot, Float:dist);
	 */
	Ham_ScheduleChange,

	/**
	 * Description:		Determines whether or not the monster can play the scripted sequence or AI sequence that is
	 *					trying to possess it. If DisregardState is set, the monster will be sucked into the script 
	 *					no matter what state it is in. ONLY Scripted AI ents should allow this.
	 *					This function is not supported by Counter-Strike, The Specialists and Natural Selection mods.
	 * Forward params:	function(this, bool:disregardState, interruptLevel);
	 * Return type:		Integer (Boolean).
	 * Execute params:	ExecuteHam(Ham_CanPlaySequence, this, bool:disregardState, interruptLevel );
	 */
	Ham_CanPlaySequence,

	/**
	 * Description:		-
	 *					This function is not supported by Counter-Strike, The Specialists and Natural Selection mods.
	 * Forward params:	function(this, bool:disregardState);
	 * Return type:		Integer (Boolean).
	 * Execute params:	ExecuteHam(Ham_CanPlaySentence, this, bool:disregardState );
	 */
	Ham_CanPlaySentence,

	/**
	 * Description:		-
	 *					This function is not supported by Counter-Strike, The Specialists and Natural Selection mods.
	 * Forward params:	function(this, const sentence[], Float:duration, Float:volume, Float:attenuation);
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_PlaySentence, this, const sentence[], Float:duration, Float:volume, Float:attenuation );
	 */
	Ham_PlaySentence,

	/**
	 * Description:		-
	 *					This function is not supported by Counter-Strike, The Specialists and Natural Selection mods.
	 * Forward params:	function(this, const sentence[], Float:duration, Float:volume, Float:attenuation, bool:concurrent, idListener);
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_PlaySentence, this, const sentence[], Float:duration, Float:volume, Float:attenuation, bool:concurrent, idListener );
	 */
	Ham_PlayScriptedSentence,

	/**
	 * Description:		-
	 *					This function is not supported by Counter-Strike, The Specialists and Natural Selection mods.
	 * Forward params:	function(this);
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_SentenceStop, this);
	 */
	Ham_SentenceStop,

	/**
	 * Description:		Surveys the Conditions information available and finds the best new state for a monster.
	 *					This function is not supported by Counter-Strike, The Specialists and Natural Selection mods.
	 * Forward params:	function(this);
	 * Return type:		Integer. (MONSTERSTATE_* constants. See HLSDK.)
	 * Execute params:	ExecuteHam(Ham_GetIdealState, this);
	 */
	Ham_GetIdealState,

	/**
	 * Description:		-
	 *					This function is not supported by Counter-Strike, The Specialists and Natural Selection mods.
	 * Forward params:	function(this, newActivity);
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_SetActivity, this, newActivity);
	 */
	Ham_SetActivity,

	/**
	 * Description:		Part of the condition collection process gets and stores data and conditions 
	 *					pertaining to a monster's enemy. Returns TRUE if Enemy LKP was updated.
	 *					This function is not supported by Counter-Strike, The Specialists and Natural Selection mods.
	 * Forward params:	function(this, idEnemy);
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_CheckEnemy, this, idEnemy);
	 */
	Ham_CheckEnemy,

	/**
	 * Description:		Allows each sequence to have a different turn rate associated with it.
	 *					This function is not supported by Counter-Strike, The Specialists and Natural Selection mods.
	 * Forward params:	function(this);
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_SetYawSpeed, this);
	 */
	Ham_SetYawSpeed,

	/**
	 * Description:		Tries to build a route as close to the target as possible, even if there isn't a path to the final point.
	 *					If supplied, search will return a node at least as far away as MinDist from vecThreat, but no farther than minDist.
	 *					If maxDist isn't supplied, it defaults to a reasonable value.
	 *					This function is not supported by Counter-Strike, The Specialists and Natural Selection mods.
	 * Forward params:	function(this, Float:threat[3], const Float:viewOffset[3], Float:minDist, Float:maxDist);
	 * Return type:		Integer (Boolean).
	 * Execute params:	ExecuteHam(Ham_BuildNearestRoute, this, const Float:threat[3], const Float:viewOffset[3], Float:minDist, Float:maxDist);
	 */
	Ham_BuildNearestRoute,

	/**
	 * Description:		Tries to find a nearby node that will hide the caller from its enemy. 
	 *					If supplied, search will return a node at least as far away as MinDist from vecThreat, but no farther than minDist.
	 *					If maxDist isn't supplied, it defaults to a reasonable value.
	 *					This function is not supported by Counter-Strike, The Specialists and Natural Selection mods.
	 * Forward params:	function(this, Float:threat[3], const Float:viewOffset[3], Float:minDist, Float:maxDist);
	 * Return type:		Integer (Boolean).
	 * Execute params:	ExecuteHam(Ham_FindCover, this, const Float:threat[3], const Float:viewOffset[3], Float:minDist, Float:maxDist);
	 */
	Ham_FindCover,

	/**
	 * Description:		-
	 *					This function is not supported by Counter-Strike, The Specialists and Natural Selection mods.
	 * Forward params:	function(this);
	 * Return type:		Float.
	 * Execute params:	ExecuteHam(Ham_CoverRadius, this);
	 */
	Ham_CoverRadius,

	/**
	 * Description:		Prequalifies a monster to do more fine checking of potential attacks.
	 *					This function is not supported by Counter-Strike, The Specialists and Natural Selection mods.
	 * Forward params:	function(this);
	 * Return type:		Integer (Boolean).
	 * Execute params:	ExecuteHam(Ham_FCanCheckAttacks, this);
	 */
	Ham_FCanCheckAttacks,

	/**
	 * Description:		-
	 *					This function is not supported by Counter-Strike, The Specialists and Natural Selection mods.
	 * Forward params:	function(this);
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_CheckAmmo, this);
	 */
	Ham_CheckAmmo,

	/**
	 * Description:		Before a set of conditions is allowed to interrupt a monster's schedule, this function removes
	 *					conditions that we have flagged to interrupt the current schedule, but may not want to interrupt
	 *					the schedule every time. (Pain, for instance)
	 *					This function is not supported by Counter-Strike, The Specialists and Natural Selection mods.
	 * Forward params:	function(this);
	 * Return type:		Integer.
	 * Execute params:	ExecuteHam(Ham_IgnoreConditions, this);
	 */
	Ham_IgnoreConditions,

	/**
	 * Description:		Tells use whether or not the monster cares about the type of Hint Node given.
	 *					This function is not supported by Counter-Strike, The Specialists and Natural Selection mods.
	 * Forward params:	function(this, hint);
	 * Return type:		Integer (Boolean).
	 * Execute params:	ExecuteHam(Ham_FValidateHintType, this, hint);
	 */
	Ham_FValidateHintType,

	/**
	 * Description:		-
	 *					This function is not supported by Counter-Strike, The Specialists and Natural Selection mods.
	 * Forward params:	function(this);
	 * Return type:		Integer (Boolean).
	 * Execute params:	ExecuteHam(Ham_FValidateHintType, this);
	 */
	Ham_FCanActiveIdle,

	/**
	 * Description:		Returns a bit mask indicating which types of sounds this monster regards. 
	 *					In the base class implementation, monsters care about all sounds, but no scents.
	 *					This function is not supported by Counter-Strike, The Specialists and Natural Selection mods.
	 * Forward params:	function(this);
	 * Return type:		Integer.
	 * Execute params:	ExecuteHam(Ham_ISoundMask, this);
	 */
	Ham_ISoundMask,

	/**
	 * Description:		-
	 *					This function is not supported by Counter-Strike, The Specialists and Natural Selection mods.
	 * Forward params:	function(this);
	 * Return type:		Float.
	 * Execute params:	ExecuteHam(Ham_HearingSensitivity, this);
	 */
	Ham_HearingSensitivity,

	/**
	 * Description:		Called by Barnacle victims when the barnacle pulls their head into its mouth.
	 *					This function is not supported by Counter-Strike, The Specialists and Natural Selection mods.
	 * Forward params:	function(this, idBarnacle);
	 * Return type:		Float.
	 * Execute params:	ExecuteHam(Ham_BarnacleVictimBitten, this, idBarnacle);
	 */
	Ham_BarnacleVictimBitten,

	/**
	 * Description:		Called by barnacle victims when the host barnacle is killed.
	 *					This function is not supported by Counter-Strike, The Specialists and Natural Selection mods.
	 * Forward params:	function(this);
	 * Return type:		Float.
	 * Execute params:	ExecuteHam(Ham_BarnacleVictimReleased, this);
	 */
	Ham_BarnacleVictimReleased,

	/**
	 * Description:		-
	 *					This function is not supported by Counter-Strike, The Specialists and Natural Selection mods.
	 * Forward params:	function(this);
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_PrescheduleThink, this);
	 */
	Ham_PrescheduleThink,

	/**
	 * Description:		-
	 *					This function is not supported by Counter-Strike, The Specialists and Natural Selection mods.
	 * Forward params:	function(this);
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_DeathSound, this);
	 */
	Ham_DeathSound,

	/**
	 * Description:		-
	 *					This function is not supported by Counter-Strike, The Specialists and Natural Selection mods.
	 * Forward params:	function(this);
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_AlertSound, this);
	 */
	Ham_AlertSound,

	/**
	 * Description:		-
	 *					This function is not supported by Counter-Strike, The Specialists and Natural Selection mods.
	 * Forward params:	function(this);
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_IdleSound, this);
	 */
	Ham_IdleSound,

	/**
	 * Description:		Unsure.
	 * Forward params:	function(this)
	 * Return type:		None.
	 * Execute Params:	ExecuteHam(Ham_StopFollowing, this);
	 */
	Ham_StopFollowing,


	/**
	 * Players have all the attributes of normal entities, in addition to these.
	 */
	
	/**
	 * Description:		Typically called every frame when a player has jump held.
	 * Forward params:	function(this)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_Player_Jump, this);
	 */
	Ham_Player_Jump,
	
	/**
	 * Description:		Typically called every frame when a player has duck held.
	 * Forward params:	function(this)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_Player_Duck, this);
	 */
	Ham_Player_Duck,
	
	/**
	 * Description:		Typically called every frame during PlayerPreThink engine call.
	 * Forward params:	function(this)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_Player_PreThink, this);
	 */
	Ham_Player_PreThink,
	
	/**
	 * Description:		Typically called every frame during PlayerPostThink engine call.
	 * Forward params:	function(this)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_Player_PostThink, this);
	 */
	Ham_Player_PostThink,
	
	/**
	 * Description:		Returns a vector that tells the gun position.
	 * Forward params:	function(this)
	 * Return type:		Vector, byreffed in execute.
	 * Execute params:	ExecuteHam(Ham_Player_GetGunPosition, this, Float:output[3]);
	 */
	Ham_Player_GetGunPosition,
	
	/**
	 * Description:		Whether or not the player should fade on death.
	 * Forward param:	function(this)
	 * Return type:		Integer (boolean).
	 * Execute params:	ExecuteHam(Ham_Player_ShouldFadeOnDeath, this);
	 */
	Ham_Player_ShouldFadeOnDeath,
	
	/**
	 * Description:		Called whenever an impulse command is executed.
	 * Forward param:	function(this)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_Player_ImpulseComands, this);
	 */
	Ham_Player_ImpulseCommands,
	
	/**
	 * Description:		Updates the client's data for hud changes (such as ammo).  Usually called every frame.
	 * Forward param:	function(this)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_Player_UpdateClientData, this);
	 */
	Ham_Player_UpdateClientData,
	

	/**
	 * Items have all the attributes of normal entities in addition to these.
	 */
	 
	/**
	 * Description:		Adds the item to the player.
	 * Forward params:	function(this, idPlayer);
	 * Return type:		Integer (boolean).
	 * Execute params:	ExecuteHam(Ham_Item_AddToPlayer, this, idPlayer);
	 */
	Ham_Item_AddToPlayer,
	
	/**
	 * Description:		Unsure.
	 * Forward params:	function(this, idOriginal);
	 * Return type:		Integer (boolean).
	 * Execute params:	ExecuteHam(Ham_Item_AddDuplicate, this, idOriginal);
	 */
	Ham_Item_AddDuplicate,
	
	/**
	 * Description:		Whether or not this entity can be deployed.
	 * Forward params:	function(this);
	 * Return type:		Integer (boolean).
	 * Execute params:	ExecuteHam(Ham_Item_CanDeploy, this);
	 */
	Ham_Item_CanDeploy,
	
	/**
	 * Description:		Deploys the entity (usually a weapon).
	 * Forward params:	function(this);
	 * Return type:		Integer (boolean).
	 * Execute params:	ExecuteHam(Ham_Item_Deploy, this);
	 */
	Ham_Item_Deploy,
	
	/**
	 * Description:		Whether or not the entity can be holstered.
	 * Forward params:	function(this);
	 * Return type:		Integer (boolean).
	 * Execute params:	ExecuteHam(Ham_Item_CanHolster, this);
	 */
	Ham_Item_CanHolster,
	
	/**
	 * Description:		Whether or not the entity (usually weapon) can be holstered.
	 * Forward params:	function(this)
	 * Return type:		Integer (boolean).
	 * Execute params:	ExecuteHam(Ham_Item_Holster, this);
	 */
	Ham_Item_Holster,
	
	/**
	 * Description:		Updates the HUD info about this item.
	 * Forward params:	function(this);
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_UpdateItemInfo, this);
	 */
	Ham_Item_UpdateItemInfo,
	
	/**
	 * Description:		Called each frame for an item, normally only on active items.
	 * Forward params:	function(this)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_Item_PreFrame, this);
	 */
	Ham_Item_PreFrame,
	
	/**
	 * Description:		Called each frame for an item, normally only on active items.
	 * Forward params:	function(this)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_Item_PostFrame, this);
	 */
	Ham_Item_PostFrame,
	
	/**
	 * Description:		Called when an item gets dropped, normally on death only.
	 * Forward params:	function(this)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_Item_Drop, this);
	 */
	Ham_Item_Drop,
	
	/**
	 * Description:		Normally called when an item gets deleted.
	 * Forward params:	function(this)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_Item_Kill, this);
	 */
	Ham_Item_Kill,
	
	/**
	 * Description:		Called when an entity starts being attached to (normally invisible and "following") a player.
	 * Forward params:	function(this, idPlayer)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_Item_AttachToPlayer, this, idPlayer)
	 */
	Ham_Item_AttachToPlayer,
	
	/**
	 * Description:		Returns the ammo index of the item.
	 * Forward params:	function(this)
	 * Return type:		Integer.
	 * Execute params:	ExecuteHam(Ham_Item_PrimaryAmmoIndex, this);
	 */
	Ham_Item_PrimaryAmmoIndex,
	
	/**
	 * Description:		Returns the secondary ammo index of the item.
	 * Forward params:	function(this)
	 * Return type:		Integer.
	 * Execute params:	ExecuteHam(Ham_Item_SecondaryAmmoIndex, this);
	 */
	Ham_Item_SecondaryAmmoIndex,
	
	/**
	 * Description:		Updates item data for the client.
	 * Forward params:	function(this, idPlayer)
	 * Return type:		Integer.
	 * Execute params:	ExecuteHam(Ham_Item_UpdateClientData, this, idPlayer);
	 */
	Ham_Item_UpdateClientData,
	
	/**
	 * Description:		Returns the entity index if the item is a weapon, -1 otherwise.
	 * Forward params:	function(this)
	 * Return type:		Entity.
	 * Execute Params:	ExecuteHam(Ham_Item_GetWeaponPtr, this)
	 */
	Ham_Item_GetWeaponPtr,
	
	/**
	 * Description:		Returns the item slot for the item.
	 * Forward params:	function(this)
	 * Return type:		Integer.
	 * Execute Params:	ExecuteHam(Ham_Item_ItemSlot, this)
	 */
	Ham_Item_ItemSlot,
	
	
	/**
	 * Weapons have all the attributes to Ham_Item_*, in addition to these.
	 */
	 
	/**
	 * Description:		Gets ammo from the target weapon.
	 * Forward params:	function(this, idTarget)
	 * Return type:		Integer.
	 * Execute Params:	ExecuteHam(Ham_Weapon_ExtractAmmo, this, idTarget)
	 */
	Ham_Weapon_ExtractAmmo,
	
	/**
	 * Description:		Gets clip ammo from the target weapon.
	 * Forward params:	function(this, idTarget)
	 * Return type:		Integer.
	 * Execute Params:	ExecuteHam(Ham_Weapon_ExtractAmmo, this, idTarget)
	 */
	Ham_Weapon_ExtractClipAmmo,
	
	/**
	 * Description:		Unsure.
	 * Forward params:	function(this)
	 * Return type:		Integer (boolean).
	 * Execute params:	ExecuteHam(Ham_Weapon_AddWeapon, this);
	 */
	Ham_Weapon_AddWeapon,
	
	/**
	 * Description:		Plays the weapon's empty sound.
	 * Forward params:	function(this)
	 * Return type:		Integer (boolean).
	 * Execute params:	ExecuteHam(Ham_Weapon_PlayEmptySound, this);
	 */
	Ham_Weapon_PlayEmptySound,
	
	/**
	 * Description:		Sets the weapon so that it can play empty sound again.
	 * Forward params:	function(this)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_Weapon_ResetEmptySound, this);
	 */
	Ham_Weapon_ResetEmptySound,
	
	/**
	 * Description:		Sends an animation event for the weapon.
	 * Forward params:	function(this, iAnim, skiplocal, body);
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_Weapon_SendWeaponAnim, this, iAnim, skiplocal, body);
	 */
	Ham_Weapon_SendWeaponAnim,
	
	/**
	 * Description:		Whether or not the weapon is usable (has ammo, etc.)
	 * Forward params:	function(this)
	 * Return type:		Integer (boolean).
	 * Execute params:	ExecuteHam(Ham_Weapon_IsUsable, this)
	 */
	Ham_Weapon_IsUsable,
	
	/**
	 * Description:		Called when the main attack of a weapon is triggered.
	 * Forward params:	function(this)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_Weapon_PrimaryAttack, this);
	 */
	Ham_Weapon_PrimaryAttack,
	
	/**
	 * Description:		Called when the secondary attack of a weapon is triggered.
	 * Forward params:	function(this)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_Weapon_SecondaryAttack, this);
	 */
	Ham_Weapon_SecondaryAttack,
	
	/**
	 * Description:		Called when the weapon is reloaded.
	 * Forward params:	function(this)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_Weapon_Reload, this);
	 */
	Ham_Weapon_Reload,
	
	/**
	 * Description:		Displays the idle animation for the weapon.
	 * Forward params:	function(this)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_Weapon_WeaponIdle, this);
	 */
	Ham_Weapon_WeaponIdle,
	
	/**
	 * Description:		There is no more ammo for this gun, so switch to the next best one.
	 * Forward params:	function(this)
	 * Return type:		None.
	 * ExecuteParams:	ExecuteHam(Ham_Weapon_RetireWeapon, this)
	 */
	Ham_Weapon_RetireWeapon,
	
	/**
	 * Description:		Whether or not the weapon should idle.
	 * Forward params:	function(this)
	 * Return type:		Integer (boolean).
	 * Execute Params:	ExecuteHam(Ham_Weapon_ShouldWeaponIdle, this)
	 */
	Ham_Weapon_ShouldWeaponIdle,
	
	/**
	 * Description:		Not sure.
	 * Forward params:	function(this)
	 * Return type:		Integer (boolean).
	 * Execute params:	ExecuteHam(Ham_Weapon_UseDecrement, this);
	 */
	Ham_Weapon_UseDecrement,
	 
	/**
	 * Description:		-
	 * Forward params:	function(this, someboolvalue)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_TS_BreakableRespawn, this, someboolvalue);
	 */
	Ham_TS_BreakableRespawn,
	
	/**
	 * Description:		-
	 * Forward params:	function(this)
	 * Return type:		Integer (boolean)
	 * Execute params:	ExecuteHam(Ham_TS_CanUsedThroughWalls, this);
	 */
	Ham_TS_CanUsedThroughWalls,
	
	/**
	 * Description:		Unsure - this was removed in TS 3.0 (and thus is deprecated).
	 * Forward params:	function(this)
	 * Return type:		Integer (I think...)
	 * Execute params:	ExecuteHam(Ham_TS_RespawnWait, this);
	 */
	Ham_TS_RespawnWait,
	
	/**
	 * Description:		This is called on a map reset for most map based entities.
	 * Forward params:	function(this);
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_CS_Restart, this);
	 */
	Ham_CS_Restart,
	
	/**
	 * Description:		Respawn function for players/bots only! Do not use this on non player/bot entities!
	 * Forward params:	function(this);
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_CS_RoundRespawn, this);
	 */
	Ham_CS_RoundRespawn,
	/**
	 * Description:		Whether or not the player can drop the specified item.
	 * Forward params:	function(this)
	 * Return type:		Integer
	 * Execute params:	ExecuteHam(Ham_CS_Item_CanDrop, this);
	 */
	Ham_CS_Item_CanDrop,
	
	/**
	 * Description:		Gets the maximum speed for whenever a player has the item deployed.
	 * Forward params:	function(this);
	 * Return type:		Float, byrefed in execute.
	 * Execute params:	ExecuteHam(Ham_CS_Item_GetMaxSpeed, this, Float:output);
	 */
	Ham_CS_Item_GetMaxSpeed,
	
	/**
	 * Description:		Sends an animation event for the weapon. skiplocal is 1 if client is predicting weapon animations.
	 * Forward params:	function(this, iAnim, skiplocal);
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_CS_Weapon_SendWeaponAnim, this, iAnim, skiplocal);
	 */
	Ham_CS_Weapon_SendWeaponAnim,
	
	/**
	 * Description:		Resets the player's max speed.
	 * Forward params:	function(this);
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_CS_Player_ResetMaxSpeed, this);
	 */
	Ham_CS_Player_ResetMaxSpeed,
	
	/**
	 * Description:		Whether or not the player is a bot.
	 * Forward params:	function(this);
	 * Return type:		Integer (boolean).
	 * Execute params:	ExecuteHam(Ham_CS_Player_IsBot, this);
	 */
	Ham_CS_Player_IsBot,
	
	/**
	 * Description:		Returns a vector that tells the autoaim direction.
	 *					Set crosshair position to point to enemey if sv_aim is 1.
	 * Forward params:	function(this, Float:delta)
	 * Return type:		Vector, byreffed in execute.
	 * Execute params:	ExecuteHam(Ham_CS_Player_GetAutoaimVector, this, Float:delta, Float:output[3]);
	 */
	Ham_CS_Player_GetAutoaimVector,
	
	/**
	 * Description:		Whether or not the player is being flashing. (flashbang grenade explosion)
	 *					blindTime is the time you are considered as being blind. (holdTime * 0.33). Used it seems only by CS bots.
	 * Forward params:	function(this, Float:blindTime, Float:duration, Float:holdTime, int alpha );
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_CS_Player_Blind, this, Float:blindTime, Float:duration, Float:holdTime, int alpha );
	 */
	Ham_CS_Player_Blind,
	
	/**
	 * Description:		Whether or not the player is touching a weapon on the ground.
	 * Forward params:	function(this, entityid);
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_CS_Player_OnTouchingWeapon, this, entityid);
	 */
	Ham_CS_Player_OnTouchingWeapon,
	
	/**
	 * Description:		I assume this spawns players at the start of a new round.
	 * Forward params:	function(this)
	 * Return type:		None.
	 * Execute Params:	ExecuteHam(Ham_DOD_RoundRespawn, this);
	 */
	Ham_DOD_RoundRespawn,
	
	/**
	 * Description:		I assume this spawns entities (like func_breakables) at the start of a new round.
	 * Forward params:	function(this)
	 * Return type:		None.
	 * Execute Params:	ExecuteHam(Ham_DOD_RoundRespawn, this);
	 */
	Ham_DOD_RoundRespawnEnt,
	
	/**
	 * Description:		Unsure.
	 * Forward params:	function(this)
	 * Return type:		None, I think...
	 * Execute params:	ExecuteHam(Ham_DOD_RoundStore, this);
	 */
	Ham_DOD_RoundStore,
	
	/**
	 * Description:		Unsure.
	 * Forward params:	function(this, someintegervalue)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_DOD_AreaSetIndex, this, someintegervalue)
	 */
	Ham_DOD_AreaSetIndex,
	
	/**
	 * Description:		Unsure
	 * Forward params:	function(this, idPlayer)
	 * Return type:		None.
	 * Execute Params:	ExecuteHam(Ham_DOD_AreaSendStatus, this, idPlayer);
	 */
	Ham_DOD_AreaSendStatus,
	
	/**
	 * Description:		Unsure.
	 * Forward params:	function(this)
	 * Return type:		Integer.
	 * Execute Params:	ExecuteHam(Ham_DOD_GetState, this);
	 */
	Ham_DOD_GetState,
	
	/**
	 * Description:		Unsure.
	 * Forward params:	function(this, idtarget)
	 * Return type:		Integer.
	 * Execute Params:	ExecuteHam(Ham_DOD_GetStateEnt, this, idtarget);
	 */
	Ham_DOD_GetStateEnt,

	/**
	 * Description:		Unsure.
	 * Forward params:	function(this)
	 * Return type:		Integer.
	 * Execute Params:	ExecuteHam(Ham_DOD_SetScriptReset, this);
	 */
	Ham_DOD_SetScriptReset,

	/**
	 * Description:		Whether or not a player can drop this item.
	 * Forward params:	function(this)
	 * Return type:		Integer (boolean).
	 * Execute Params:	ExecuteHam(Ham_DOD_Item_CanDrop, this);
	 */
	Ham_DOD_Item_CanDrop,
	
	Ham_DOD_Item_SpawnDeploy,
	Ham_DOD_Item_SetDmgTime,
	Ham_DOD_Item_DropGren,
	Ham_DOD_Weapon_IsUseable,
	Ham_DOD_Weapon_Aim,
	Ham_DOD_Weapon_flAim,
	Ham_DOD_Weapon_RemoveStamina,
	Ham_DOD_Weapon_ChangeFOV,
	Ham_DOD_Weapon_ZoomOut,
	Ham_DOD_Weapon_ZoomIn,
	Ham_DOD_Weapon_GetFOV,
	Ham_DOD_Weapon_IsWaterSniping, /* PlayerIsWaterSniping (had to truncate the name) */
	Ham_DOD_Weapon_UpdateZoomSpeed,
	Ham_DOD_Weapon_Special,
	
	/** 
	 * Description:		Get the item name.
	 * Forward params:	function(this);
	 * Return type:		String (string length returned and string byref'd in ExecuteHam).
	 * Execute params:	ExecuteHam(Ham_TFC_DB_GetItemName, this, buffer[], size);
	 */
	Ham_TFC_DB_GetItemName,

	/**
	 * Description:		Unsure.
	 * Forward params:	function(this, iduser)
	 * Return type:		Integer.
	 * Execute params:	ExecuteHam(Ham_TFC_EngineerUse, this, iduser)
	 */
	Ham_TFC_EngineerUse,
	
	/**
	 * Description:		Unsure.
	 * Forward params:	function(this)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_TFC_Finished, this);
	 */
	Ham_TFC_Finished,
	
	/**
	 * Description:		Unsure.
	 * Forward params:	function(this, entityid, Float:floata, Float:floatb)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_TFC_EmpExplode, this, entityid, Float:floata, Float:floatb)
	 */
	Ham_TFC_EmpExplode,
	
	/**
	 * Description:		Unsure.
	 * Forward params:	function(this, Float:floata, Float:floatb)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_TFC_CalcEmpDmgRad, this, Float:floata, Float:floatb)
	 */
	Ham_TFC_CalcEmpDmgRad,
	
	/**
	 * Description:		Unsure.
	 * Forward params:	function(this, entityid)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_TFC_TakeEmpBlast, this, entityid);
	 */
	Ham_TFC_TakeEmpBlast,
	
	/**
	 * Description:		Unsure.
	 * Forward params:	function(this)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_TFC_EmpRemove, this);
	 */
	Ham_TFC_EmpRemove,
	
	/**
	 * Description:		Unsure.
	 * Forward params:	function(this, entityid, Float:floata)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_TFC_TakeConcussionBlast, this, entityid, Float:floata);
	 */
	Ham_TFC_TakeConcussionBlast,
	
	/**
	 * Description:		Unsure.
	 * Forward params:	function(this, entityid)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_TFC_Concuss, this, entityid);
	 */
	Ham_TFC_Concuss,

	/**
	 * Description:		This entity is exploding, or otherwise needs to inflict damage upon entities within a certain range.
	 * Forward params:	function(this, inflictorId, attackerId, Float:damage, classIgnore, bitsDamageType)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_TFC_RadiusDamage, this, inflictorId, attackerId, Float:damage, classIgnore, bitsDamageType);
	 */
	Ham_TFC_RadiusDamage,

	/**
	 * Description:		This entity is exploding, or otherwise needs to inflict damage upon entities within a certain range.
	 * Forward params:	function(this, const Float:source[3], inflictorId, attackerId, Float:damage, classIgnore, bitsDamageType)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_TFC_RadiusDamage2, this, const Float:source[3], inflictorId, attackerId, Float:damage, classIgnore, bitsDamageType);
	 */
	Ham_TFC_RadiusDamage2,
	
	/**
	 * Description:		Unsure.
	 *					Is only in ESF Open Beta.
	 * Forward params:	function(this)
	 * Return type:		Integer (boolean).
	 * Execute params:	ExecuteHam(Ham_ESF_IsEnvModel, this);
	 */
	Ham_ESF_IsEnvModel, 
	
	/**
	 * Description:		Unsure.
	 *					Is only in ESF Open Beta.
	 * Forward params:	function(this, entityida, entityidb, Float:floata, Float:floatb, dmgbits)
	 * Return type:		Integer.
	 * Execute params:	ExecuteHam(Ham_ESF_TakeDamage2, this, entityida, entityidb, Float:floata, Float:floatb, dmgbits);
	 */
	Ham_ESF_TakeDamage2,

	/**
	 * Description:		Unsure.
	 * Forward params:	function(this)
	 * Return type:		Integer.
	 * Execute params:	ExecuteHam(Ham_ESF_Weapon_HolsterWhenMeleed, this);
	 */
	Ham_ESF_Weapon_HolsterWhenMeleed,
	
	/**
	 * Description:		Returns how many points each entity is worth.
	 * Forward params:	function(this)
	 * Return type:		Integer.
	 * Execute params:	ExecuteHam(Ham_NS_GetPointValue, this);
	 */
	Ham_NS_GetPointValue,
	
	/**
	 * Description:		Unsure.  Probably awards this with the killing of idvictim.
	 * Forward params:	function(this, idvictim)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_NS_AwardKill, this, idvictim);
	 */
	Ham_NS_AwardKill,
	
	/**
	 * Description:		Unsure, probably whenever an entity resets after a new round.
	 * Forward params:	function(this)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_NS_ResetEntity, this);
	 */
	Ham_NS_ResetEntity,
	
	/**
	 * Description:		Unsure.
	 * Forward params:	function(this)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_NS_UpdateOnRemove, this)
	 */
	Ham_NS_UpdateOnRemove,

	/**
	 * Description:		-
	 * Forward params:	function(this, constroller, Float:value)
	 * Return type:		Float.
	 * Execute params:	ExecuteHam(Ham_SetBoneController, this, constroller, Float:value)
	 */
	Ham_NS_SetBoneController,

	/**
	 * Description:		-
	 * Forward params:	function(this)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_SetBoneController, this)
	 */
	Ham_NS_SaveDataForReset,
	
	/**
	 * Description:		-
	 * Forward params:	function(this)
	 * Return type:		Integer.
	 * Execute params:	ExecuteHam(Ham_NS_GetHull, this)
	 */
	Ham_NS_GetHull,

	/**
	 * Description:		-
	 * Forward params:	function(this)
	 * Return type:		Float.
	 * Execute params:	ExecuteHam(Ham_NS_GetMaxWalkSpeed, this)
	 */
	Ham_NS_GetMaxWalkSpeed,

	/**
	 * Description:		-
	 * Forward params:	function(this, const teamID[])
	 * Return type:		Integer.
	 * Execute params:	ExecuteHam(Ham_NS_SetTeamID, this, const teamID[])
	 */
	Ham_NS_SetTeamID,

	/**
	 * Description:		-
	 * Forward params:	function(this)
	 * Return type:		Integer.
	 * Execute params:	ExecuteHam(Ham_NS_GetEffectivePlayerClass, this)
	 */
	Ham_NS_GetEffectivePlayerClass,

	/**
	 * Description:		-
	 * Forward params:	function(this)
	 * Return type:		Integer.
	 * Execute params:	ExecuteHam(Ham_NS_GetAuthenticationMask, this)
	 */
	Ham_NS_GetAuthenticationMask,

	/**
	 * Description:		-
	 * Forward params:	function(this)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_NS_EffectivePlayerClassChanged, this)
	 */
	Ham_NS_EffectivePlayerClassChanged,

	/**
	 * Description:		-
	 * Forward params:	function(this)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_NS_NeedsTeamUpdate, this)
	 */
	Ham_NS_NeedsTeamUpdate,

	/**
	 * Description:		-
	 * Forward params:	function(this)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_NS_SendTeamUpdate, this)
	 */
	Ham_NS_SendTeamUpdate,

	/**
	 * Description:		-
	 * Forward params:	function(this)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_NS_SendWeaponUpdate, this)
	 */
	Ham_NS_SendWeaponUpdate,

	/**
	 * Description:		-
	 * Forward params:	function(this, idOther)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_NS_InitPlayerFromSpawn, this, idOther)
	 */
	Ham_NS_InitPlayerFromSpawn,

	/**
	 * Description:		-
	 * Forward params:	function(this)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_NS_PackDeadPlayerItems, this)
	 */
	Ham_NS_PackDeadPlayerItems,

	
	/** Virtual functions added to TS in TS 3 */
	
	/**
	 * Description:		Unsure.
	 * Forward params:	function(this)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_TS_GiveSlowMul, this)
	 */
	Ham_TS_GiveSlowMul,
	
	/**
	 * Description:		Unsure.  The second paramater is actually a char.
	 * Forward params:	function(this, Float:someval, someotherval)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_TS_GoSlow, this, Float:someval, someotherval)
	 */
	Ham_TS_GoSlow,
	
	/**
	 * Description:		Probably returns true if the user is in slow mo.
	 * Forward params:	function(this)
	 * Return type:		Integer (boolean).
	 * Execute params:	ExecuteHam(Ham_TS_InSlow, this)
	 */
	Ham_TS_InSlow,
	
	/**
	 * Description:		Returns true if the entity is an objective.
	 * Forward params:	function(this)
	 * Return type:		Integer (boolean).
	 * Execute params:	ExecuteHam(Ham_TS_IsObjective, this)
	 */
	Ham_TS_IsObjective,
	
	/**
	 * Description:		Unsure.
	 * Forward params:	function(this, bool:someval)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_TS_EnableObjective, this, bool:someval)
	 */
	Ham_TS_EnableObjective,
	
	/**
	 * Description:		Probably called when the engine call to OnEntFreePrivateData is called (the entity destructor.)
	 * Forward params:	function(this)
	 * Return type:		None.
	 * Execute params:	ExecuteHam(Ham_TS_OnEntFreePrivateData, this)
	 */
	Ham_TS_OnFreeEntPrivateData,
	
	/**
	 * Description:		Probably called when the engine call to ShouldCollide is called.
	 * Forward params:	function(this, otherEntity)
	 * Return type:		Integer (boolean).
	 * Execute params:	ExecuteHam(Ham_TS_ShouldCollide, this, otherEntity)
	 */
	Ham_TS_ShouldCollide,
	
	/**
	 * DONT USE ME LOL
	 */
	HAM_LAST_ENTRY_DONT_USE_ME_LOL
};

enum HamError
{
	HAM_OK = 0,
	
	HAM_INVALID_FUNC,			// The function is not valid
	HAM_FUNC_NOT_CONFIGURED,	// This function is not configured in hamdata.ini
	
	HAM_ERR_END
};
