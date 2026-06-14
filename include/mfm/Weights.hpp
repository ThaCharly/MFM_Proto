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

// --- CONTEXT EXTRACTOR ---
inline float ctxPressHighBoost()  { return Config::getInstance().get("CTX_PRESS_HIGH_BOOST", 0.15f); }
inline float ctxPressGegenBoost() { return Config::getInstance().get("CTX_PRESS_GEGEN_BOOST", 0.25f); }
inline float ctxDefLineThresh()   { return Config::getInstance().get("CTX_DEF_LINE_THRESH", 0.6f); }
inline float ctxDefLineBoost()    { return Config::getInstance().get("CTX_DEF_LINE_BOOST", 0.15f); }
inline float ctxPressExtreme()    { return Config::getInstance().get("CTX_PRESS_EXTREME", 0.75f); }
inline float ctxPressHigh()       { return Config::getInstance().get("CTX_PRESS_HIGH", 0.50f); }
inline float ctxPressMedium()     { return Config::getInstance().get("CTX_PRESS_MEDIUM", 0.25f); }
inline float ctxSpaceThresh()     { return Config::getInstance().get("CTX_SPACE_THRESH", 0.4f); }

// --- STATE UPDATER ---
inline float timeBase()           { return Config::getInstance().get("TIME_BASE", 3.0f); }
inline float timeHold()           { return Config::getInstance().get("TIME_HOLD", 6.0f); }
inline float timePassSafe()       { return Config::getInstance().get("TIME_PASS_SAFE", 4.0f); }
inline float timeShoot()          { return Config::getInstance().get("TIME_SHOOT", 2.0f); }
inline float pressIncSuccess()    { return Config::getInstance().get("PRESS_INC_SUCCESS", 0.05f); }
inline float momentumIncSuccess() { return Config::getInstance().get("MOMENTUM_INC_SUCCESS", 0.02f); }
inline float pressResetLoss()     { return Config::getInstance().get("PRESS_RESET_LOSS", 0.2f); }
inline float pressResetGoal()     { return Config::getInstance().get("PRESS_RESET_GOAL", 0.1f); }
inline float momentumResetGoal()  { return Config::getInstance().get("MOMENTUM_RESET_GOAL", 0.5f); }

// --- SEÑALES: ATTRIBUTE ---
inline float attrVisionMult()     { return Config::getInstance().get("ATTR_VISION_MULT", 0.6f); }
inline float attrDribbleMult()    { return Config::getInstance().get("ATTR_DRIBBLE_MULT", 0.5f); }
inline float attrComposureMult()  { return Config::getInstance().get("ATTR_COMPOSURE_MULT", 0.3f); }
inline float attrShootMult()      { return Config::getInstance().get("ATTR_SHOOT_MULT", 0.4f); }
inline float attrShootLongMult()  { return Config::getInstance().get("ATTR_SHOOT_LONG_MULT", 0.3f); }
inline float attrStrengthMult()   { return Config::getInstance().get("ATTR_STRENGTH_MULT", 0.4f); }

// --- SEÑALES: CONSECUTIVE PASSES ---
inline float cp5PassRisky()       { return Config::getInstance().get("CP_5_PASS_RISKY", 1.4f); }
inline float cp5Shoot()           { return Config::getInstance().get("CP_5_SHOOT", 1.3f); }
inline float cp5Dribble()         { return Config::getInstance().get("CP_5_DRIBBLE", 1.2f); }
inline float cp5PassSafe()        { return Config::getInstance().get("CP_5_PASS_SAFE", 0.8f); }
inline float cp3PassRisky()       { return Config::getInstance().get("CP_3_PASS_RISKY", 1.15f); }

// --- SEÑALES: MOMENTUM ---
inline float momHighPassRisky()   { return Config::getInstance().get("MOM_HIGH_PASS_RISKY", 1.3f); }
inline float momHighDribble()     { return Config::getInstance().get("MOM_HIGH_DRIBBLE", 1.2f); }
inline float momHighShoot()       { return Config::getInstance().get("MOM_HIGH_SHOOT", 1.15f); }
inline float momLowHold()         { return Config::getInstance().get("MOM_LOW_HOLD", 1.4f); }
inline float momLowPassSafe()     { return Config::getInstance().get("MOM_LOW_PASS_SAFE", 1.3f); }
inline float momLowPassRisky()    { return Config::getInstance().get("MOM_LOW_PASS_RISKY", 0.6f); }

