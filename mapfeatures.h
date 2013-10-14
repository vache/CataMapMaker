#ifndef FEATURES_H
#define FEATURES_H

//#include "color.h"
#include "colors.h"
#include <QList>
#include <QString>

enum ter_id {
t_null = 0,
t_hole, // Real nothingness; makes you fall a z-level
// Ground
t_dirt, t_sand, t_dirtmound, t_pit_shallow, t_pit,
t_pit_corpsed, t_pit_covered, t_pit_spiked, t_pit_spiked_covered,
t_rock_floor, t_rubble, t_ash, t_metal, t_wreckage,
t_grass,
t_metal_floor,
t_pavement, t_pavement_y, t_sidewalk, t_concrete,
t_floor,
t_dirtfloor,//Dirt floor(Has roof)
t_grate,
t_slime,
t_bridge,
// Lighting related
t_skylight, t_emergency_light_flicker, t_emergency_light,
// Walls
t_wall_log_half, t_wall_log, t_wall_log_chipped, t_wall_log_broken, t_palisade, t_palisade_gate, t_palisade_gate_o,
t_wall_half, t_wall_wood, t_wall_wood_chipped, t_wall_wood_broken,
t_wall_v, t_wall_h, t_concrete_v, t_concrete_h,
t_wall_metal_v, t_wall_metal_h,
t_wall_glass_v, t_wall_glass_h,
t_wall_glass_v_alarm, t_wall_glass_h_alarm,
t_reinforced_glass_v, t_reinforced_glass_h,
t_bars,
t_door_c, t_door_b, t_door_o, t_door_locked_interior, t_door_locked, t_door_locked_alarm, t_door_frame,
t_chaingate_l, t_fencegate_c, t_fencegate_o, t_chaingate_c, t_chaingate_o, t_door_boarded,
t_door_metal_c, t_door_metal_o, t_door_metal_locked,
t_door_bar_c, t_door_bar_o, t_door_bar_locked,
t_door_glass_c, t_door_glass_o,
t_portcullis,
t_recycler, t_window, t_window_taped, t_window_domestic, t_window_domestic_taped, t_window_open, t_curtains,
t_window_alarm, t_window_alarm_taped, t_window_empty, t_window_frame, t_window_boarded,
t_window_stained_green, t_window_stained_red, t_window_stained_blue,
t_rock, t_fault,
t_paper,
// Tree
t_tree, t_tree_young, t_tree_apple, t_underbrush, t_shrub, t_shrub_blueberry, t_shrub_strawberry, t_trunk,
t_root_wall,
t_wax, t_floor_wax,
t_fence_v, t_fence_h, t_chainfence_v, t_chainfence_h, t_chainfence_posts,
t_fence_post, t_fence_wire, t_fence_barbed, t_fence_rope,
t_railing_v, t_railing_h,
// Nether
t_marloss, t_fungus, t_tree_fungal,
// Water, lava, etc.
t_water_sh, t_water_dp, t_water_pool, t_sewage,
t_lava,
// More embellishments than you can shake a stick at.
t_sandbox, t_slide, t_monkey_bars, t_backboard,
t_gas_pump, t_gas_pump_smashed,
t_generator_broken,
t_missile, t_missile_exploded,
t_radio_tower, t_radio_controls,
t_console_broken, t_console, t_gates_mech_control, t_gates_control_concrete, t_barndoor, t_palisade_pulley,
t_sewage_pipe, t_sewage_pump,
t_centrifuge,
t_column,
t_vat,
// Staircases etc.
t_stairs_down, t_stairs_up, t_manhole, t_ladder_up, t_ladder_down, t_slope_down,
 t_slope_up, t_rope_up,
t_manhole_cover,
// Special
t_card_science, t_card_military, t_card_reader_broken, t_slot_machine,
 t_elevator_control, t_elevator_control_off, t_elevator, t_pedestal_wyrm,
 t_pedestal_temple,
// Temple tiles
t_rock_red, t_rock_green, t_rock_blue, t_floor_red, t_floor_green, t_floor_blue,
 t_switch_rg, t_switch_gb, t_switch_rb, t_switch_even,

num_terrain_types
};

