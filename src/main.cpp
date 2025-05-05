// Butano's sprites and libraries
#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_sprite_text_generator.h"
#include "bn_sprite_ptr.h"
#include "bn_vector.h"
#include "bn_string.h"
#include "bn_format.h"
// Can use random module instead of mod
// #include "bn_random.h"
#include "bn_sprite_animate_actions.h"
#include "common_variable_8x16_sprite_font.h" 
#include "bn_sprite_items_variable_8x16_font_red.h"
#include "bn_sprite_actions.h"
#include "bn_bg_palettes.h"
// #include "bn_time.h"
#include "bn_log.h"
#include "bn_string.h"

// My sprites and libraries
#include "bn_sprite_items_roulette_wheel.h"
#include "spin_roulette.h"                     // Assembly mod function

int frame_counter = 0; 
int result = 0;
int spin_frame = -500;
int bet_frame = -500;
int money = 100;
int payout = 1;
bool bet_is_color = true;
bn::string<5> bet_color = "Black";
int bet_number = 17;
int bet_value = 5;

bn::sprite_text_generator text_gen(common::variable_8x16_sprite_font);
bn::vector<bn::sprite_ptr, 128> text_sprites;
bn::sprite_palette_item original_palette_item = text_gen.palette_item();

void setBetText() {
    if (bet_is_color) {
        if (bet_color == "Green") {
            payout = 17;
        } else {
            payout = 1;
        }
        text_gen.generate(-80, -70, bn::to_string<10>(bet_color) + " " + bn::to_string<10>(payout) + ":1", text_sprites);
    } else {
        payout = 35;
        if (bet_number == 37) {
            text_gen.generate(-80, -70, "00 " + bn::to_string<10>(payout) + ":1", text_sprites);
        } else {
            text_gen.generate(-80, -70, bn::to_string<10>(bet_number) + " " + bn::to_string<10>(payout) + ":1", text_sprites);
        }
    }
    // text_gen.generate(0, -70, "Bet: $" + bn::to_string<16>(bet_value), text_sprites);
}

int calculateMoneyEarned(int spin_result) {
    if (bet_is_color ) {
        if (bet_color == "Red") {
            if (spin_result == 1 || spin_result == 3 || spin_result == 5 || spin_result == 7 ||
                spin_result == 9 || spin_result == 12 || spin_result == 14 || spin_result == 16 ||
                spin_result == 18 || spin_result == 21 || spin_result == 23 || spin_result == 25 ||
                spin_result == 27 || spin_result == 28 || spin_result == 30 || spin_result == 32 ||
                spin_result == 34 || spin_result == 36) {
                return bet_value;
            } else {
                return -1 * bet_value;
            }
        } else if (bet_color == "Black") {
            if (spin_result == 2 || spin_result == 4 || spin_result == 6 || spin_result == 8 ||
                spin_result == 10 || spin_result == 11 || spin_result == 13 || spin_result == 15 ||
                spin_result == 17 || spin_result == 19 || spin_result == 20 || spin_result == 22 ||
                spin_result == 24 || spin_result == 26 || spin_result == 29 || spin_result == 31 ||
                spin_result == 33 || spin_result == 35) {
                return bet_value;
            } else {
                return -1 * bet_value;
            }
        } else {
            if (spin_result == 0 || spin_result == 37) {
                return payout * bet_value;
            } else {
                return (-1 * bet_value);
            }
        }
    } else {
        if (spin_result == bet_number) {
            return payout * bet_value;
        } else {
            return (-1 * bet_value);
        }
    }
}

