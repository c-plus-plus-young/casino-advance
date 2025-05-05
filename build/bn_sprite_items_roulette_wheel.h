#ifndef BN_SPRITE_ITEMS_ROULETTE_WHEEL_H
#define BN_SPRITE_ITEMS_ROULETTE_WHEEL_H

#include "bn_sprite_item.h"

//{{BLOCK(roulette_wheel_bn_gfx)

//======================================================================
//
//	roulette_wheel_bn_gfx, 64x2432@4, 
//	+ palette 16 entries, not compressed
//	+ 2432 tiles Metatiled by 8x4 not compressed
//	Total size: 32 + 77824 = 77856
//
//	Time-stamp: 2025-04-19, 13:56:45
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_ROULETTE_WHEEL_BN_GFX_H
#define GRIT_ROULETTE_WHEEL_BN_GFX_H

#define roulette_wheel_bn_gfxTilesLen 77824
extern const bn::tile roulette_wheel_bn_gfxTiles[2432];

#define roulette_wheel_bn_gfxPalLen 32
extern const bn::color roulette_wheel_bn_gfxPal[16];

#endif // GRIT_ROULETTE_WHEEL_BN_GFX_H

//}}BLOCK(roulette_wheel_bn_gfx)

namespace bn::sprite_items
{
    constexpr inline sprite_item roulette_wheel(sprite_shape_size(sprite_shape::WIDE, sprite_size::HUGE), 
            sprite_tiles_item(span<const tile>(roulette_wheel_bn_gfxTiles, 2432), bpp_mode::BPP_4, compression_type::NONE, 76), 
            sprite_palette_item(span<const color>(roulette_wheel_bn_gfxPal, 16), bpp_mode::BPP_4, compression_type::NONE));
}

#endif

