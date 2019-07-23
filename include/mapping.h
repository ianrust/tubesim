struct Position {
    float x = 0;
    float y = 0;
    float z = 0;
    Position(){};
    Position(float x_, float y_) {
        x = x_;
        y = y_;
        z = 0;
    }
};

// enum CHANNEL_TYPE

class MappingConfing {
public:
    // global settings
    size_t leds_per_channel = 700;

    float pitch_length = 20.0;
    float pitch_width = 15.0;
    float pitch_length_half;
    float pitch_width_half;

    // channel on the octo board
    size_t goal_channels[4] = {0, 1, 4, 5};
    Position goal_positions[4];
    
    size_t line_channels[2] = {2, 6};


    // goal settings
    size_t goal_led_strip_length = 50;
    size_t num_goal_leds_excluded = 5;
    size_t num_goal_leds_excluded_double;
    size_t goal_led_strip_length_cropped;
    size_t addresses_per_goal = 600;
    float pixel_height = 0.1;
    float goal_width_half = 7.5;

    // line settings
    float pixel_length = 0.05;

    MappingConfing() {
        goal_led_strip_length_cropped = goal_led_strip_length - num_goal_leds_excluded;
        pitch_length_half = pitch_length/2;
        pitch_width_half = pitch_width/2;
        num_goal_leds_excluded_double = num_goal_leds_excluded*2;
        goal_positions[0] = Position(-pitch_length_half, -pitch_width_half);
        goal_positions[1] = Position(-pitch_length_half, pitch_width_half);
        goal_positions[2] = Position(pitch_length_half, pitch_width_half);
        goal_positions[3] = Position(pitch_length_half, -pitch_width_half);
    }

};

const MappingConfing mapping_config;


bool isGoal(size_t address) {
    return (address / mapping_config.leds_per_channel) < 4;
}

// +x is true/positive
int getSide(size_t address) {
    return ((address / mapping_config.leds_per_channel) == 4) ? 1 : -1;
}

// +x is true/positive
bool getSideBool(size_t address) {
    return (address > (2*mapping_config.leds_per_channel));
}

//assumes all LEDs are in 1 group for each pole
//removes last 5 address on each shortened strip
void addressToImageIndex(size_t address, size_t& x, size_t& y, bool& valid) {
    size_t cropped_address = address % mapping_config.leds_per_channel;
    size_t gap = 0;
    size_t low = mapping_config.goal_led_strip_length_cropped;
    for (; (low < mapping_config.addresses_per_goal); low+=2*mapping_config.goal_led_strip_length) {
        if (cropped_address < low) {
            break;
        } else if (cropped_address < (low+mapping_config.num_goal_leds_excluded_double)) {
            valid = false;
            return;
        }
        gap+=mapping_config.num_goal_leds_excluded_double;
    }

    cropped_address -= gap;

    valid = true;
    x = (address % mapping_config.addresses_per_goal) / mapping_config.goal_led_strip_length;
    if (x % 2 == 0) {
        y = (cropped_address % mapping_config.goal_led_strip_length_cropped);
    } else {
        y = (mapping_config.goal_led_strip_length_cropped - 1) -
            (cropped_address % mapping_config.goal_led_strip_length_cropped);
    }
}

//assumes all LEDs are in 1 group for each pole, 12 strips
// TODO add position of pixel around the pole
void addressToCartesianPoint(size_t address, float& x_cart, float& y_cart, float& z_cart) {
    size_t x, y;
    bool valid;
    bool goal = isGoal(address);
    if (goal) {
        addressToImageIndex(address, x, y, valid);
    }
    size_t goal_index = address / mapping_config.leds_per_channel;
    // for goals
    if (goal) {
        if (goal_index == 0) {
            x_cart = -(mapping_config.pitch_length_half);
            y_cart = -(mapping_config.goal_width_half);
        } else if (goal_index == 1) {
            x_cart = -(mapping_config.pitch_length_half);
            y_cart = (mapping_config.goal_width_half);
        } else if (goal_index == 2) {
            x_cart = (mapping_config.pitch_length_half);
            y_cart = (mapping_config.goal_width_half);
        } else if (goal_index == 3) {
            x_cart = (mapping_config.pitch_length_half);
            y_cart = -(mapping_config.goal_width_half);
        }
        z_cart = y * mapping_config.pixel_height;
    } else { //for lines
        size_t progressIndex = address % mapping_config.leds_per_channel;
        int side = getSide(address);
        if (progressIndex < 200) {
            x_cart = side * float(progressIndex) * mapping_config.pixel_length;
            y_cart = (mapping_config.pitch_width_half);
        } else if (progressIndex < 500) {
            x_cart = side*(mapping_config.pitch_length_half); 
            y_cart = (mapping_config.pitch_width_half) - (progressIndex+1 - 200) * mapping_config.pixel_length; 
        } else {
            x_cart = -side*((mapping_config.pitch_length_half) - (progressIndex+1 - 500) * mapping_config.pixel_length); 
            y_cart = -(mapping_config.pitch_width_half); 
        }
        z_cart = 0;
    }
}