int main() {
    bn::core::init();
    // template<int MaxSize> string(std::nullptr_t)-> bn::string<MaxSize>

    // // Jan 2nd, 2000 12:30:01
    // // bn::time custom_time(2000, 1, 2, 12, 30, 1);
    // bn::time current_time;
    // current_time.set_hour(12);
    // current_time.set_minute(30);
    // current_time.set_second(1);
    // // bn::random rand_int;

    // int seed;

    // bn::optional<bn::time> ?_time = bn::time::current();
    // if (current_time) {
    //     int seed = current_time.second();
    //     BN_LOG("Seconds: " + bn::to_string<2>(seed));
    // }
    // else {
    //     BN_LOG("RTC not available or time invalid");
    //     int seed = -1;
    // }
    // BN_LOG(bn::to_string<64>(seed));

    // Background
    bn::bg_palettes::set_transparent_color(bn::color(0, 16, 4));

    // Roulette Wheel
    bn::sprite_ptr roulette_wheel_sprite = bn::sprite_items::roulette_wheel.create_sprite(0, 48);
    roulette_wheel_sprite.set_scale(2);
    // Defines animation for wheel: it has 76 frames which should change every 1/20th of a second
    bn::sprite_animate_action<76>action = bn::create_sprite_animate_action_forever(
        roulette_wheel_sprite, 5, bn::sprite_items::roulette_wheel.tiles_item(), 
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 
        22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 
        41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 
        60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75);

    // Text
    text_gen.set_center_alignment();
    text_gen.generate(0, -35, "Roulette Wheel Simulator", text_sprites);
    text_gen.generate(0, -20, "All bets $5. Press A to spin", text_sprites);
    text_gen.generate(0, -5, "and arrow keys to change bet", text_sprites);
    text_gen.generate(100, -70, "$" + bn::to_string<11>(money), text_sprites);
    setBetText();
    

    while(true) {

        if (money == 0) {
            text_sprites.clear();
            text_gen.generate(0, -27, "$0 left. Game Over", text_sprites);
            // WAIT FUNCTION
            break;
        }

        if ((bn::keypad::right_released() || bn::keypad::left_released()) && frame_counter > bet_frame + 5) {
            text_sprites.clear();
            bet_is_color = !bet_is_color;
            text_gen.generate(100, -70, "$" + bn::to_string<11>(money), text_sprites);
            bet_frame = frame_counter;
            setBetText();
            bn::core::update();
        }

        if (bn::keypad::down_released() && frame_counter > bet_frame + 5) {
            text_sprites.clear();
            if (bet_is_color == false) {
                if (bet_number > 0 ) {
                    bet_number -=1;
                } else {
                    bet_number = 37;
                }
            } else {
                if (bet_color == "Black") {
                    bet_color = "Red";
                } else if (bet_color == "Red") {
                    bet_color = "Green";
                } else {
                    bet_color = "Black";
                }
            }
            text_gen.generate(100, -70, "$" + bn::to_string<11>(money), text_sprites);
            bet_frame = frame_counter;
            setBetText();
            bn::core::update();
        }

        if (bn::keypad::up_released() && frame_counter > bet_frame + 5) {
            text_sprites.clear();
            if (bet_is_color == false) {
                if (bet_number < 37 ) {
                    bet_number +=1;
                } else {
                    bet_number = 0;
                }
            } else {
                if (bet_color == "Black") {
                    bet_color = "Green";
                } else if (bet_color == "Red") {
                    bet_color = "Black";
                } else {
                    bet_color = "Red";
                }
            }
            text_gen.generate(100, -70, "$" + bn::to_string<11>(money), text_sprites);
            setBetText();
            bet_frame = frame_counter;
            bn::core::update();
        }

        if (bn::keypad::a_released() && (frame_counter > spin_frame + 90)) {
            // Show loading message while spinning
            text_sprites.clear();
            text_gen.generate(0, -27, "Spinning...", text_sprites);
            text_gen.generate(100, -70, "$" + bn::to_string<11>(money), text_sprites);
            setBetText();
            spin_frame = frame_counter;
            
            result = spin_roulette(frame_counter, 38);
            // result = rand_int.get_unbiased_int(0, 38);
            bn::core::update();
        }

        if (frame_counter <= spin_frame + 100 && frame_counter >= spin_frame + 90) {
            // Update the message to show the result
            // 1-36 are themselves, 37 is 00
            if(result == 37) {
                text_sprites.clear();
                text_gen.generate(0, -35, "Landed on 00", text_sprites);
                text_gen.generate(0, -20, "Press A to spin again", text_sprites);
                setBetText();
            } else {
                text_sprites.clear();
                if (result == 1 || result == 3 || result == 5 || result == 7 ||
                    result == 9 || result == 12 || result == 14 || result == 16 ||
                    result == 18 || result == 21 || result == 23 || result == 25 ||
                    result == 27 || result == 28 || result == 30 || result == 32 ||
                    result == 34 || result == 36) {
                    text_gen.set_palette_item(bn::sprite_items::variable_8x16_font_red.palette_item());
                } 
                text_gen.generate(0, -35, "Landed on: " + bn::to_string<13>(result), text_sprites);
                text_gen.generate(0, -20, "Press A to spin again", text_sprites);
                text_gen.set_palette_item(original_palette_item);
                setBetText();
            }

            money += calculateMoneyEarned(result);
            text_gen.generate(100, -70, "$" + bn::to_string<11>(money), text_sprites);
            spin_frame = -500;
            bn::core::update();
        }

        frame_counter++;
        action.update();
        bn::core::update();
    }
}