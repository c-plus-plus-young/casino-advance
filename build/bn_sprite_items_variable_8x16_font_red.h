#ifndef BN_SPRITE_ITEMS_VARIABLE_8X16_FONT_RED_H
#define BN_SPRITE_ITEMS_VARIABLE_8X16_FONT_RED_H

#include "bn_sprite_item.h"

//{{BLOCK(variable_8x16_font_red_bn_gfx)

//======================================================================
//
//	variable_8x16_font_red_bn_gfx, 8x16@4, 
//	+ palette 16 entries, not compressed
//	+ 2 tiles Metatiled by 1x2 not compressed
//	Total size: 32 + 64 = 96
//
//	Time-stamp: 2025-05-06, 15:35:36
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_VARIABLE_8X16_FONT_RED_BN_GFX_H
#define GRIT_VARIABLE_8X16_FONT_RED_BN_GFX_H

#define variable_8x16_font_red_bn_gfxTilesLen 64
extern const bn::tile variable_8x16_font_red_bn_gfxTiles[2];

#define variable_8x16_font_red_bn_gfxPalLen 32
extern const bn::color variable_8x16_font_red_bn_gfxPal[16];

#endif // GRIT_VARIABLE_8X16_FONT_RED_BN_GFX_H

//}}BLOCK(variable_8x16_font_red_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item variable_8x16_font_red(sprite_shape_size(sprite_shape::TALL, sprite_size::SMALL), 
            sprite_tiles_item(span<const tile>(variable_8x16_font_red_bn_gfxTiles, 2), bpp_mode::BPP_4, compression_type::NONE, 1), 
            sprite_palette_item(span<const color>(variable_8x16_font_red_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

