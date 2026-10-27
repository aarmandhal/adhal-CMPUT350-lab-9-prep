#ifndef CAMERA_H
#define CAMERA_H

#include "vector_util.h"
#include <SFML/System.hpp>

class Camera {
public:
    Camera(const sf::Vector2f& windowSize, const sf::Vector2f& viewCenterWorld,
           float worldUnitsPerPixel = 1.f)
        : mWindowSize{windowSize},
          mViewCenterWorld{viewCenterWorld},
          mWorldUnitsPerPixel{worldUnitsPerPixel} {}

    // TODO: all of these:

    sf::Vector2f windowToWorld(const sf::Vector2f& pWindow) {
        // transform window coords to world coords
        sf::Vector2f world =
            mViewCenterWorld + (pWindow - mWindowSize * 0.5f) * mWorldUnitsPerPixel;
        return world;
    };

    sf::Vector2f worldToWindow(const sf::Vector2f& pWorld) {
        // transform world coords to window coords
        sf::Vector2f window =
            mWindowSize * 0.5f + (pWorld - mViewCenterWorld) / mWorldUnitsPerPixel;
        return window;
    };

    sf::Vector2f windowPercentToWorld(const sf::Vector2f& pWindowPercent) {
        // transform window coords to world coords as a fraction of window size
        sf::Vector2f pWindow = pWindowPercent * mWindowSize;
        return windowToWorld(pWindow);
    };

    sf::Vector2f worldToWindowPercent(const sf::Vector2f& pWorld) {
        // transform world coords to window coords as a fraction of window size
        sf::Vector2f pWindow = worldToWindow(pWorld);
        return pWindow / mWindowSize;
    };

    void translateWorld(const sf::Vector2f& deltaWorld) {
        // translate the world by deltaWorld
        mViewCenterWorld += deltaWorld;
    };

    void translateWindow(const sf::Vector2f& deltaScreen) {
        // translate the world by deltaScreen in world units
        translateWorld(deltaScreen * mWorldUnitsPerPixel);
    };

    void translateWindowPercent(const sf::Vector2f& deltaScreenPercent) {
        // translate the world by deltaScreenPercent in world units
        translateWindow(deltaScreenPercent * mWindowSize);
    };

    void setCamera(const sf::Vector2f& pWorld, const sf::Vector2f& pWindow) {
        // set the camera center to pWorld
        mViewCenterWorld = pWorld - (pWindow - mWindowSize * 0.5f) * mWorldUnitsPerPixel;
    };

    void setCameraPercent(const sf::Vector2f& pWorld, const sf::Vector2f& pWindowPercent) {
        // set the camera center to pWorld as a fraction of window size
        sf::Vector2f pWindow = pWindowPercent * mWindowSize;
        setCamera(pWorld, pWindow);
    };

    void setCameraCenter(const sf::Vector2f& pWorld) {
        // set the camera center to pWorld
        mViewCenterWorld = pWorld;
    };

    sf::Vector2f getCameraCenter() const {
        // get the camera center
        return mViewCenterWorld;
    };

private:
    sf::Vector2f mWindowSize;       // size of the window in screen pixels (i.e. window coords)
    sf::Vector2f mViewCenterWorld;  // world coords point corresponding to the center of our window.
    float mWorldUnitsPerPixel;      // distance in world coords covered by one pixel
};

#endif  // CAMERA_H