struct ter_t {
 QString name; //The plaintext name of the terrain type the user would see (IE: dirt)

//The symbol drawn on the screen for the terrain. Please note that there are extensive rules as to which
//possible object/field/entity in a single square gets drawn and that some symbols are "reserved" such as * and % to do programmatic behavior.

 char sym;

 nc_color color;  //The color the sym will draw in on the GUI.

 ter_id id;

 ter_t()
 {
     name = "nothing";
     sym = ' ';
     color = c_black;
     id = t_null;
 }

 ter_t(QString n, char s, nc_color c, ter_id i)
 {
     name = n;
     sym = s;
     color = c;
     id = i;
 }

 ter_t(const ter_t& copy)
 {
     name = copy.name;
     sym = copy.sym;
     color = copy.color;
     id = copy.id;
 }
};

const ter_t terlist[num_terrain_types] = {
{"nothing", ' '  , c_white  , t_null},
{("empty space"), ' '  , c_black  , t_hole},
{("dirt"), '.'  , c_brown  , t_dirt},
{("sand"), '.'  , c_yellow  , t_sand},
{("mound of dirt"), '#'  , c_brown  , t_dirtmound},
{("shallow pit"), '0'  , c_yellow  , t_pit_shallow},
{("pit"), '0'  , c_brown  , t_pit},
{("corpse filled pit"), '#'  , c_green  , t_pit_corpsed},
{("covered pit"), '#'  , c_ltred  , t_pit_covered},
{("spiked pit"), '0'  , c_ltred  , t_pit_spiked},
{("covered spiked pit"), '#'  , c_ltred  , t_pit_spiked_covered},
{("rock floor"), '.'  , c_ltgray  , t_rock_floor},
{("pile of rubble"), '^'  , c_ltgray  , t_rubble},
{("pile of ash"), '#'  , c_ltgray  , t_ash},
{("twisted metal"), '#'  , c_cyan  , t_metal},
{("metal wreckage"), '#'  , c_cyan  , t_wreckage},
{("grass"), '.'  , c_green  , t_grass},
{("metal floor"), '.'  , c_ltcyan  , t_metal_floor},
{("pavement"), '.'  , c_dkgray  , t_pavement},
{("yellow pavement"), '.'  , c_yellow  , t_pavement_y},
{("sidewalk"), '.'  , c_ltgray  , t_sidewalk},
{("concrete"), '.'  , c_ltgray  , t_concrete},
{("floor"), '.'  , c_cyan  , t_floor},
{("dirt floor"), '.'  , c_brown  , t_dirtfloor},
{("metal grate"), '#'  , c_dkgray  , t_grate},
{("slime"), '~'  , c_green  , t_slime},
{("walkway"), '#'  , c_yellow  , t_bridge},
{("floor(skylight)"), '.'  , c_white  , t_skylight},
{("floor(emrg light)"), '.'  , c_white  , t_emergency_light_flicker},
{("floor(reg light)"), '.'  , c_white  , t_emergency_light},
{("half-built log wall"), '#'  , c_brown  , t_wall_log_half},
{("log wall"), '#'  , c_brown  , t_wall_log},
{("chipped log wall"), '#'  , c_brown  , t_wall_log_chipped},
{("broken log wall"), '&'  , c_brown  , t_wall_log_broken},
{("palisade wall"), '#'  , c_brown  , t_palisade},
{("palisade gate"), '+'  , c_ltred  , t_palisade_gate},
{("open palisade gate"), '.'  , c_brown  , t_palisade_gate_o},
{("half-built wall"), '#' , c_ltred, t_wall_half},
{("wooden wall"), '#'  , c_ltred  , t_wall_wood},
{("chipped wood wall"), '#'  , c_ltred  , t_wall_wood_chipped},
{("broken wood wall"), '&'  , c_ltred  , t_wall_wood_broken},
{("wall"), '|'  , c_ltgray  , t_wall_v},
{("wall"), '-'  , c_ltgray  , t_wall_h},
{("concrete wall"), '|'  , c_dkgray  , t_concrete_v},
{("concrete wall"), '-'  , c_dkgray  , t_concrete_h},
{("metal wall"), '|'  , c_cyan  , t_wall_metal_v},
{("metal wall"), '-'  , c_cyan  , t_wall_metal_h},
{("glass wall"), '|'  , c_ltcyan  , t_wall_glass_v},
{("glass wall"), '-'  , c_ltcyan  , t_wall_glass_h},
{("glass wall(alarm)"), '|'  , c_ltcyan  , t_wall_glass_v_alarm},
{("glass wall(alarm)"), '-'  , c_ltcyan  , t_wall_glass_h_alarm},
{("reinforced glass"), '|'  , c_ltcyan  , t_reinforced_glass_v},
{("reinforced glass"), '-'  , c_ltcyan  , t_reinforced_glass_h},
{("metal bars"), '"'  , c_ltgray  , t_bars},
{("closed wood door"), '+'  , c_brown  , t_door_c},
{("damaged wood door"), '&'  , c_brown  , t_door_b},
{("open wood door"), '\''  , c_brown  , t_door_o},
{("closed wood door(locked all)"), '+'  , c_brown  , t_door_locked_interior},
{("closed wood door(locked inside)"), '+'  , c_brown  , t_door_locked},
{("closed wood door(lock alarm)"), '+'  , c_brown  , t_door_locked_alarm},
{("empty door frame"), '.'  , c_brown  , t_door_frame},
{("locked wire gate"), '+'  , c_cyan  , t_chaingate_l},
{("closed wooden gate"), '+'  , c_brown  , t_fencegate_c},
{("open wooden gate"), '.'  , c_brown  , t_fencegate_o},
{("closed wire gate"), '+'  , c_cyan  , t_chaingate_c},
{("open wire gate"), '.'  , c_cyan  , t_chaingate_o},
{("boarded up door"), '#'  , c_brown  , t_door_boarded},
{("closed metal door"), '+'  , c_cyan  , t_door_metal_c},
{("open metal door"), '\''  , c_cyan  , t_door_metal_o},
{("closed metal door(locked)"), '+'  , c_cyan  , t_door_metal_locked},
{("closed bar door(unlocked)"), '+'  , c_cyan  , t_door_bar_c},
{("open bar door"), '\''  , c_cyan  , t_door_bar_o},
{("closed bar door(locked)"), '+'  , c_cyan  , t_door_bar_locked},
{("closed glass door"), '+'  , c_ltcyan  , t_door_glass_c},
{("open glass door"), '\''  , c_ltcyan  , t_door_glass_o},
{("makeshift portcullis"), '&'  , c_cyan  , t_portcullis},
{("steel compactor"), '&'  , c_green  , t_recycler},
{("window"), '"'  , c_ltcyan  , t_window},
{("taped window"), '"'  , c_dkgray  , t_window_taped},
{("window(curtains)"), '"'  , c_ltcyan  , t_window_domestic},
{("taped window(curtains)"), '"'  , c_dkgray  , t_window_domestic_taped},
{("open window"), '\''  , c_ltcyan  , t_window_open},
{("closed curtains"), '"'  , c_dkgray  , t_curtains},
{("window(alarm)"), '"'  , c_ltcyan  , t_window_alarm},
{("taped window(alarm)"), '"'  , c_dkgray  , t_window_alarm_taped},
{("empty window"), '0'  , c_yellow  , t_window_empty},
{("window frame"), '0'  , c_ltcyan  , t_window_frame},
{("boarded up window"), '#'  , c_brown  , t_window_boarded},
{("high stained glass window(g)"),'"'  , c_ltgreen  , t_window_stained_green},
{("high stained glass window(r)"),'"'  , c_ltred  , t_window_stained_red},
{("high stained glass window(b)"),'"'  , c_ltblue  , t_window_stained_blue},
{("solid rock"), '#'  , c_white  , t_rock},
{("odd fault"), '#'  , c_magenta  , t_fault},
{("paper wall"), '#'  , c_white  , t_paper},
{("tree"), '7'  , c_green  , t_tree},
{("young tree"), '1'  , c_green  , t_tree_young},
{("apple tree"), '7'  , c_ltgreen  , t_tree_apple},
{("underbrush"), '#'  , c_ltgreen  , t_underbrush},
{("shrub"), '#'  , c_green  , t_shrub},
{("blueberry bush"), '#'  , c_ltgreen  , t_shrub_blueberry},
{("strawberry bush"), '#'  , c_ltgreen  , t_shrub_strawberry},
{("tree trunk"), '1'  , c_brown  , t_trunk},
{("root wall"), '#'  , c_brown  , t_root_wall},
{("wax wall"), '#'  , c_yellow  , t_wax},
{("wax floor"), '.'  , c_yellow  , t_floor_wax},
{("picket fence"), '|'  , c_brown  , t_fence_v},
{("picket fence"), '-'  , c_brown  , t_fence_h},
{("chain link fence"), '|'  , c_cyan  , t_chainfence_v},
{("chain link fence"), '-'  , c_cyan  , t_chainfence_h},
{("metal post"), '#'  , c_cyan  , t_chainfence_posts},
{("fence post"), '#'  , c_brown  , t_fence_post},
{("wire fence"), '$'  , c_blue  , t_fence_wire},
{("barbed wire fence"), '$'  , c_blue  , t_fence_barbed},
{("rope fence"), '$'  , c_brown  , t_fence_rope},
{("railing"), '|'  , c_yellow  , t_railing_v},
{("railing"), '-'  , c_yellow  , t_railing_h},
{("marloss bush"), '1'  , c_dkgray  , t_marloss},
{("fungal bed"), '#'  , c_dkgray  , t_fungus},
{("fungal tree"), '7'  , c_dkgray  , t_tree_fungal},
{("shallow water"), '~'  , c_ltblue  , t_water_sh},
{("deep water"), '~'  , c_blue  , t_water_dp},
{("pool water"), '~'  , c_ltblue  , t_water_pool},
{("sewage"), '~'  , c_ltgreen  , t_sewage},
{("lava"), '~'  , c_red  , t_lava},
{("sandbox"), '#'  , c_yellow  , t_sandbox},
{("slide"), '#'  , c_ltcyan  , t_slide},
{("monkey bars"), '#'  , c_cyan  , t_monkey_bars},
{("backboard"), '7'  , c_red  , t_backboard},
{("gasoline pump"), '&'  , c_red  , t_gas_pump},
{("smashed gas pump"), '&'  , c_ltred  , t_gas_pump_smashed},
{("broken generator"), '&'  , c_ltgray  , t_generator_broken},
{("missile"), '#'  , c_ltblue  , t_missile},
{("blown-out missile"), '#'  , c_ltgray  , t_missile_exploded},
{("radio tower"), '&'  , c_ltgray  , t_radio_tower},
{("radio controls"), '6'  , c_green  , t_radio_controls},
{("broken console"), '6'  , c_ltgray  , t_console_broken},
{("computer console"), '6'  , c_blue  , t_console},
{("mechanical winch(mech)"), '6'  , c_cyan_red , t_gates_mech_control},
{("mechanical winch(concrete)"), '6'  , c_cyan_red , t_gates_control_concrete},
{("rope and pulley(barn)"), '|'  , c_brown  , t_barndoor},
{("rope and pulley(palisade)"), '|'  , c_brown  , t_palisade_pulley},
{("sewage pipe"), '1'  , c_ltgray  , t_sewage_pipe},
{("sewage pump"), '&'  , c_ltgray  , t_sewage_pump},
{("centrifuge"), '{'  , c_magenta  , t_centrifuge},
{("column"), '1'  , c_ltgray  , t_column},
{("cloning vat"), '0'  , c_ltcyan  , t_vat},
{("stairs down"), '>'  , c_yellow  , t_stairs_down},
{("stairs up"), '<'  , c_yellow  , t_stairs_up},
{("manhole"), '>'  , c_dkgray  , t_manhole},
{("ladder"), '<'  , c_dkgray  , t_ladder_up},
{("ladder"), '>'  , c_dkgray  , t_ladder_down},
{("downward slope"), '>'  , c_brown  , t_slope_down},
{("upward slope"), '<'  , c_brown  , t_slope_up},
{("rope leading up"), '<'  , c_white  , t_rope_up},
{("manhole cover"), '0'  , c_dkgray  , t_manhole_cover},
{("card reader(science)"), '6'  , c_pink  , t_card_science},
{("card reader(military)"), '6'  , c_pink  , t_card_military},
{("broken card reader"), '6'  , c_ltgray  , t_card_reader_broken},
{("slot machine"), '6'  , c_green  , t_slot_machine},
{("elevator controls"), '6'  , c_ltblue  , t_elevator_control},
{("powerless controls"), '6'  , c_ltgray  , t_elevator_control_off},
{("elevator"), '.'  , c_magenta  , t_elevator},
{("dark pedestal"), '&'  , c_dkgray  , t_pedestal_wyrm},
{("light pedestal"), '&'  , c_white  , t_pedestal_temple},
{("red stone"), '#'  , c_red  , t_rock_red},
{("green stone"), '#'  , c_green  , t_rock_green},
{("blue stone"), '#'  , c_blue  , t_rock_blue},
{("red floor"), '.'  , c_red  , t_floor_red},
{("green floor"), '.'  , c_green  , t_floor_green},
{("blue floor"), '.'  , c_blue  , t_floor_blue},
{("yellow switch"), '6'  , c_yellow  , t_switch_rg},
{("cyan switch"), '6'  , c_cyan  , t_switch_gb},
{("purple switch"), '6'  , c_magenta  , t_switch_rb},
{("checkered switch"), '6'  , c_white , t_switch_even}
};

