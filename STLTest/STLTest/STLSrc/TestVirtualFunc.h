#pragma once

class BaseCls
{
public:
    BaseCls();

    virtual void Init();
};

class DeriveCls : public BaseCls
{
public:
    DeriveCls();

    virtual void Init();
};