#include "header.h"

// Define platform segments
typedef struct {
    int startX;
    int endX;
    int groundY;
} GroundSegment;

#define NUM_SEGMENTS 6  // Number of platform areas

GroundSegment groundData[NUM_SEGMENTS] = {
    {0, 555, 560},
    {560, 730, 470},
    {830, 996, 390},
    {1046, 1611, 560},
    {1732, 2060, 414},
    {2162, 2324, 414}
};

// Function to get the ground/platform height at a given x position
int getGroundHeight(int x) {
    for (int i = 0; i < NUM_SEGMENTS; i++) {
        if (x >= groundData[i].startX && x <= groundData[i].endX) {
            return groundData[i].groundY;
        }
    }
    return -1;  // No ground (fall zone)
}

// Function to check if the player is on a platform
int isOnPlatform(int x, int y) {
    int groundY = getGroundHeight(x);
    return (groundY != -1 && y + 64 >= groundY);  // 64 is the player's height
}
