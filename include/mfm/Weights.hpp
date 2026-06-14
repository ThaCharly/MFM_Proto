#pragma once
#include "Config.hpp"

namespace mfm::Weights {

// --- INFERENCIA: PROBABILIDAD BASE ---
inline float baseActionProb() { return Config::getInstance().get("BASE_ACTION_PROB", 0.01f); }

// --- INFERENCIA: ZONAS ---
inline float zoneDefPassSafe() { return Config::getInstance().get("ZONE_DEF_PASS_SAFE", 0.60f); }
inline float zoneDefLongBall() { return Config::getInstance().get("ZONE_DEF_LONG_BALL", 0.25f); }
inline float zoneDefHold()     { return Config::getInstance().get("ZONE_DEF_HOLD", 0.10f); }

inline float zoneTransPassSafe()  { return Config::getInstance().get("ZONE_TRANS_PASS_SAFE", 0.50f); }
inline float zoneTransPassRisky() { return Config::getInstance().get("ZONE_TRANS_PASS_RISKY", 0.20f); }
inline float zoneTransDribble()   { return Config::getInstance().get("ZONE_TRANS_DRIBBLE", 0.15f); }

inline float zoneOffPassRisky() { return Config::getInstance().get("ZONE_OFF_PASS_RISKY", 0.35f); }
inline float zoneOffCross()     { return Config::getInstance().get("ZONE_OFF_CROSS", 0.20f); }
inline float zoneOffDribble()   { return Config::getInstance().get("ZONE_OFF_DRIBBLE", 0.20f); }

inline float zoneDangerShoot()    { return Config::getInstance().get("ZONE_DANGER_SHOOT", 0.60f); }
inline float zoneDangerPassSafe() { return Config::getInstance().get("ZONE_DANGER_PASS_SAFE", 0.15f); }

// --- INFERENCIA: ROLES ---
inline float roleGkLongBall()    { return Config::getInstance().get("ROLE_GK_LONG_BALL", 3.0f); }
inline float roleTargetManHold() { return Config::getInstance().get("ROLE_TARGET_MAN_HOLD", 3.5f); }

// --- INFERENCIA: TÁCTICAS ---
inline float tacticDirectPassRisky() { return Config::getInstance().get("TACTIC_DIRECT_PASS_RISKY", 1.6f); }
inline float tacticLongLongBall()    { return Config::getInstance().get("TACTIC_LONG_LONG_BALL", 2.5f); }
inline float transFastPassRisky()    { return Config::getInstance().get("TRANS_FAST_PASS_RISKY", 2.0f); }
inline float transFastDribble()      { return Config::getInstance().get("TRANS_FAST_DRIBBLE", 1.5f); }

// --- RESOLUCIÓN: PASE SEGURO ---
inline float resPassSafeTech()   { return Config::getInstance().get("RES_PASS_SAFE_TECH", 0.7f); }
inline float resPassSafeComp()   { return Config::getInstance().get("RES_PASS_SAFE_COMP", 0.3f); }
inline float resPassSafeDefPos() { return Config::getInstance().get("RES_PASS_SAFE_DEF_POS", 0.2f); }

// --- RESOLUCIÓN: PASE ARRIESGADO ---
inline float resPassRiskTech()   { return Config::getInstance().get("RES_PASS_RISK_TECH", 0.4f); }
inline float resPassRiskVis()    { return Config::getInstance().get("RES_PASS_RISK_VIS", 0.4f); }
inline float resPassRiskComp()   { return Config::getInstance().get("RES_PASS_RISK_COMP", 0.2f); }
inline float resPassRiskDefAnt() { return Config::getInstance().get("RES_PASS_RISK_DEF_ANT", 0.4f); }
inline float resPassRiskDefPos() { return Config::getInstance().get("RES_PASS_RISK_DEF_POS", 0.3f); }

// --- RESOLUCIÓN: GAMBETA ---
inline float resDribbleTech()    { return Config::getInstance().get("RES_DRIBBLE_TECH", 0.6f); }
inline float resDribblePace()    { return Config::getInstance().get("RES_DRIBBLE_PACE", 0.4f); }
inline float resDribbleDefTack() { return Config::getInstance().get("RES_DRIBBLE_DEF_TACK", 0.6f); }
inline float resDribbleDefPace() { return Config::getInstance().get("RES_DRIBBLE_DEF_PACE", 0.4f); }

// --- RESOLUCIÓN: RETENCIÓN (HOLD) ---
inline float resHoldStr()     { return Config::getInstance().get("RES_HOLD_STR", 0.7f); }
inline float resHoldComp()    { return Config::getInstance().get("RES_HOLD_COMP", 0.3f); }
inline float resHoldDefStr()  { return Config::getInstance().get("RES_HOLD_DEF_STR", 0.5f); }
inline float resHoldDefMark() { return Config::getInstance().get("RES_HOLD_DEF_MARK", 0.3f); }

// --- RESOLUCIÓN: TIRO ---
inline float resShootTech()        { return Config::getInstance().get("RES_SHOOT_TECH", 0.6f); }
inline float resShootComp()        { return Config::getInstance().get("RES_SHOOT_COMP", 0.4f); }
inline float resShootLongPenalty() { return Config::getInstance().get("RES_SHOOT_LONG_PENALTY", 0.7f); }
inline float resGkRef()            { return Config::getInstance().get("RES_GK_REF", 0.6f); }
inline float resGkPos()            { return Config::getInstance().get("RES_GK_POS", 0.4f); }

// --- CONSTANTES GLOBALES Y FÍSICA ---
inline float fatigueMaxPenalty() { return Config::getInstance().get("FATIGUE_MAX_PENALTY", 0.5f); }
inline float fatigueScale()      { return Config::getInstance().get("FATIGUE_SCALE", 150.0f); }
inline float fatigueBaseRate()   { return Config::getInstance().get("FATIGUE_BASE_RATE", 0.04f); }

} // namespace mfm::Weights