const int ternoitems[] = { t_wall_log_half, t_wall_log, t_wall_log_chipped, t_wall_log_broken, t_palisade, t_palisade_gate, t_wall_half, t_wall_wood, t_wall_wood_chipped, t_wall_wood_broken,
                 t_wall_h, t_wall_v, t_concrete_h, t_concrete_v, t_wall_metal_h, t_wall_metal_v, t_reinforced_glass_h, t_reinforced_glass_v, t_wall_glass_h, t_wall_glass_v,
                 t_wall_glass_h_alarm, t_wall_glass_v_alarm, t_bars, t_door_c, t_door_b, t_door_locked, t_door_locked_interior, t_door_locked_alarm, t_door_boarded, t_door_metal_c, t_door_metal_locked,
                 t_door_bar_c, t_door_bar_locked, t_door_glass_c, t_portcullis, t_window, t_window_taped, t_window_domestic, t_window_domestic_taped, t_window_open, t_curtains, t_window_alarm, t_window_alarm_taped,
                 t_window_frame, t_window_boarded, t_window_stained_blue, t_window_stained_green, t_window_stained_red, t_rock, t_fault, t_paper, t_tree, t_tree_young, t_tree_apple, t_root_wall, t_wax,
                 t_fence_h, t_fence_v, t_chainfence_h, t_chainfence_v, t_railing_h, t_railing_v, t_tree_fungal, t_gas_pump, t_gas_pump_smashed, t_generator_broken, t_missile, t_missile_exploded,
                 t_radio_tower, t_radio_controls, t_console_broken, t_console, t_gates_mech_control, t_gates_control_concrete, t_barndoor, t_palisade_pulley, t_sewage_pump, t_card_military, t_card_science,
                 t_card_reader_broken, t_slot_machine, t_elevator_control, t_elevator_control_off };



