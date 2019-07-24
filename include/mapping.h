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

enum ChannelType {
    GOALPOST = 0,
    LINES = 1,
    NOTCONNECTED = 2
};

class MappingConfig {
public:
    // global settings
    size_t leds_per_channel = 700;

    float pitch_length = 20.0;
    float pitch_width = 15.0;
    float pitch_length_half;
    float pitch_width_half;

    // channel on the octo board
    ChannelType channels[8] = {
        ChannelType::GOALPOST,
        ChannelType::GOALPOST,
        ChannelType::LINES,
        ChannelType::NOTCONNECTED,
        ChannelType::GOALPOST,
        ChannelType::GOALPOST,
        ChannelType::LINES,
        ChannelType::NOTCONNECTED
    };
    Position positions[8];
    
    // goal settings
    size_t goal_led_strip_length = 50;
    size_t num_goal_leds_excluded = 5;
    size_t num_goal_leds_excluded_double;
    size_t goal_led_strip_length_cropped;
    size_t addresses_per_goal = 600;
    float pixel_height = 0.1;
    float goal_width_half = 2.5;
    float radius = 0.1;

    // line settings
    float pixel_length = 0.05;
    float line_width = 0.05;

    MappingConfig() {
        goal_led_strip_length_cropped = goal_led_strip_length - num_goal_leds_excluded;
        pitch_length_half = pitch_length/2;
        pitch_width_half = pitch_width/2;
        num_goal_leds_excluded_double = num_goal_leds_excluded*2;
        positions[0] = Position(-pitch_length_half, -goal_width_half);
        positions[1] = Position(-pitch_length_half, goal_width_half);
        positions[2] = Position(1, 0); // line direction
        positions[4] = Position(pitch_length_half, goal_width_half);
        positions[5] = Position(pitch_length_half, -goal_width_half);
        positions[6] = Position(-1, 0); // line direction
    }

    bool isGoal(size_t address) const {
        return channels[int(address / leds_per_channel)] == ChannelType::GOALPOST;
    }

    bool isLine(size_t address) const {
        return channels[int(address / leds_per_channel)] == ChannelType::LINES;
    }

    // +x is true/positive
    int getSide(size_t address) const {
        return ((address / leds_per_channel) == 4) ? 1 : -1;
    }

    // +x is true/positive
    bool getSideBool(size_t address) const {
        return (address > (2*leds_per_channel));
    }

    ChannelType getChannelType(size_t channel) const {
        return channels[channel];
    }

    Position getPosition(size_t channel) const {
        return positions[channel];
    }

    //assumes all LEDs are in 1 group for each pole
    //removes last 5 address on each shortened strip
    void addressToImageIndex(size_t address, size_t& x, size_t& y, bool& valid) const {
        size_t cropped_address = address % leds_per_channel;
        size_t gap = 0;
        size_t low = goal_led_strip_length_cropped;
        for (; (low < addresses_per_goal); low+=2*goal_led_strip_length) {
            if (cropped_address < low) {
                break;
            } else if (cropped_address < (low+num_goal_leds_excluded_double)) {
                valid = false;
                return;
            }
            gap+=num_goal_leds_excluded_double;
        }

        cropped_address -= gap;

        valid = true;
        x = (address % addresses_per_goal) / goal_led_strip_length;
        if (x % 2 == 0) {
            y = (cropped_address % goal_led_strip_length_cropped);
        } else {
            y = (goal_led_strip_length_cropped - 1) -
                (cropped_address % goal_led_strip_length_cropped);
        }
    }

    //assumes all LEDs are in 1 group for each pole, 12 strips
    // TODO add position of pixel around the pole
    void addressToCartesianPoint(size_t address, float& x_cart, float& y_cart, float& z_cart) const {
        size_t x, y;
        bool valid;
        bool goal = isGoal(address);
        if (goal) {
            addressToImageIndex(address, x, y, valid);
        }
        size_t goal_index = address / leds_per_channel;
        // for goals
        if (goal) {
            if (goal_index == 0) {
                x_cart = -(pitch_length_half);
                y_cart = -(goal_width_half);
            } else if (goal_index == 1) {
                x_cart = -(pitch_length_half);
                y_cart = (goal_width_half);
            } else if (goal_index == 2) {
                x_cart = (pitch_length_half);
                y_cart = (goal_width_half);
            } else if (goal_index == 3) {
                x_cart = (pitch_length_half);
                y_cart = -(goal_width_half);
            }
            z_cart = y * pixel_height;
        } else { //for lines
            size_t progressIndex = address % leds_per_channel;
            int side = getSide(address);
            if (progressIndex < 200) {
                x_cart = side * float(progressIndex) * pixel_length;
                y_cart = (pitch_width_half);
            } else if (progressIndex < 500) {
                x_cart = side*(pitch_length_half); 
                y_cart = (pitch_width_half) - (progressIndex+1 - 200) * pixel_length; 
            } else {
                x_cart = -side*((pitch_length_half) - (progressIndex+1 - 500) * pixel_length); 
                y_cart = -(pitch_width_half); 
            }
            z_cart = 0;
        }
    }


};

const MappingConfig mapping_config;