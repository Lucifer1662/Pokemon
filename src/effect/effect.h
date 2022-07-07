#pragma once


struct Effect {
    virtual bool trigger() = 0;
    virtual ~Effect() = default;
};