// --- SEÑALES: PASSING LANES ---
inline float lane0PassSafe()      { return Config::getInstance().get("LANE_0_PASS_SAFE", 0.3f); }
inline float lane0PassRisky()     { return Config::getInstance().get("LANE_0_PASS_RISKY", 0.0f); }
inline float lane0Hold()          { return Config::getInstance().get("LANE_0_HOLD", 2.0f); }
inline float lane0Dribble()       { return Config::getInstance().get("LANE_0_DRIBBLE", 1.5f); }
inline float lane1PassRisky()     { return Config::getInstance().get("LANE_1_PASS_RISKY", 0.5f); }
inline float lane1PassSafe()      { return Config::getInstance().get("LANE_1_PASS_SAFE", 0.8f); }

// --- SEÑALES: PRESSURE ---
inline float pressExtPassSafe()   { return Config::getInstance().get("PRESS_EXT_PASS_SAFE", 1.4f); }
inline float pressExtHold()       { return Config::getInstance().get("PRESS_EXT_HOLD", 1.3f); }
inline float pressExtPassRisky()  { return Config::getInstance().get("PRESS_EXT_PASS_RISKY", 0.4f); }
inline float pressExtDribble()    { return Config::getInstance().get("PRESS_EXT_DRIBBLE", 0.5f); }
inline float pressExtShoot()      { return Config::getInstance().get("PRESS_EXT_SHOOT", 0.7f); }
inline float pressHighPassSafe()  { return Config::getInstance().get("PRESS_HIGH_PASS_SAFE", 1.2f); }
inline float pressHighPassRisky() { return Config::getInstance().get("PRESS_HIGH_PASS_RISKY", 0.7f); }

// --- SEÑALES: SCORE URGENCY ---
inline float urgLoseComfShoot()     { return Config::getInstance().get("URG_LOSE_COMF_SHOOT", 2.0f); }
inline float urgLoseComfLongBall()  { return Config::getInstance().get("URG_LOSE_COMF_LONG_BALL", 1.8f); }
inline float urgLoseComfPassRisky() { return Config::getInstance().get("URG_LOSE_COMF_PASS_RISKY", 1.6f); }
inline float urgLoseComfHold()      { return Config::getInstance().get("URG_LOSE_COMF_HOLD", 0.3f); }
inline float urgLoseComfPassSafe()  { return Config::getInstance().get("URG_LOSE_COMF_PASS_SAFE", 0.5f); }
inline float urgLoseTightPassRisky(){ return Config::getInstance().get("URG_LOSE_TIGHT_PASS_RISKY", 1.4f); }
inline float urgLoseTightShoot()    { return Config::getInstance().get("URG_LOSE_TIGHT_SHOOT", 1.3f); }
inline float urgWinComfPassSafe()   { return Config::getInstance().get("URG_WIN_COMF_PASS_SAFE", 1.5f); }
inline float urgWinComfHold()       { return Config::getInstance().get("URG_WIN_COMF_HOLD", 1.6f); }
inline float urgWinComfPassRisky()  { return Config::getInstance().get("URG_WIN_COMF_PASS_RISKY", 0.5f); }
inline float urgWinComfShoot()      { return Config::getInstance().get("URG_WIN_COMF_SHOOT", 0.7f); }

// --- RESOLUCIÓN: ESCALA DE DUELOS ---
inline float duelBase()  { return Config::getInstance().get("DUEL_BASE", 50.0f); }
inline float duelScale() { return Config::getInstance().get("DUEL_SCALE", 1.0f); }

// --- RESOLUCIÓN: TIROS AL ARCO (PRECISIÓN) ---
inline float resShootOnTargetScale() { return Config::getInstance().get("RES_SHOOT_ON_TARGET_SCALE", 0.75f); }
inline float resShootOnTargetMin()   { return Config::getInstance().get("RES_SHOOT_ON_TARGET_MIN", 15.0f); }
inline float resShootOnTargetMax()   { return Config::getInstance().get("RES_SHOOT_ON_TARGET_MAX", 90.0f); }

} // namespace mfm::Weights