//On altering any entries in this enum please add or remove the appropriate entry to the furn_names array in tile_id_data.h

enum furn_id {
f_null,
f_hay,
f_bulletin,
f_indoor_plant,
f_bed, f_toilet, f_makeshift_bed,
f_sink, f_oven, f_woodstove, f_fireplace, f_bathtub,
f_chair, f_armchair, f_sofa, f_cupboard, f_trashcan, f_desk, f_exercise,
f_bench, f_table, f_pool_table,
f_counter,
f_fridge, f_glass_fridge, f_dresser, f_locker,
f_rack, f_bookcase,
f_washer, f_dryer,
f_dumpster, f_dive_block,
f_crate_c, f_crate_o,
f_canvas_wall, f_canvas_door, f_canvas_door_o, f_groundsheet, f_fema_groundsheet,
f_skin_wall, f_skin_door, f_skin_door_o, f_skin_groundsheet,
f_mutpoppy,
f_safe_c, f_safe_l, f_safe_o,
f_plant_seed, f_plant_seedling, f_plant_mature, f_plant_harvest,
num_furniture_types
};

struct furn_t {
 QString name;
 char sym;
  nc_color color;
 furn_id id;
};

const furn_t furnlist[num_furniture_types] = {
{"nothing", ' '  , c_white  , f_null},
{("hay"), '#'  , i_brown  , f_hay},
{("bulletin board"), '6'  , c_blue  , f_bulletin},
{("indoor plant"), '^'  , c_green  , f_indoor_plant},
{("bed"), '#'  , c_magenta  , f_bed},
{("toilet"), '&'  , c_white  , f_toilet},
{("makeshift bed"), '#'  , c_magenta  , f_makeshift_bed},
{("sink"), '&'  , c_white  , f_sink},
{("oven"), '#'  , c_dkgray  , f_oven},
{("wood stove"), '#'  , i_red  , f_woodstove},
{("fireplace"), '#'  , i_white  , f_fireplace},
{("bathtub"), '~'  , c_white  , f_bathtub},
{("chair"), '#'  , c_brown  , f_chair},
{("arm chair"), 'H'  , c_green  , f_armchair},
{("sofa"), 'H'  , i_red  , f_sofa},
{("cupboard"), '#'  , c_blue  , f_cupboard},
{("trash can"), '&'  , c_ltcyan  , f_trashcan},
{("desk"), '#'  , c_ltred  , f_desk},
{("exercise machine"), 'T'  , c_dkgray  , f_exercise},
{("bench"), '#'  , c_brown  , f_bench},
{("table"), '#'  , c_red  , f_table},
{("pool table"), '#'  , c_green  , f_pool_table},
{("counter"), '#'  , c_blue  , f_counter},
{("refrigerator"), '{'  , c_ltcyan  , f_fridge},
{("glass door fridge"), '{'  , c_ltcyan  , f_glass_fridge},
{("dresser"), '{'  , c_brown  , f_dresser},
{("locker"), '{'  , c_ltgray  , f_locker},
{("display rack"), '{'  , c_ltgray  , f_rack},
{("book case"), '{'  , c_brown  , f_bookcase},
{("washing machine"), '{'  , i_white  , f_washer},
{("dryer"), '{'  , i_white  , f_dryer},
{("dumpster"), '{'  , c_green  , f_dumpster},
{("diving block"), 'O'  , c_ltgray  , f_dive_block},
{("crate"), 'X'  , i_brown  , f_crate_c},
{("open crate"), 'O'  , i_brown  , f_crate_o},
{("canvas wall"), '#'  , c_blue  , f_canvas_wall},
{("canvas flap"), '+'  , c_blue  , f_canvas_door},
{("open canvas flap"), '.'  , c_blue  , f_canvas_door_o},
{("groundsheet"), ';'  , c_green  , f_groundsheet},
{("groundsheet"), ';'  , c_green  , f_fema_groundsheet},
{("animalskin wall"), '#'  , c_brown  , f_skin_wall},
{("animalskin flap"), '+'  , c_white  , f_skin_door},
{("open animalskin flap"), '.'  , c_white  , f_skin_door_o},
{("animalskin floor"), ';'  , c_brown  , f_skin_groundsheet},
{("mutated poppy flower"), 'f'  , c_red  , f_mutpoppy},
{("safe"), 'X'  , c_ltgray  , f_safe_c},
{("safe"), 'X'  , c_ltgray  , f_safe_l},
{("open safe"), 'O'  , c_ltgray  , f_safe_o},
{("seed"), '^'  , c_brown  , f_plant_seed},
{("seedling"), '^'  , c_green  , f_plant_seedling},
{("mature plant"), '#'  , c_green  , f_plant_mature},
{("harvestable plant"), '#'  , c_ltgreen , f_plant_harvest},
};

const int furnnoitems[] = { f_bulletin, f_canvas_wall, f_canvas_door, f_skin_wall, f_skin_door, f_plant_seed, f_plant_seedling, f_plant_harvest, f_plant_mature };

#endif // FEATURES_H
