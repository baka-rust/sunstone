#ifndef QUADTYPES_H
#define QUADTYPES_H

static const int QUADS_PER_ROW = 64;

// Plaintext tilelist:
// use tl_, tr_, bl_, br_ prefixes
//
// * blank — transparent
// * black — solid black
//
// * wall_back_horiz — back wall, connected horiz
// * wall_back_vert — back wall, connected vertically
// * wall_left_vert — left wall, connected vertically
// * wall_left_horiz — left wall, connected horiz
// * wall_right_vert — right wall, connected vert
// * wall_right_horiz — ...
// * wall_bottom — bottom wall is connected identically both ways
//
// * floor
// * floor_dec_full_vert
// * floor_dec_full_horiz
// * floor_dec_semi_vert
// * floor_dec_semi_horiz

enum QuadType {
    // These groupings are horribly arbitrary.
    
    // First row
    tl_blank = 0,
    tr_blank,
    
    tl_black,
    tr_black,
    
    tl_wall_back_horiz,
    tr_wall_back_horiz,
    
    tl_wall_back_vert,
    tr_wall_back_vert,
    
    tl_wall_left_vert, // TODO condense?
    tr_wall_left_vert,
    
    tl_wall_left_horiz,
    tr_wall_left_horiz,
    
    tl_wall_right_vert,
    tr_wall_right_vert,
    
    tl_wall_right_horiz,
    tr_wall_right_horiz,
    
    tl_wall_bottom,
    tr_wall_bottom,
    
    tl_floor,
    tr_floor,
    
    tl_floor_dec_full_vert,
    tr_floor_dec_full_vert,
    
    tl_floor_dec_full_horiz,
    tr_floor_dec_full_horiz,
    
    tl_floor_dec_semi_vert,
    tr_floor_dec_semi_vert,
    
    tl_floor_hec_semi_horiz,
    tr_floor_dec_semi_horiz
    
    // Second row
    bl_blank = 0 + QUADS_PER_ROW,
    br_blank,
    
    bl_black,
    br_black,
    
    bl_wall_back_horiz,
    br_wall_back_horiz,
    
    bl_wall_back_vert,
    br_wall_back_vert,
    
    bl_wall_left_vert, // TODO condense?
    br_wall_left_vert,
    
    bl_wall_left_horiz,
    br_wall_left_horiz,
    
    bl_wall_right_vert,
    br_wall_right_vert,
    
    bl_wall_right_horiz,
    br_wall_right_horiz,
    
    bl_wall_bottom,
    br_wall_bottom,
    
    bl_floor,
    br_floor,
    
    bl_floor_dec_full_vert,
    br_floor_dec_full_vert,
    
    bl_floor_dec_full_horiz,
    br_floor_dec_full_horiz,
    
    bl_floor_dec_semi_vert,
    br_floor_dec_semi_vert,
    
    bl_floor_hec_semi_horiz,
    br_floor_dec_semi_horiz
};

#endif // QUADTYPES_H