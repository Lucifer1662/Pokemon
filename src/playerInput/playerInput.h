#pragma once

struct PlayerInput {
    virtual void makeDecision();
    virtual ~PlayerInput() = default;
};