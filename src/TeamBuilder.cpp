#include "mfm/TeamBuilder.hpp"

namespace mfm {

Team TeamBuilder::createNacional() {
    Team t;
    t.name = "Nacional";
    t.formation = FormationId::F_433;
    t.tactics = {
        .press_style = PressStyle::HIGH_PRESS,
        .build_up = BuildUpStyle::LONG_BALL,
        .atk_transition = TransitionStyle::FAST_BREAK,
        .def_transition = TransitionStyle::IMMEDIATE_PRESS,
        .defensive_line = 0.67f,
        .width = 0.4f
    };
    
    t.squad = {
        {"Luis Mejía [GK]", RoleId::GOALKEEPER, PlayerAttributes{
            .passing=45, .first_touch=50, .dribbling=10, .shooting=10, .heading=60, 
            .crossing=10, .vision=45, .positioning=75, .anticipation=70, .composure=75, 
            .pace=50, .stamina=60, .strength=75, .tackling=10, .marking=10, 
            .reflexes_gk=85, .positioning_gk=82, .handling_gk=78, .aerial_gk=80
        }, 0},
        
        {"Emiliano Ancheta [DF_R]", RoleId::OFFENSIVE_FULLBACK, PlayerAttributes{
            .passing=65, .first_touch=68, .dribbling=70, .shooting=50, .heading=65, 
            .crossing=72, .vision=60, .positioning=70, .anticipation=70, .composure=68, 
            .pace=80, .stamina=85, .strength=72, .tackling=74, .marking=68, 
            .reflexes_gk=10, .positioning_gk=10, .handling_gk=10, .aerial_gk=10
        }, 1},
        
        {"Sebastián Coates [DF_C]", RoleId::CENTER_BACK, PlayerAttributes{
            .passing=68, .first_touch=65, .dribbling=50, .shooting=45, .heading=82, 
            .crossing=50, .vision=65, .positioning=80, .anticipation=82, .composure=85, 
            .pace=55, .stamina=70, .strength=88, .tackling=85, .marking=80, 
            .reflexes_gk=10, .positioning_gk=10, .handling_gk=10, .aerial_gk=10
        }, 1},
        
        {"Agustín Rogel [DF_C]", RoleId::CENTER_BACK, PlayerAttributes{
            .passing=60, .first_touch=62, .dribbling=45, .shooting=40, .heading=78, 
            .crossing=45, .vision=55, .positioning=75, .anticipation=78, .composure=70, 
            .pace=70, .stamina=80, .strength=80, .tackling=80, .marking=75, 
            .reflexes_gk=10, .positioning_gk=10, .handling_gk=10, .aerial_gk=10
        }, 1},
        
        {"Camilo Cándido [DF_L]", RoleId::DEFENSIVE_FULLBACK, PlayerAttributes{
            .passing=68, .first_touch=70, .dribbling=65, .shooting=55, .heading=60, 
            .crossing=75, .vision=65, .positioning=72, .anticipation=74, .composure=70, 
            .pace=75, .stamina=82, .strength=74, .tackling=76, .marking=72, 
            .reflexes_gk=10, .positioning_gk=10, .handling_gk=10, .aerial_gk=10
        }, 1},
        
        {"Agustín Dos Santos [MC_D]", RoleId::DEFENSIVE_MIDFIELDER, PlayerAttributes{
            .passing=70, .first_touch=72, .dribbling=60, .shooting=55, .heading=65, 
            .crossing=55, .vision=65, .positioning=78, .anticipation=80, .composure=75, 
            .pace=75, .stamina=88, .strength=78, .tackling=82, .marking=78, 
            .reflexes_gk=10, .positioning_gk=10, .handling_gk=10, .aerial_gk=10
        }, 2},
        
        {"Lucas Boggio [MC_C]", RoleId::BOX_TO_BOX, PlayerAttributes{
            .passing=75, .first_touch=75, .dribbling=68, .shooting=60, .heading=60, 
            .crossing=65, .vision=72, .positioning=76, .anticipation=75, .composure=78, 
            .pace=72, .stamina=85, .strength=76, .tackling=78, .marking=70, 
            .reflexes_gk=10, .positioning_gk=10, .handling_gk=10, .aerial_gk=10
        }, 2},
        
        {"Diente López [MC_A]", RoleId::ADVANCED_PLAYMAKER, PlayerAttributes{
            .passing=82, .first_touch=82, .dribbling=80, .shooting=75, .heading=55, 
            .crossing=75, .vision=85, .positioning=78, .anticipation=65, .composure=80, 
            .pace=68, .stamina=70, .strength=65, .tackling=50, .marking=45, 
            .reflexes_gk=10, .positioning_gk=10, .handling_gk=10, .aerial_gk=10
        }, 2},
        
        {"Tomás Verón Lupi [EX_R]", RoleId::WINGER, PlayerAttributes{
            .passing=68, .first_touch=72, .dribbling=82, .shooting=68, .heading=55, 
            .crossing=78, .vision=65, .positioning=70, .anticipation=60, .composure=68, 
            .pace=88, .stamina=84, .strength=65, .tackling=45, .marking=40, 
            .reflexes_gk=10, .positioning_gk=10, .handling_gk=10, .aerial_gk=10
        }, 3},
        
        {"Maxi Gómez [DC]", RoleId::TARGET_FORWARD, PlayerAttributes{
            .passing=62, .first_touch=75, .dribbling=68, .shooting=94, .heading=85, 
            .crossing=50, .vision=65, .positioning=82, .anticipation=70, .composure=80, 
            .pace=85, .stamina=78, .strength=86, .tackling=40, .marking=35, 
            .reflexes_gk=10, .positioning_gk=10, .handling_gk=10, .aerial_gk=10
        }, 3},
        
        {"Rodrigo Martínez [EX_L]", RoleId::INSIDE_FORWARD, PlayerAttributes{
            .passing=72, .first_touch=76, .dribbling=80, .shooting=80, .heading=80, 
            .crossing=65, .vision=70, .positioning=78, .anticipation=65, .composure=78, 
            .pace=78, .stamina=75, .strength=82, .tackling=45, .marking=40, 
            .reflexes_gk=10, .positioning_gk=10, .handling_gk=10, .aerial_gk=10
        }, 3}
    };
    return t;
}

Team TeamBuilder::createPenarol() {
    Team t;
    t.name = "Peñarol";
    t.formation = FormationId::F_442;
    t.tactics = {
        .press_style = PressStyle::MID_BLOCK,
        .build_up = BuildUpStyle::PATIENT,
        .atk_transition = TransitionStyle::CONTROLLED,
        .def_transition = TransitionStyle::REGROUP,
        .defensive_line = 0.4f,
        .width = 0.5f
    };
    
    t.squad = {
        {"Washington Aguerre [GK]", RoleId::GOALKEEPER, PlayerAttributes{
            .passing=50, .first_touch=55, .dribbling=10, .shooting=10, .heading=60, 
            .crossing=10, .vision=40, .positioning=72, .anticipation=68, .composure=70, 
            .pace=55, .stamina=60, .strength=70, .tackling=10, .marking=10, 
            .reflexes_gk=84, .positioning_gk=80, .handling_gk=75, .aerial_gk=78
        }, 0},
        
        {"Brian Barboza [DF_R]", RoleId::OFFENSIVE_FULLBACK, PlayerAttributes{
            .passing=70, .first_touch=72, .dribbling=75, .shooting=60, .heading=55, 
            .crossing=75, .vision=68, .positioning=70, .anticipation=68, .composure=72, 
            .pace=82, .stamina=84, .strength=65, .tackling=70, .marking=65, 
            .reflexes_gk=10, .positioning_gk=10, .handling_gk=10, .aerial_gk=10
        }, 1},
        
        {"Emanuel Gularte [DF_C]", RoleId::CENTER_BACK, PlayerAttributes{
            .passing=62, .first_touch=65, .dribbling=48, .shooting=45, .heading=85, 
            .crossing=45, .vision=55, .positioning=78, .anticipation=80, .composure=75, 
            .pace=60, .stamina=75, .strength=86, .tackling=82, .marking=78, 
            .reflexes_gk=10, .positioning_gk=10, .handling_gk=10, .aerial_gk=10
        }, 1},
        
        {"Mauricio Lemos [DF_C]", RoleId::CENTER_BACK, PlayerAttributes{
            .passing=65, .first_touch=68, .dribbling=50, .shooting=40, .heading=80, 
            .crossing=50, .vision=60, .positioning=76, .anticipation=78, .composure=74, 
            .pace=65, .stamina=78, .strength=82, .tackling=80, .marking=75, 
            .reflexes_gk=10, .positioning_gk=10, .handling_gk=10, .aerial_gk=10
        }, 1},
        
        {"Maximiliano Olivera [DF_L]", RoleId::DEFENSIVE_FULLBACK, PlayerAttributes{
            .passing=65, .first_touch=68, .dribbling=60, .shooting=45, .heading=65, 
            .crossing=68, .vision=60, .positioning=74, .anticipation=72, .composure=70, 
            .pace=78, .stamina=80, .strength=75, .tackling=78, .marking=72, 
            .reflexes_gk=10, .positioning_gk=10, .handling_gk=10, .aerial_gk=10
        }, 1},
        
        {"Jesús Trindade [MC_D]", RoleId::DEFENSIVE_MIDFIELDER, PlayerAttributes{
            .passing=72, .first_touch=70, .dribbling=62, .shooting=50, .heading=65, 
            .crossing=55, .vision=68, .positioning=78, .anticipation=82, .composure=76, 
            .pace=70, .stamina=85, .strength=80, .tackling=84, .marking=78, 
            .reflexes_gk=10, .positioning_gk=10, .handling_gk=10, .aerial_gk=10
        }, 2},
        
        {"Rodrigo Fernández [MC_C]", RoleId::BOX_TO_BOX, PlayerAttributes{
            .passing=74, .first_touch=75, .dribbling=70, .shooting=65, .heading=60, 
            .crossing=68, .vision=75, .positioning=78, .anticipation=74, .composure=75, 
            .pace=78, .stamina=86, .strength=72, .tackling=76, .marking=68, 
            .reflexes_gk=10, .positioning_gk=10, .handling_gk=10, .aerial_gk=10
        }, 2},
        
        {"Eduardo Darias [MC_A]", RoleId::ADVANCED_PLAYMAKER, PlayerAttributes{
            .passing=80, .first_touch=80, .dribbling=78, .shooting=72, .heading=55, 
            .crossing=75, .vision=82, .positioning=75, .anticipation=65, .composure=78, 
            .pace=72, .stamina=72, .strength=65, .tackling=55, .marking=50, 
            .reflexes_gk=10, .positioning_gk=10, .handling_gk=10, .aerial_gk=10
        }, 2},
        
        {"Nahuel Umpierrez [EX_L]", RoleId::WINGER, PlayerAttributes{
            .passing=72, .first_touch=76, .dribbling=80, .shooting=68, .heading=55, 
            .crossing=76, .vision=70, .positioning=72, .anticipation=60, .composure=70, 
            .pace=85, .stamina=80, .strength=65, .tackling=45, .marking=40, 
            .reflexes_gk=10, .positioning_gk=10, .handling_gk=10, .aerial_gk=10
        }, 3},
        
        {"Facundo Batista [DC]", RoleId::PRESSING_FORWARD, PlayerAttributes{
            .passing=65, .first_touch=72, .dribbling=70, .shooting=80, .heading=78, 
            .crossing=55, .vision=65, .positioning=80, .anticipation=75, .composure=78, 
            .pace=78, .stamina=82, .strength=78, .tackling=50, .marking=45, 
            .reflexes_gk=10, .positioning_gk=10, .handling_gk=10, .aerial_gk=10
        }, 3},
        
        {"Matías Arezo [EX_R]", RoleId::INSIDE_FORWARD, PlayerAttributes{
            .passing=70, .first_touch=75, .dribbling=82, .shooting=75, .heading=65, 
            .crossing=72, .vision=68, .positioning=75, .anticipation=65, .composure=74, 
            .pace=86, .stamina=78, .strength=70, .tackling=45, .marking=40, 
            .reflexes_gk=10, .positioning_gk=10, .handling_gk=10, .aerial_gk=10
        }, 3}
    };
    return t;
}

} // namespace mfm